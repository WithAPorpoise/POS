///////////////////////////////////////////////////////////////////////////
// Precompilled headers
///////////////////////////////////////////////////////////////////////////
#include <pch.hpp>
#include <POS/UI/Window.hpp>
#include <POS/UI/Screen/Home.hpp>

///////////////////////////////////////////////////////////////////////////
auto main(
    int argc,
    char *argv[]
) -> int
{
    // ::pos::ui::Window window{ argc, argv, 1920, 1080, "MainPosSystemWindow" };
    ::pos::ui::Window window{ argc, argv, 720, 520, "MainPosSystemWindow" };
    ::pos::ui::screen::Home homeScreen{ window };
    window.linkVirtualKeyPad(homeScreen.getVirtualKeyPad());
    return window.exec();
}
