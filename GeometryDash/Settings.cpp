#include "Settings.h"

Settings::Settings( float width, float height ) : volume( 50.0f ), selectedShapeIndex( 2 ), selectedColorIndex( 0 ) {
    if ( !font.loadFromFile( "AcherusGrotesque-Regular.otf" ) ) {
        // Handle error
    }

    volumeText.setString( "Volume" );
    volumeText.setFont( font );
    volumeText.setCharacterSize( 40 );
    volumeText.setFillColor( sf::Color::White );
    volumeText.setPosition( sf::Vector2f( width / 2 - volumeText.getGlobalBounds().width / 2, height / 2 - volumeText.getGlobalBounds().height - 120 ) );

    volumeBar.setSize( sf::Vector2f( 200, 20 ) );
    volumeBar.setFillColor( sf::Color::White );
    volumeBar.setPosition( sf::Vector2f( width / 2 - volumeBar.getSize().x / 2, height / 2 - 100 ) );

    volumeIndicator.setSize( sf::Vector2f( 10, 40 ) );
    volumeIndicator.setFillColor( sf::Color::Red );
    volumeIndicator.setPosition( volumeBar.getPosition().x + ( volume / 100.0f ) * volumeBar.getSize().x - volumeIndicator.getSize().x / 2, volumeBar.getPosition().y - 10 );

    shapeText.setFont( font );
    shapeText.setString( "Shape" );
    shapeText.setCharacterSize( 40 );
    shapeText.setFillColor( sf::Color::White );
    shapeText.setPosition( sf::Vector2f( width / 2 - shapeText.getGlobalBounds().width / 2, height / 2 - 60 ) );

    std::vector<std::string> shapes = { "Circle", "Diamond", "Square" };
    shapeOptions.clear();
    for ( int i = 0; i < shapes.size(); ++i ) {
        sf::Text shapeOption;
        shapeOption.setFont( font );
        shapeOption.setString( shapes [ i ] );
        shapeOption.setCharacterSize( 30 );
        shapeOption.setFillColor( i == selectedShapeIndex ? sf::Color::Red : sf::Color::White );
        shapeOptions.push_back( shapeOption );
    }
    updateShapeSelection( width, height );

    colorText.setFont( font );
    colorText.setString( "Color" );
    colorText.setCharacterSize( 40 );
    colorText.setFillColor( sf::Color::White );
    colorText.setPosition( sf::Vector2f( width / 2 - colorText.getGlobalBounds().width / 2, height / 2 + 120 ) );

    std::vector<sf::Color> colors = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow };
    colorOptions.clear();
    for ( int i = 0; i < colors.size(); ++i ) {
        sf::RectangleShape colorOption;
        colorOption.setSize( sf::Vector2f( 40, 40 ) );
        colorOption.setFillColor( colors [ i ] );
        colorOptions.push_back( colorOption );
    }
    backgroundTexture.loadFromFile( "Resources/images/Gamebackground.png" );
    backgroundSprite.setTexture( backgroundTexture );
    updateColorSelection( width, height );
}

void Settings::draw( sf::RenderWindow& window ) {
    window.draw( backgroundSprite );
    window.draw( volumeText );
    window.draw( volumeBar );
    window.draw( volumeIndicator );
    window.draw( shapeText );
    for ( const auto& shapeOption : shapeOptions ) {
        window.draw( shapeOption );
    }
    window.draw( colorText );
    for ( const auto& colorOption : colorOptions ) {
        window.draw( colorOption );
    }
}

void Settings::handleEvent( sf::Event& event, sf::RenderWindow& window ) {
    if ( event.type == sf::Event::MouseButtonPressed ) {
        if ( event.mouseButton.button == sf::Mouse::Left ) {
            sf::Vector2i mousePosition = sf::Mouse::getPosition( window );
            if ( volumeBar.getGlobalBounds().contains( static_cast< sf::Vector2f >( mousePosition ) ) ) {
                volume = ( mousePosition.x - volumeBar.getPosition().x ) / volumeBar.getSize().x * 100.0f;
                volumeIndicator.setPosition( volumeBar.getPosition().x + ( volume / 100.0f ) * volumeBar.getSize().x - volumeIndicator.getSize().x / 2, volumeBar.getPosition().y - 10 );
            }
            for ( int i = 0; i < shapeOptions.size(); ++i ) {
                if ( shapeOptions [ i ].getGlobalBounds().contains( static_cast< sf::Vector2f >( mousePosition ) ) ) {
                    selectedShapeIndex = i;
                    updateShapeSelection( window.getSize().x, window.getSize().y );
                }
            }
            for ( int i = 0; i < colorOptions.size(); ++i ) {
                if ( colorOptions [ i ].getGlobalBounds().contains( static_cast< sf::Vector2f >( mousePosition ) ) ) {
                    selectedColorIndex = i;
                    updateColorSelection( window.getSize().x, window.getSize().y );
                }
            }
        }
    }
}

void Settings::updateShapeSelection( float width, float height ) {
    for ( int i = 0; i < shapeOptions.size(); ++i ) {
        shapeOptions [ i ].setFillColor( i == selectedShapeIndex ? sf::Color::Red : sf::Color::White );
        shapeOptions [ i ].setPosition( sf::Vector2f( width / 2 - shapeOptions [ i ].getGlobalBounds().width / 2, height / 2 + i * 40 ) );
    }
}

void Settings::updateColorSelection( float width, float height ) {
    for ( int i = 0; i < colorOptions.size(); ++i ) {
        colorOptions [ i ].setOutlineThickness( i == selectedColorIndex ? 5 : 0 );
        colorOptions [ i ].setOutlineColor( sf::Color::White );
        colorOptions [ i ].setPosition( sf::Vector2f( width / 2 - ( colorOptions.size() * 50 ) / 2 + i * 50, height / 2 + 180 ) );
    }
}

sf::Color Settings::getSelectedColor() const {
    return colorOptions [ selectedColorIndex ].getFillColor();
}

std::string Settings::getSelectedShape() const {
    return shapeOptions [ selectedShapeIndex ].getString();
}