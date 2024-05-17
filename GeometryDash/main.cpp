#include "main.h"

using namespace sf;
bool pause = false;

int main() {
    int length = 800, width = 1000;
    RenderWindow window( VideoMode( width, length), "Geometry Dash" );

    Game game( width, length, &pause );
    while ( window.isOpen() ) {
        Event event;
        while ( window.pollEvent( event ) ) {
            if ( event.type == Event::Closed ) {
                window.close();
            }

            if ( event.type == Event::KeyPressed ) {
                if ( event.key.code == Keyboard::Backspace ) {
                    std::cout << "DEBUG BREAK";
                }
                if ( event.key.code == Keyboard::P ) {
                    pause = !pause;
                }
                if ( event.key.code == Keyboard::R ) {
                    game.reset();
                }
                if ( event.key.code == Keyboard::Escape ) {
                    window.close();
                }
                if ( !pause ) {
                    
                    if ( event.key.code == Keyboard::Space ) {
                        game.jump();
                    }
                    if ( event.key.code == Keyboard::Up ) {
                        game.increaseObsticleSpeed();
                    }
                    if ( event.key.code == Keyboard::Down ) {
                        game.decreaseObsticleSpeed();
                    }
                }
            }
        }
        if ( !pause ) {
            game.update();

            window.clear( Color::Black );
            game.draw( window );
            window.display();
        }
	}
	return 0;
}