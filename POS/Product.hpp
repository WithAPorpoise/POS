#pragma once

#include <POS/UI/Box/ATextBox.hpp>
#include <DB/Products.hpp>

namespace pos {

///////////////////////////////////////////////////////////////////////////
/// \brief Simplifies and automates the usage of a qt window
/// \ingroup ecs
///
/// \include Product.hpp <POS/Product.hpp>
///
/// Contains a ::QApplication and a ::QMainWindow window
///
///////////////////////////////////////////////////////////////////////////
class Product {

public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Static
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Create a product by pulling information from DB
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] static auto getFromDataBase(
        const ::std::string& id,
        ::std::shared_ptr<::db::Products> dbProducts
    ) -> Product;



public:

    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Constructors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Constructor
    ///
    /// forward to the other constructor while passing null valuesa
    ///
    ///////////////////////////////////////////////////////////////////////////
    Product(
        :std::size_t id,
        ::std::string name,
        ::std::int64_t price,
        ::std::size_t quantity = 1
    ) noexcept;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Accessors
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getId() const
        -> ::std::size_t;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getName() const
        -> const ::std::string&;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getPrice() const
        -> ::std::int64_t;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getQuantity() const
        -> ::std::size_t;



private:

    ::std::size_t m_id;
    ::std::string m_name;
    ::std::int64_t m_price;
    ::std::size_t m_quantity;

};

} // namespace pos
