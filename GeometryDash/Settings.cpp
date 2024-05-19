// Settings.cpp
#include "Settings.h"

Settings::Settings( float width, float height ) : volume( 50.0f ) {
    if ( !font.loadFromFile( "AcherusGrotesque-Regular.otf" ) ) {
        // Handle error
    }

    volumeText.setFont( font );
    volumeText.setString( "Volume" );
    volumeText.setCharacterSize( 40 );
    volumeText.setFillColor( sf::Color::White );
    volumeText.setPosition( sf::Vector2f( width / 2 - volumeText.getGlobalBounds().width / 2, height / 2 - volumeText.getGlobalBounds().height - 20 ) );

    volumeBar.setSize( sf::Vector2f( 200, 20 ) );
    volumeBar.setFillColor( sf::Color::White );
    volumeBar.setPosition( sf::Vector2f( width / 2 - volumeBar.getSize().x / 2, height / 2 ) );

    volumeIndicator.setSize( sf::Vector2f( 10, 40 ) );
    volumeIndicator.setFillColor( sf::Color::Red );
    volumeIndicator.setPosition( volumeBar.getPosition().x + ( volume / 100.0f ) * volumeBar.getSize().x - volumeIndicator.getSize().x / 2, volumeBar.getPosition().y - 10 );
}

void Settings::draw( sf::RenderWindow& window ) {
    window.draw( volumeText );
    window.draw( volumeBar );
    window.draw( volumeIndicator );
}

void Settings::handleEvent( sf::Event& event, sf::RenderWindow& window ) {
    if ( event.type == sf::Event::MouseButtonPressed ) {
        if ( event.mouseButton.button == sf::Mouse::Left ) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition( window );
            if ( volumeBar.getGlobalBounds().contains( static_cast< sf::Vector2f >( mousePosition ) ) ) {
                volume = ( mousePosition.x - volumeBar.getPosition().x ) / volumeBar.getSize().x * 100.0f;
                volumeIndicator.setPosition( volumeBar.getPosition().x + ( volume / 100.0f ) * volumeBar.getSize().x - volumeIndicator.getSize().x / 2, volumeBar.getPosition().y - 10 );
            }
        }
    }
}