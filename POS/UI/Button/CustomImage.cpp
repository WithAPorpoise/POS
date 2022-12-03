///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>

///////////////////////////////////////////////////////////////////////////
// Headers
///////////////////////////////////////////////////////////////////////////
#include <POS/UI/Button/CustomImage.hpp>
#include <POS/UI/ErrorNotification.hpp>



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Constructors
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
::pos::ui::button::CustomImage::CustomImage(
    ::QMainWindow& window,
    const ::std::string& filepath,
    ::std::size_t xPos,
    ::std::size_t yPos,
    ::std::size_t xSize,
    ::std::size_t ySize,
    ::std::function<void()> callback
) noexcept
    : ::pos::ui::AImageButton{ window, filepath, xPos, yPos, xSize, ySize }
    , m_window{ window }
    , m_callback{ ::std::move(callback) }
{}

///////////////////////////////////////////////////////////////////////////
::pos::ui::button::CustomImage::CustomImage(
    ::QMainWindow& window,
    const ::std::string& filepath,
    const ::std::string& tooltip,
    ::std::size_t xPos,
    ::std::size_t yPos,
    ::std::size_t xSize,
    ::std::size_t ySize,
    ::std::function<void()> callback
) noexcept
    : ::pos::ui::AImageButton{ window, filepath, tooltip, xPos, yPos, xSize, ySize }
    , m_window{ window }
    , m_callback{ ::std::move(callback) }
{}



///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////
// Override
//
///////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////
auto ::pos::ui::button::CustomImage::hitButton(
    [[ maybe_unused ]] const QPoint &pos
) const
    -> bool
{
    try {
        m_callback();
    } catch (const ::std::exception& e) {
        new ::pos::ui::ErrorNotification{ m_window, e.what() };
    }
    return false;
}
