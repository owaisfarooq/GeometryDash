// Game.h
#ifndef GAME_H
#define GAME_H

#include "main.h"

class Game {
public:
    Game( int windowWidth, int windowHeight, bool* pause );
    void update();
    void draw( sf::RenderWindow& window );
    void jump();
    void reset();
    void increaseObsticleSpeed();
    void decreaseObsticleSpeed();
private:
    sf::RectangleShape player;
    sf::RectangleShape obstacle;
    sf::Text score;
    sf::Font font;
    sf::Vector2f playerStartingPosition;
    sf::Vector2f obsticleStartingPosition;
    sf::SoundBuffer JumpAudio;
    sf::SoundBuffer GameOverAudio;
    sf::SoundBuffer BonusAudio;
    sf::Sound soundPlayer;
    time_t startTime;
    bool* pausePtr;
    float maxJumpingHeight;
    float jumpIncrement;
    float obstacleSpeed;
    float obstacleSpeedIncremenet;
    float scoreCount;
    bool isJumping;
    void updateScoreText();
    void resetObsticlePosition();
    void resetPlayerPosition();
};

#endif // GAME_H
