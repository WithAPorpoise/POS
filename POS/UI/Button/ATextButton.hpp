#pragma once

namespace pos::ui::button {

///////////////////////////////////////////////////////////////////////////
/// \brief Simplifies the usage of a Qt button with an image
/// \ingroup ecs
///
/// \include ATextButton.hpp <POS/UI/Button/ATextButton.hpp>
///
///////////////////////////////////////////////////////////////////////////
class ATextButton
    : public ::QPushButton
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
    /// The filename is searched within the ./assets/ directory
    ///
    ///////////////////////////////////////////////////////////////////////////
    explicit ATextButton(
        ::QMainWindow& window,
        const ::std::string& text,
        ::std::size_t xPos,
        ::std::size_t yPos,
        ::std::size_t xSize,
        ::std::size_t ySize
    ) noexcept;



    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////
    // Rule of 5
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////////////////////////////////////////////////////////////////

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    virtual ~ATextButton() noexcept;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    ATextButton(
        const ATextButton& other
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Copy assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        const ATextButton& other
    ) noexcept
        -> ATextButton& = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move constructor
    ///
    ///////////////////////////////////////////////////////////////////////////
    ATextButton(
        ATextButton& that
    ) noexcept = delete;

    ///////////////////////////////////////////////////////////////////////////
    /// \brief Move assign operator
    ///
    ///////////////////////////////////////////////////////////////////////////
    auto operator=(
        ATextButton& that
    ) noexcept
        -> ATextButton = delete;



private:

    ::std::vector<::std::string> m_lines;

};

} // namespace pos::ui::button

namespace pos::ui { using ATextButton = pos::ui::button::ATextButton; }
