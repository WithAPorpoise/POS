///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <POS/UI/Screen/Home.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::pos::ui::screen::Home::Home(
    ::pos::ui::Window& window
) noexcept
    : m_window{ window }
    , m_products{
        m_window.get(),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.05),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.05),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.50),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.9)
    }, m_virtualKeyPad {
        m_window.get(),
        m_products,
        static_cast<::std::size_t>(m_window.getSize().width() * 0.56),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.05),
        static_cast<::std::size_t>(m_window.getSize().width()),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.05),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.39),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.9)
    }, m_addProductButton{
        m_window.get(),
        "add.png",
        "Add a product to cart from its ID",
        static_cast<::std::size_t>(m_window.getSize().width() * 0.56),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.05),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.08),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.08),
        [this](){
            m_virtualKeyPad.reveal(
                ::std::bind_front(&::pos::ui::ProductContainer::emplaceFromId, &m_products)
            );
        }
    }, m_removeProductButton{
        m_window.get(),
        "remove.png",
        "Remove the selected product in the cart",
        static_cast<::std::size_t>(m_window.getSize().width() * 0.56),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.15),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.08),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.08),
        [this](){
            m_products.removeSelected();
        }
    }, m_clearCartButton{
        m_window.get(),
        "clear.png",
        "Remove all products in the cart",
        static_cast<::std::size_t>(m_window.getSize().width() * 0.56),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.25),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.08),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.08),
        [this](){
            m_products.clear();
        }
    }, m_addFundsButton{
        m_window.get(),
        "addFunds.png",
        "Add funds to pay the cart",
        static_cast<::std::size_t>(m_window.getSize().width() * 0.66),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.05),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.08),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.08),
        [this](){
            m_virtualKeyPad.reveal(
                ::std::bind_front(&::pos::ui::ProductContainer::addFunds, &m_products)
            );
        }
    }, m_payButton{
        m_window.get(),
        "pay.png",
        "Pay the cart if enough funds",
        static_cast<::std::size_t>(m_window.getSize().width() * 0.66),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.15),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.08),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.08),
        [this](){
            if (!m_products.size()) {
                throw ::std::runtime_error{ "Nothing is present in the cart" };
            } else if (!m_products.pay()) {
                throw ::std::runtime_error{ "Not enough funds to pay" };
            }
        }
    }, m_saveCartButton{
        m_window.get(),
        "save.png",
        "Save the current cart into the data base",
        static_cast<::std::size_t>(m_window.getSize().width() * 0.76),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.05),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.08),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.08),
        [this](){
            throw ::std::runtime_error{ "TODO: saveCart" };
        }
    }, m_loadCartButton{
        m_window.get(),
        "load.png",
        "Replace current cart with the cart retrieved from the data base with its ID",
        static_cast<::std::size_t>(m_window.getSize().width() * 0.76),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.15),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.08),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.08),
        [this](){
            m_virtualKeyPad.reveal([](const ::std::string& id){
                throw ::std::runtime_error{ "TODO: loadCart ("s + id + ")" };
            });
        }
    }, m_exitButton{
        m_window.get(),
        "exit.png",
        "Close the POS application",
        static_cast<::std::size_t>(m_window.getSize().width() * 0.86),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.85),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.08),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.08),
        [this](){
            m_window.get().close();
        }
    }, m_createOnDataBaseButton{
        m_window.get(),
        "create.png",
        "Create a new product in the data base (will probably never work)",
        static_cast<::std::size_t>(m_window.getSize().width() * 0.86),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.05),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.08),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.08),
        [this](){
            m_virtualKeyPad.reveal([](const ::std::string& id){
                throw ::std::runtime_error{ "TODO: removeFromDB id: ("s + id + ")" };
            });
        }
    }, m_removeOnDataBaseButton{
        m_window.get(),
        "removeFromDB.png",
        "Remove a product in the data base (will probably never work)",
        static_cast<::std::size_t>(m_window.getSize().width() * 0.86),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.15),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.08),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.08),
        [this](){
            m_virtualKeyPad.reveal([](const ::std::string& id){
                throw ::std::runtime_error{ "TODO: removeFromDB id: ("s + id + ")" };
            });
        }
    }, m_searchInformationOnDataBaseButton{
        m_window.get(),
        "search.png",
        "Search information of a product in the data base",
        static_cast<::std::size_t>(m_window.getSize().width() * 0.86),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.25),
        static_cast<::std::size_t>(m_window.getSize().width() * 0.08),
        static_cast<::std::size_t>(m_window.getSize().height() * 0.08),
        [this](){
            m_virtualKeyPad.reveal([](const ::std::string& id){
                throw ::std::runtime_error{ "TODO: searchInformation id: ("s + id + ")" };
            });
        }
    }
{
    m_products.emplace(1uz, "article1"s, 10'20ll, 2uz);
    m_products.emplace(1uz, "article2"s, 22'31ll, 1uz);
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Accessors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
[[ nodiscard ]] auto ::pos::ui::screen::Home::getVirtualKeyPad()
    -> ::pos::ui::VirtualKeyPad&
{
    return m_virtualKeyPad;
}
