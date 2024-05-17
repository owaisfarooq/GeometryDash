#include "main.h"

Game::Game( int windowWidth, int windowHeight, bool* pause ) {
    startTime = time( 0 );

    pausePtr = pause;
    playerStartingPosition = sf::Vector2f( 100, windowHeight - 200 );
    obsticleStartingPosition = sf::Vector2f( windowWidth - 100, windowHeight - 70 );

    player.setSize( sf::Vector2f( 50, 50 ) );
    player.setFillColor( sf::Color::Green );
    player.setPosition( playerStartingPosition );

    obstacle.setSize( sf::Vector2f( 30, 20 ) );
    obstacle.setFillColor( sf::Color::Red );
    obstacle.setPosition( obsticleStartingPosition );

    font.loadFromFile( "AcherusGrotesque-Regular.otf" );
    score.setFont( font );
    score.setCharacterSize( 24 );
    score.setFillColor( sf::Color::White );
    score.setPosition( 100, 100 );

    JumpAudio.loadFromFile( "Resources/audio/jump.wav" );
    BonusAudio.loadFromFile( "Resources/audio/Bonus.wav" );
    GameOverAudio.loadFromFile( "Resources/audio/Game-Over.wav" );
    //soundPlayer.setBuffer( JumpAudio );
    scoreCount = 0;
    jumpIncrement = 0.75;
    maxJumpingHeight = 350;
    isJumping = false;
    obstacleSpeedIncremenet = 0.2;
    obstacleSpeed = 0.75;

    updateScoreText();
}

void Game::update() {
    int timeSpent = time( 0 ) - startTime;
    if ( isJumping ) {
        // going up
        sf::Vector2f playerOldPosition = player.getPosition();
        
        if ( maxJumpingHeight > playerOldPosition.y ) {
            isJumping = false;
        };

        player.setPosition( playerOldPosition.x, playerOldPosition.y - jumpIncrement );
    } else {
        // going back down after going up
        sf::Vector2f playerCurrentPosition = player.getPosition();

        if ( playerCurrentPosition.y < playerStartingPosition.y ) {
            player.setPosition( playerCurrentPosition.x, playerCurrentPosition.y + jumpIncrement );
        }
    }

    if ( obstacle.getPosition().x < -100 ) {
            resetObsticlePosition();
    }

    if ( player.getGlobalBounds().intersects( obstacle.getGlobalBounds() ) ) {
        player.setFillColor( sf::Color::Red );
        soundPlayer.setBuffer( GameOverAudio );
        soundPlayer.play();
        *pausePtr = true;
    } else {
        player.setFillColor( sf::Color::Green );
        if ( player.getPosition() == playerStartingPosition ) {
            scoreCount += 0.002;
        }
    }
    if ( int( scoreCount ) % 25 == 0 && scoreCount >= 25 ) {
        soundPlayer.setBuffer( BonusAudio );
        soundPlayer.play();
        obstacleSpeed += 0.00005;
    }
    sf::Vector2f obstacleOldPosition = obstacle.getPosition();
    obstacle.setPosition( obstacleOldPosition.x - obstacleSpeed, obstacleOldPosition.y );
    updateScoreText();
}

void Game::reset() { 
    if ( *pausePtr == true ) {
        *pausePtr = false;
    }
    scoreCount = 0;
    resetObsticlePosition();
    resetPlayerPosition();
}

void Game::resetObsticlePosition() {
    obstacle.setPosition( obsticleStartingPosition );
}
void Game::resetPlayerPosition() {
    player.setPosition( playerStartingPosition );
}

void Game::increaseObsticleSpeed() { 
    if ( obstacleSpeed < 1 ) {
        obstacleSpeed += obstacleSpeedIncremenet;
    }
}
void Game::decreaseObsticleSpeed() { 
    if ( obstacleSpeed > obstacleSpeedIncremenet ) {
        obstacleSpeed -= obstacleSpeedIncremenet;
    }
}

void Game::draw( sf::RenderWindow& window ) {
    window.draw( player );
    window.draw( obstacle );
    window.draw( score );
}

void Game::updateScoreText() {
    int scoreToDisplay = scoreCount;
    score.setString( "Score: " + std::to_string( scoreToDisplay ) );
}

void Game::jump() {
    if ( player.getPosition().y == playerStartingPosition.y ) {
        soundPlayer.setBuffer( JumpAudio );
        soundPlayer.play();
        isJumping = true;
    }
}