// Instructions.h
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <SFML/Graphics.hpp>

class Instructions {
public:
    Instructions( float width, float height );
    void draw( sf::RenderWindow& window );
    void handleEvent( sf::Event& event, sf::RenderWindow& window );

private:
    sf::Font font;
    sf::Text instructionsText;
};

#endif // INSTRUCTIONS_H
