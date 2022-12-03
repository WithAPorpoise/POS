///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <POS/UI/Button/CustomText.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::pos::ui::button::CustomText::CustomText(
    ::QMainWindow& window,
    const ::std::string& text,
    ::std::size_t xPos,
    ::std::size_t yPos,
    ::std::size_t xSize,
    ::std::size_t ySize,
    ::std::function<void()> callback
) noexcept
    : ::pos::ui::ATextButton{ window, text, xPos, yPos, xSize, ySize }
    , m_callback{ ::std::move(callback) }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Override
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::pos::ui::button::CustomText::hitButton(
    [[ maybe_unused ]] const QPoint &pos
) const
    -> bool
{
    m_callback();
    return false;
}