#pragma once


#include <POS/UI/VirtualKeyPad.hpp>

namespace pos::ui {

///////////////////////////////////////////////////////////////////////////
/// \brief Simplifies and automates the usage of a qt window
/// \ingroup ecs
///
/// \include Window.hpp <POS/UI/Window.hpp>
///
/// Contains a ::QApplication and a ::QMainWindow window
///
///////////////////////////////////////////////////////////////////////////
class Window
    : public ::QApplication
{

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
    /// Creates, Resizes, renames, and show a Qt window
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit Window(
        int argc,
        char *argv[],
        ::std::size_t xSize,
        ::std::size_t ySize,
        const ::std::string& name
    ) noexcept;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Helpers
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    void resize(
        ::std::size_t xSize,
        ::std::size_t ySize
    );

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto get()
        -> ::QMainWindow&;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    [[ nodiscard ]] auto getSize() const
        -> ::QSize;

    ///////////////////////////////////////////////////////////////////////////
    ///
    ///////////////////////////////////////////////////////////////////////////
    void linkVirtualKeyPad(
        ::pos::ui::VirtualKeyPad& virtualKeyPad
    )
    {
        m_window.m_keyboardInputCallback =
            ::std::bind_front(&::pos::ui::VirtualKeyPad::write, &virtualKeyPad);
    }



private:

    class InternalWindow
        : public ::QMainWindow
    {
    protected:
        void keyPressEvent(QKeyEvent *event) override
        {
            if (m_keyboardInputCallback) {
                switch (event->key()) {
                case Qt::Key_0: m_keyboardInputCallback.value()("0"s); break;
                case Qt::Key_1: m_keyboardInputCallback.value()("1"s); break;
                case Qt::Key_2: m_keyboardInputCallback.value()("2"s); break;
                case Qt::Key_3: m_keyboardInputCallback.value()("3"s); break;
                case Qt::Key_4: m_keyboardInputCallback.value()("4"s); break;
                case Qt::Key_5: m_keyboardInputCallback.value()("5"s); break;
                case Qt::Key_6: m_keyboardInputCallback.value()("6"s); break;
                case Qt::Key_7: m_keyboardInputCallback.value()("7"s); break;
                case Qt::Key_8: m_keyboardInputCallback.value()("8"s); break;
                case Qt::Key_9: m_keyboardInputCallback.value()("9"s); break;
                case Qt::Key_Period: m_keyboardInputCallback.value()("."s); break;
                default: break;
                }
            }
        }

    public:
        ::std::optional<::std::function<void(const ::std::string&)>> m_keyboardInputCallback;
    };
    Window::InternalWindow m_window;
    ::std::size_t m_xSize;
    ::std::size_t m_ySize;

};

} // namespace pos::ui
