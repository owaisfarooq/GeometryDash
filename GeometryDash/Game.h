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
    void toggleGodMode();
    bool isPlayerTouchingObstacle();
    void setPlayerShape( const std::string& shape );
    void setPlayerColor( sf::Color color );
private:
    //sf::RectangleShape player;
    sf::ConvexShape player;

    sf::RectangleShape obstacleRect;
    sf::CircleShape obstacleCircle;
    sf::ConvexShape obstacleTriangle;
    sf::Shape* currentObstacle; // Pointer to the current obstacle shape

    void setRandomObstacleShape();


    sf::Text score;
    sf::Text instructionsText;
    sf::Text GODMODETEXT;
    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite1;
    sf::Sprite backgroundSprite2;
    sf::Vector2f playerStartingPosition;
    sf::Vector2f obsticleStartingPosition;
    sf::SoundBuffer JumpAudio;
    sf::SoundBuffer GameOverAudio;
    sf::SoundBuffer BonusAudio;
    sf::Sound soundPlayer;
    time_t startTime;
    sf::Color playerFillColor;
    float backgroundSpeed;
    float backgroundPosition;
    float maxJumpingHeight;
    float jumpIncrement;
    float initialObstacleSpeed;
    float obstacleSpeed;
    float obstacleSpeedIncrement;
    float scoreCount;
    int lastBonusAtScore;

    bool isGodModeEnabled;
    bool* pausePtr;
    bool isJumping;

    void resetObsticlePosition();
    void resetPlayerPosition();
    void updateScoreText();
    void resetStats();
    void updateStats();
    void moveBackground(float deltaTime);
    
};

#endif // GAME_H