#include "main.h"
#include "Menu.h"
#include "Stats.h"
#include "Settings.h"
#include "Instructions.h"
#include <SFML/System/Clock.hpp>
#include <ctime>

using namespace sf;

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

void applySettings( Game& game, const Settings& settings ) {
    game.setPlayerShape( settings.getSelectedShape() );
    game.setPlayerColor( settings.getSelectedColor() );
}

int main() {
    int length = 700, width = 1400;
    RenderWindow window( VideoMode( width, length ), "Geometry Dash" );

    GameState gameState = GameState::MENU;
    Game game( width, length, &pause );
    Menu menu( width, length );
    Stats stats( width, length );
    Settings settings( width, length );
    Instructions instructions( width, length );

    Clock clock;
    const float timeStep = 1.0f / 60.0f; // 60 updates per secondi
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
                    applySettings( game, settings );
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
                    bool isLost = game.isPlayerTouchingObstacle();
                    if ( event.key.code == sf::Keyboard::P && !isLost ) {
                        pause = true;
                    }
                    if ( event.key.code == sf::Keyboard::G ) {
                        game.toggleGodMode();
                    }
                    if ( event.key.code == sf::Keyboard::R && isLost ) {
                        game.reset();
                    }
                    if ( event.key.code == sf::Keyboard::Space && !isLost ) {
                        pause = false;
                    }
                    if ( event.key.code == sf::Keyboard::Escape && ( pause ) ) {
                        gameState = GameState::MENU;
                    }
                    if ( event.key.code == sf::Keyboard::Space ) {
                        game.jump();
                    }
                    if ( !pause ) {
                        if ( event.key.code == sf::Keyboard::Space ) {
                            game.jump();
                        }
                        if ( event.key.code == sf::Keyboard::Up ) {
                            game.increaseObstacleSpeed();
                        }
                        if ( event.key.code == sf::Keyboard::Down ) {
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