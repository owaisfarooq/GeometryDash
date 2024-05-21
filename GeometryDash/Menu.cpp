// Menu.cpp
#include "Menu.h"

Menu::Menu( float width, float height ) {
    if ( !font.loadFromFile( "AcherusGrotesque-Regular.otf" ) ) {
        // Handle error
    }

    playButton.setFont( font );
    playButton.setString( "Play" );
    playButton.setCharacterSize( 40 );
    playButton.setFillColor( sf::Color::White );
    playButton.setPosition( sf::Vector2f( width / 2 - playButton.getGlobalBounds().width / 2, height / 2 - 150 ) );

    settingsButton.setFont( font );
    settingsButton.setString( "Settings" );
    settingsButton.setCharacterSize( 40 );
    settingsButton.setFillColor( sf::Color::White );
    settingsButton.setPosition( sf::Vector2f( width / 2 - settingsButton.getGlobalBounds().width / 2, height / 2 - 50 ) );

    instructionsButton.setFont( font );
    instructionsButton.setString( "Instructions" );
    instructionsButton.setCharacterSize( 40 );
    instructionsButton.setFillColor( sf::Color::White );
    instructionsButton.setPosition( sf::Vector2f( width / 2 - instructionsButton.getGlobalBounds().width / 2, height / 2 + 50 ) );

    statsButton.setFont( font );
    statsButton.setString( "Stats" );
    statsButton.setCharacterSize( 40 );
    statsButton.setFillColor( sf::Color::White );
    statsButton.setPosition( sf::Vector2f( width / 2 - statsButton.getGlobalBounds().width / 2, height / 2 + 150 ) );

    backgroundTexture.loadFromFile( "Resources/images/HomeBackground.jpg" );
    backgroundSprite.setTexture( backgroundTexture );
    backgroundSprite.setScale( 1.6, 1.75 );
}

void Menu::draw( sf::RenderWindow& window ) {
    window.draw( backgroundSprite );
    window.draw( playButton );
    window.draw( settingsButton );
    window.draw( instructionsButton );
    window.draw( statsButton );
}

bool Menu::isPlayButtonPressed( sf::Vector2i mousePosition ) {
    return playButton.getGlobalBounds().contains( static_cast< sf::Vector2f >( mousePosition ) );
}

bool Menu::isSettingsButtonPressed( sf::Vector2i mousePosition ) {
    return settingsButton.getGlobalBounds().contains( static_cast< sf::Vector2f >( mousePosition ) );
}

bool Menu::isInstructionsButtonPressed( sf::Vector2i mousePosition ) {
    return instructionsButton.getGlobalBounds().contains( static_cast< sf::Vector2f >( mousePosition ) );
}

bool Menu::isStatsButtonPressed( sf::Vector2i mousePosition ) {
    return statsButton.getGlobalBounds().contains( static_cast< sf::Vector2f >( mousePosition ) );
}