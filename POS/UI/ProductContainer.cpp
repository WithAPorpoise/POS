///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <POS/UI/ProductContainer.hpp>
#include <POS/UI/ErrorNotification.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::pos::ui::ProductContainer::ProductContainer(
    ::QMainWindow& window,
    ::std::shared_ptr<::db::Products> dbProducts
) noexcept
    : ProductContainer{ window, dbProducts, 0, 0, 0, 0 }
{}

///////////////////////////////////////////////////////////////////////////
::pos::ui::ProductContainer::ProductContainer(
    ::QMainWindow& window,
    ::std::shared_ptr<::db::Products> dbProducts,
    ::std::size_t xPos,
    ::std::size_t yPos,
    ::std::size_t xSize,
    ::std::size_t ySize
) noexcept
    : m_window{ window }
    , m_dbProducts{ dbProducts }
    , m_table{ new QTableWidget{ 0, 3, &window } }
    , m_totalTextBox{ window, xPos, yPos + ySize - (18 * 2 + 2), xSize, 18 }
    , m_fundsTextBox{ window, xPos, yPos + ySize - 18, xSize, 18 }
{
    for (auto i{ 1uz }; true; ++i) {
        if (::std::ifstream ifs("database/cart/Cart"s + ::std::to_string(i) + ".csv"); !ifs.good()) {
            m_id = ::std::to_string(i);
            break;
        }
    }

    m_table->move(static_cast<int>(xPos), static_cast<int>(yPos));
    m_table->resize(static_cast<int>(xSize), static_cast<int>(ySize - (20 * 2)));
    m_table->verticalHeader()->hide();
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);

    {
        QStringList headers;
        headers << "Price" << "Quantity" << "Name";
        m_table->setHorizontalHeaderLabels(headers);
    }

    m_table->setColumnWidth(0, 80);
    m_table->setColumnWidth(1, 60);
    m_table->horizontalHeader()->setStretchLastSection(true);

    m_totalTextBox.setVerticalScrollBarPolicy(::Qt::ScrollBarAlwaysOff);
    m_fundsTextBox.setVerticalScrollBarPolicy(::Qt::ScrollBarAlwaysOff);
    this->printTotal();
    this->printFunds();
    m_table->show();
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Operations
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::pos::ui::ProductContainer::load(
    const ::std::string& id
)
{
    if (::std::ifstream ifs("database/cart/Cart"s + id + ".csv"); !ifs.good()) {
        throw ::std::runtime_error{ "Cart ID does not exist" };
    }

    this->clear();
    m_products.clear();

    m_id = id;
    auto db{ ::std::make_shared<::db::Cart>("Cart"s + m_id) };
    for (auto& product : db->retrieveAll()) {
        this->add(product);
    }
}

