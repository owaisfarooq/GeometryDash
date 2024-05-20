#ifndef SETTINGS_H
#define SETTINGS_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Settings {
public:
    Settings( float width, float height );

    void draw( sf::RenderWindow& window );
    void handleEvent( sf::Event& event, sf::RenderWindow& window );

    sf::Color getSelectedColor() const;
    std::string getSelectedShape() const;

private:
    sf::Font font;
    sf::Text volumeText;
    sf::RectangleShape volumeBar;
    sf::RectangleShape volumeIndicator;
    float volume;

    sf::Text shapeText;
    std::vector<sf::Text> shapeOptions;
    int selectedShapeIndex;

    sf::Text colorText;
    std::vector<sf::RectangleShape> colorOptions;
    int selectedColorIndex;

    void updateShapeSelection( float width, float height );
    void updateColorSelection( float width, float height );
};

#endif // SETTINGS_H
