#pragma once

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <POS/UI/Window.hpp>
#include <POS/UI/ProductContainer.hpp>
#include <POS/UI/VirtualKeyPad.hpp>
#include <POS/UI/Box/ATextBox.hpp>
#include <POS/UI/Button/CustomImage.hpp>
#include <DB/Products.hpp>

namespace pos::ui::screen {

///////////////////////////////////////////////////////////////////////////
/// \brief Describes the home page
/// \ingroup ecs
///
/// \include Home.hpp <POS/Home.hpp>
///
/// Contains a list of items, a virtual key pad and buttons to delete and
/// checkout
///
///////////////////////////////////////////////////////////////////////////
class Home {

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
    explicit Home(
        ::pos::ui::Window& window,
        ::std::shared_ptr<::db::Products> dbProducts
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
    [[ nodiscard ]] auto getVirtualKeyPad()
        -> ::pos::ui::VirtualKeyPad&;



private:

    ::pos::ui::Window& m_window;
    ::std::shared_ptr<::db::Products> m_dbProducts;

    ::pos::ui::ProductContainer m_products;
    ::pos::ui::VirtualKeyPad m_virtualKeyPad;

    ::pos::ui::button::CustomImage m_addProductButton;
    ::pos::ui::button::CustomImage m_removeProductButton;
    ::pos::ui::button::CustomImage m_clearCartButton;
    ::pos::ui::button::CustomImage m_addFundsButton;
    ::pos::ui::button::CustomImage m_payButton;
    ::pos::ui::button::CustomImage m_saveCartButton;
    ::pos::ui::button::CustomImage m_loadCartButton;
    ::pos::ui::button::CustomImage m_exitButton;
    // ::pos::ui::button::CustomImage m_createOnDataBaseButton;
    // ::pos::ui::button::CustomImage m_removeOnDataBaseButton;
    // ::pos::ui::button::CustomImage m_searchInformationOnDataBaseButton;
};

} // namespace pos::ui::screen