///////////////////////////////////////////////////////////////////////////
void ::pos::ui::ProductContainer::save()
{
    ::std::remove(::std::string{ "database/cart/Cart"s + m_id + ".csv" }.c_str());
    auto db{ ::db::Cart::get("Cart"s + m_id) };
    for (auto& product : m_products) {
        db->insert(product);
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Accessors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::pos::ui::ProductContainer::add(
    const ::pos::Product& product
) -> ::std::size_t
{
    m_products.push_back(product);

    const auto index{ m_products.size() - 1 };

    m_table->insertRow(static_cast<int>(index));
    m_table->setCurrentIndex(m_table->model()->index(static_cast<int>(index), 0));

    m_table->setItem(static_cast<int>(index), 0, new ::QTableWidgetItem{ ::fmt::format("${}.{}",
        product.getPrice() * product.getQuantity() / 100,
        product.getPrice() * product.getQuantity() % 100
    ).c_str() });
    m_table->setItem(static_cast<int>(index), 1, new ::QTableWidgetItem{ ::fmt::format("{}",
        product.getQuantity()
    ).c_str() });
    m_table->setItem(static_cast<int>(index), 2, new ::QTableWidgetItem{ ::fmt::format("{}",
        product.getName()
    ).c_str() });

    this->printTotal();

    return index;
}

///////////////////////////////////////////////////////////////////////////
auto ::pos::ui::ProductContainer::size()
    -> ::std::size_t
{
    return m_products.size();
}

///////////////////////////////////////////////////////////////////////////
auto ::pos::ui::ProductContainer::emplaceFromId(
    const ::std::vector<::std::string>& ids
) -> ::std::size_t
{
    return this->add(::pos::Product::getFromDataBase(ids[0], m_dbProducts));
}

///////////////////////////////////////////////////////////////////////////
auto ::pos::ui::ProductContainer::addFunds(
    const ::std::vector<::std::string>& values
) -> ::std::size_t
{
    m_funds += ::std::stoi(values[0]) * 100;
    if (auto it{ values[0].find(".") }; it != ::std::string::npos) {
        m_funds += ::std::stoi(values[0].substr(it + 1));
    }
    this->printFunds();
    return m_funds;
}

///////////////////////////////////////////////////////////////////////////
auto ::pos::ui::ProductContainer::pay()
    -> bool
{
    auto total{ 0ll };
    for (const auto& p : m_products) {
        total += p.getPrice() * p.getQuantity();
    }
    if (m_funds >= total) {
        this->clear();
        m_funds -= total;
        this->printFunds();
        ::std::remove(::std::string{ "database/cart/Cart"s + m_id + ".csv" }.c_str());
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////
void ::pos::ui::ProductContainer::remove(
    ::std::size_t productIndex
)
{
    m_table->removeRow(static_cast<int>(productIndex));
    m_products.erase(m_products.begin() + static_cast<long>(productIndex));
    this->printTotal();
}

///////////////////////////////////////////////////////////////////////////
void ::pos::ui::ProductContainer::removeSelected()
{
    if (!m_products.empty()) {
        auto productIndex{ m_table->selectionModel()->selectedRows().front().row() };
        m_table->removeRow(productIndex);
        m_products.erase(m_products.begin() + productIndex);
        if (productIndex) {
            m_table->setCurrentIndex(m_table->model()->index(productIndex - 1, 0));
        } else {
            m_table->setCurrentIndex(m_table->model()->index(0, 0));
        }
        this->printTotal();
    } else {
        new ::pos::ui::ErrorNotification{ m_window, "No remaining item to delete" };
    }
}

///////////////////////////////////////////////////////////////////////////
void ::pos::ui::ProductContainer::clear()
{
    while (m_table->rowCount()) {
        m_table->removeRow(0);
    }
    m_products.clear();
    this->printTotal();
}

///////////////////////////////////////////////////////////////////////////
void ::pos::ui::ProductContainer::setReadOnly(
    bool value
)
{
    m_table->setDisabled(value);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Helpers
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::pos::ui::ProductContainer::printTotal()
{
    auto total{ 0ll };
    for (const auto& p : m_products) {
        total += p.getPrice() * p.getQuantity();
    }
    m_totalTextBox.clearLine();
    m_totalTextBox.addLine(::fmt::format("Total: ${}.{}", total / 100, total % 100));
    m_totalTextBox.print();
}

///////////////////////////////////////////////////////////////////////////
void ::pos::ui::ProductContainer::printFunds()
{
    m_fundsTextBox.clearLine();
    if (m_funds % 100 == 0) {
        m_fundsTextBox.addLine(::fmt::format("Funds: ${}.00", m_funds / 100, m_funds % 100));
    } else if (m_funds % 100 < 10) {
        m_fundsTextBox.addLine(::fmt::format("Funds: ${}.0{}", m_funds / 100, m_funds % 100));
    } else {
        m_fundsTextBox.addLine(::fmt::format("Funds: ${}.{}", m_funds / 100, m_funds % 100));
    }
    m_fundsTextBox.print();
}
