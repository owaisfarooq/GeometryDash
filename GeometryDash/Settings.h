#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>

class Settings {
public:
    enum class PlayerShape {
        Rectangle,
        Triangle,
        Diamond,
        Rhombus
    };

    Settings( float width, float height );
    void draw( sf::RenderWindow& window );
    void handleEvent( sf::Event& event, sf::RenderWindow& window );

    PlayerShape getPlayerShape() const;

private:
    sf::Font font;
    sf::Text volumeText;
    sf::RectangleShape volumeBar;
    sf::RectangleShape volumeIndicator;
    float volume;

    sf::Text shapeText;
    sf::Text rectangleOption;
    sf::Text triangleOption;
    sf::Text diamondOption;
    sf::Text rhombusOption;

    PlayerShape playerShape;

    void updateShapeSelection( sf::Vector2i mousePosition );
};

#endif // SETTINGS_H
