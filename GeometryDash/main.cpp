#include "main.h"
#include "Menu.h"
#include "Stats.h"
#include "Settings.h"
#include "Instructions.h"
#include <SFML/System/Clock.hpp>
#include <ctime>

using namespace sf;

enum GameState {
    MENU,
    SETTINGS,
    INSTRUCTIONS,
    STATS,
    PLAYING
};

bool pause = false;

void handleMenuState( Event& event, GameState& gameState, Menu& menu, RenderWindow& window ) {
    if ( event.type == Event::MouseButtonPressed ) {
        if ( event.mouseButton.button == Mouse::Left ) {
            if ( menu.isPlayButtonPressed( Mouse::getPosition( window ) ) ) {
                gameState = GameState::PLAYING;
            } else if ( menu.isSettingsButtonPressed( Mouse::getPosition( window ) ) ) {
                gameState = GameState::SETTINGS;
            } else if ( menu.isInstructionsButtonPressed( Mouse::getPosition( window ) ) ) {
                gameState = GameState::INSTRUCTIONS;
            } else if ( menu.isStatsButtonPressed( Mouse::getPosition( window ) ) ) {
                gameState = GameState::STATS;
            }
        }
    }
}

void handlePlayingState( Event& event, GameState& gameState, Game& game ) {
    if ( event.type == Event::KeyPressed ) {
        handlePlayingState( event, gameState, game );
    }
}


int main() {
    int length = 800, width = 1000;
    RenderWindow window( VideoMode( width, length ), "Geometry Dash" );

    GameState gameState = GameState::MENU;
    Game game( width, length, &pause );
    Menu menu( width, length );
    Stats stats( width, length );
    Settings settings( width, length );
    Instructions instructions( width, length );

    Clock clock;
    const float timeStep = 1.0f / 60.0f; // 60 updates per second
    float accumulator = 0.0f;

    while ( window.isOpen() ) {
        Event event;
        while ( window.pollEvent( event ) ) {
            if ( event.type == Event::Closed ) {
                window.close();
            }

            if ( gameState == GameState::MENU ) {
                handleMenuState( event, gameState, menu, window );
                
            } else if ( gameState == GameState::SETTINGS ) {
                settings.handleEvent( event, window );
                if ( event.type == Event::KeyPressed && event.key.code == Keyboard::Escape ) {
                    gameState = GameState::MENU;
                }
            } else if ( gameState == GameState::INSTRUCTIONS ) {
                if ( event.type == Event::KeyPressed && event.key.code == Keyboard::Escape ) {
                    gameState = GameState::MENU;
                }
            } else if ( gameState == GameState::STATS ) {
                if ( event.type == Event::KeyPressed && event.key.code == Keyboard::Escape ) {
                    gameState = GameState::MENU;
                }
            } else if ( gameState == GameState::PLAYING ) {
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
                    if ( event.key.code == Keyboard::Escape && pause ) {
                        gameState = GameState::MENU;
                        //window.close();
                    }
                    if ( !pause ) {
                        if ( event.key.code == Keyboard::Space ) {
                            game.jump();
                        }
                        if ( event.key.code == Keyboard::Up ) {
                            game.increaseObstacleSpeed();
                        }
                        if ( event.key.code == Keyboard::Down ) {
                            game.decreaseObstacleSpeed();
                        }
                    }
                }
            }
        }

        float deltaTime = clock.restart().asSeconds();
        accumulator += deltaTime;

        while ( accumulator >= timeStep ) {
            if ( gameState == GameState::PLAYING && !pause ) {
                game.update( timeStep );
            }
            accumulator -= timeStep;
        }

        window.clear( Color::Black );

        if ( gameState == GameState::PLAYING ) {
            game.draw( window );
        } else if ( gameState == GameState::MENU ) {
            menu.draw( window );
        } else if ( gameState == GameState::SETTINGS ) {
            settings.draw( window );
        } else if ( gameState == GameState::INSTRUCTIONS ) {
            instructions.draw( window );
        } else if ( gameState == GameState::STATS ) {
            stats.draw( window );
        }


        window.display();
    }

    return 0;
}