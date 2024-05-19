// Game.h
#ifndef GAME_H
#define GAME_H

#include "main.h"

class Game {
public:
    Game( int windowWidth, int windowHeight, bool* pause );
    void update( float deltaTime );
    void draw( sf::RenderWindow& window );
    void jump();
    void reset();
    void increaseObstacleSpeed();
    void decreaseObstacleSpeed();
    bool isPlayerTouchingObstacle();
private:
    sf::RectangleShape player;
    sf::RectangleShape obstacle;
    sf::Text score;
    sf::Text startingText;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite1;
    sf::Sprite backgroundSprite2;
    sf::Vector2f playerStartingPosition;
    sf::Vector2f obstacleStartingPosition;
    sf::SoundBuffer JumpAudio;
    sf::SoundBuffer GameOverAudio;
    sf::SoundBuffer BonusAudio;
    sf::Sound soundPlayer;
    time_t startTime;
    float backgroundSpeed;

    float backgroundPosition;
    float maxJumpingHeight;
    float jumpIncrement;
    float obstacleSpeed;
    float obstacleSpeedIncrement;
    float scoreCount;

    bool* pausePtr;
    bool isJumping;

    void resetObstaclePosition();
    void resetPlayerPosition();
    void updateScoreText();
    void resetStats();
    void updateStats();
    void moveBackground(float deltaTime);
};

#endif // GAME_H