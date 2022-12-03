///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <DB/Products.hpp>
#include <POS/Product.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Static
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
///
///////////////////////////////////////////////////////////////////////////
auto ::db::Products::get()
    -> ::std::shared_ptr<Products>
{
    ::std::string name{ "Products" };
    if (::std::ifstream ifs("database/"s + name + ".csv"); !ifs.good()) {
        auto db{ ::std::make_shared<Products>(name) };
        db->executeCode("CREATE TABLE "s + name + "("s +
            "ID       INT NOT NULL,"s +
            "NAME     TEXT,"s +
            "PRICE    INT,"s +
            "QUANTITY INT"s +
        ");" );

        db->insert({ 1, "testProduct01", 1234, 1 });
        db->insert({ 2, "testProduct02", 1234, 1 });
        db->insert({ 3, "testProduct03", 1234, 1 });
        db->insert({ 4, "testProduct04", 1234, 1 });
        db->insert({ 5, "testProduct05", 1234, 1 });
        db->insert({ 6, "testProduct06", 1234, 1 });
        db->insert({ 7, "testProduct07", 1234, 1 });
        db->insert({ 8, "testProduct08", 1234, 1 });
        db->insert({ 9, "testProduct09", 1234, 1 });

        return db;
    } else {
        return ::std::make_shared<Products>(name);
    }
}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::db::Products::Products(
    ::std::string name,
    ::std::string path
)
    : ::db::ADatabase{ name, path }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Operations
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
void ::db::Products::insert(
    const ::pos::Product& product
)
{
    this->insertInto(
        { "ID", "NAME", "PRICE", "QUANTITY" },
        { ::std::to_string(product.getId()), "'"s + product.getName() + "'", ::std::to_string(product.getPrice()), ::std::to_string(product.getQuantity()) }
    );
}

static int callback(void* productPtr, int argc, char **argv, char** azColName [[ maybe_unused ]])
{
    if (argc < 4 || ::std::stol(argv[3]) <= 0) {
        return 1;
    }

    auto& products{ *static_cast<::std::vector<::pos::Product>*>(productPtr) };

    ::std::size_t id{ ::std::stol(argv[0]) };
    ::std::string name{ argv[1] };
    ::std::int64_t price{ ::std::stol(argv[2]) };

    products.emplace_back(id, name, price, 1);
    return 0;
}

///////////////////////////////////////////////////////////////////////////
auto ::db::Products::retrieve(
    const ::std::vector<::std::string>& ids
) -> ::std::vector<::pos::Product>
{
    ::std::vector<::pos::Product> products;

    for (auto& id : ids) {
        ::std::string sqlCode{ "SELECT * FROM Products WHERE ID="s + id + "" };
        if (char* errPtr; sqlite3_exec(m_db, sqlCode.c_str(), callback, static_cast<void*>(&products), &errPtr) != SQLITE_OK) {
            // ::std::string errMsg{ errPtr };
            // ::sqlite3_free(errPtr);
            // throw ::std::runtime_error{ "Error executing DB code:\n\n" + sqlCode + "\n\n\t"s + errMsg };
        }
    }

    return products;
}

///////////////////////////////////////////////////////////////////////////
auto ::db::Products::retrieveAll()
    -> ::std::vector<::pos::Product>
{
    ::std::vector<::pos::Product> products;

    ::std::string sqlCode{ "SELECT * FROM Products" };
    if (char* errPtr; sqlite3_exec(m_db, sqlCode.c_str(), callback, static_cast<void*>(&products), &errPtr) != SQLITE_OK) {
        // ::std::string errMsg{ errPtr };
        // ::sqlite3_free(errPtr);
        // throw ::std::runtime_error{ "Error executing DB code:\n\n" + sqlCode + "\n\n\t"s + errMsg };
    }

    return products;
}
