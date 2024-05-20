// Menu.h
#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

class Menu {
public:
    Menu( float width, float height );
    void draw( sf::RenderWindow& window );
    bool isPlayButtonPressed( sf::Vector2i mousePosition );
    bool isSettingsButtonPressed( sf::Vector2i mousePosition );
    bool isInstructionsButtonPressed( sf::Vector2i mousePosition );
    bool isStatsButtonPressed( sf::Vector2i mousePosition );
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

private:
    sf::Font font;
    sf::Text playButton;
    sf::Text settingsButton;
    sf::Text instructionsButton;
    sf::Text statsButton;
};

#endif // MENU_H
