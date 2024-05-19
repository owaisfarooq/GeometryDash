// Instructions.cpp
#include "Instructions.h"

Instructions::Instructions( float width, float height ) {
    if ( !font.loadFromFile( "AcherusGrotesque-Regular.otf" ) ) {
        // Handle error
    }

    instructionsText.setFont( font );
    instructionsText.setString(
        "Instructions:\n\n"
        "1. Press 'Space' to jump.\n"
        "2. Avoid the obstacles.\n"
        "3. Press 'P' to pause/resume the game.\n"
        "4. Press 'R' to reset the game.\n"
        "5. Press 'Esc' to exit the game.\n\n"
        "Press 'Esc' to go back to the menu."
    );
    instructionsText.setCharacterSize( 24 );
    instructionsText.setFillColor( sf::Color::White );
    instructionsText.setPosition( sf::Vector2f( width / 10, height / 10 ) );
}

void Instructions::draw( sf::RenderWindow& window ) {
    window.draw( instructionsText );
}

void Instructions::handleEvent( sf::Event& event, sf::RenderWindow& window ) {
    // Handle events specific to the Instructions page if needed
}
