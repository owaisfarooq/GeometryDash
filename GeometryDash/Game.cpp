#include "stats.h"
#include "main.h"

Game::Game( int windowWidth, int windowHeight, bool* pause ) {
    startTime = time( 0 );

    pausePtr = pause;
    *pausePtr = true;
    playerStartingPosition = sf::Vector2f( 100, windowHeight - 100 );
    obsticleStartingPosition = sf::Vector2f( windowWidth , windowHeight - 70 );

    player.setPointCount( 4 );
    player.setPoint( 0, sf::Vector2f( 0, 0 ) );
    player.setPoint( 1, sf::Vector2f( 50, 0 ) );
    player.setPoint( 2, sf::Vector2f( 50, 50 ) );
    player.setPoint( 3, sf::Vector2f( 0, 50 ) );
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

    startingText.setFont( font );
    startingText.setCharacterSize( 24 );
    startingText.setFillColor( sf::Color::White );
    startingText.setString("Press Space to start / resume\nPress P to pause\nPress ESC to go to menu\nPress R to restart.");
    float textWidth = startingText.getLocalBounds().width;
    float textHeight = startingText.getLocalBounds().height;
    startingText.setPosition( ( windowWidth - textWidth ) / 2, ( windowHeight - textHeight ) / 2 );


    JumpAudio.loadFromFile( "Resources/audio/jump.wav" );
    BonusAudio.loadFromFile( "Resources/audio/Bonus.wav" );
    GameOverAudio.loadFromFile( "Resources/audio/Game-Over.wav" );

    scoreCount = 0;
    jumpIncrement = 900.0f; // pixels per second
    maxJumpingHeight = 500.0f; // adjusted for higher jump
    isJumping = false;
    obstacleSpeedIncremenet = 50.0f; // pixels per second
    obstacleSpeed = 800.0f; // pixels per second, increased for faster movement

    backgroundTexture.loadFromFile( "Resources/images/Gamebackground.png" );
    backgroundSprite1.setTexture( backgroundTexture );
    backgroundSprite2.setTexture( backgroundTexture );
    backgroundSprite1.setPosition( 0, 0 );
    backgroundSprite2.setPosition( windowWidth, 0 );
    backgroundSpeed = 100.0f; // pixels per second



    updateScoreText();
}

void Game::update( float deltaTime ) {
    if ( isJumping ) {
        sf::Vector2f playerOldPosition = player.getPosition();
        float newY = playerOldPosition.y - jumpIncrement * deltaTime;

        if ( newY <= maxJumpingHeight ) {
            isJumping = false;
            newY = maxJumpingHeight;
        }
        player.setPosition( playerOldPosition.x, newY );
    } else {
        sf::Vector2f playerCurrentPosition = player.getPosition();

        if ( playerCurrentPosition.y < playerStartingPosition.y ) {
            float newY = playerCurrentPosition.y + jumpIncrement * deltaTime;
            if ( newY > playerStartingPosition.y ) {
                newY = playerStartingPosition.y;
            }
            player.setPosition( playerCurrentPosition.x, newY );
        }
    }

    if ( obstacle.getPosition().x < -100 ) {
        resetObsticlePosition();
    }

    
    if ( isPlayerTouchingObstacle() ) {
        player.setFillColor( sf::Color::Red );
        soundPlayer.setBuffer( GameOverAudio );
        soundPlayer.play();
        *pausePtr = true;

        updateStats();
        resetStats();

    } else {
        moveBackground( deltaTime );
        player.setFillColor( playerFillColor );
        scoreCount += 2.0f * deltaTime;
        if ( player.getPosition() == playerStartingPosition ) {
        }
    }

    if ( int( scoreCount ) % 25 == 0 && scoreCount >= 25 ) {
        soundPlayer.setBuffer( BonusAudio );
        soundPlayer.play();
        obstacleSpeed += 0.00005f;
    }

    sf::Vector2f obstacleOldPosition = obstacle.getPosition();
    obstacle.setPosition( obstacleOldPosition.x - obstacleSpeed * deltaTime, obstacleOldPosition.y );

    updateScoreText();
}

void Game::moveBackground(float deltaTime) {
    // Update the background position
    backgroundSprite1.move( -backgroundSpeed * deltaTime, 0 );
    backgroundSprite2.move( -backgroundSpeed * deltaTime, 0 );

    if ( backgroundSprite1.getPosition().x <= -backgroundSprite1.getGlobalBounds().width ) {
        backgroundSprite1.setPosition( backgroundSprite2.getPosition().x + backgroundSprite2.getGlobalBounds().width, 0 );
    }
    if ( backgroundSprite2.getPosition().x <= -backgroundSprite2.getGlobalBounds().width ) {
        backgroundSprite2.setPosition( backgroundSprite1.getPosition().x + backgroundSprite1.getGlobalBounds().width, 0 );
    }
}

bool Game::isPlayerTouchingObstacle() {
    // Use smaller bounding boxes for collision detection
    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect obstacleBounds = obstacle.getGlobalBounds();

    // Shrink the bounds by a small amount
    float playerSizeAdjustment = 0;
    float obsticleSizeAdjustment = 0;
    playerBounds.left += playerSizeAdjustment;
    playerBounds.top += playerSizeAdjustment;
    playerBounds.width -= playerSizeAdjustment * 2;
    playerBounds.height -= playerSizeAdjustment * 2;

    /*obstacleBounds.left += obsticleSizeAdjustment;*/
    obstacleBounds.left += 0;
    obstacleBounds.top += obsticleSizeAdjustment;
    obstacleBounds.width -= obsticleSizeAdjustment * 2;
    obstacleBounds.height -= obsticleSizeAdjustment * 2;

    return playerBounds.intersects( obstacleBounds );
}
void Game::reset() {
    startTime = time( 0 );
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

void Game::increaseObstacleSpeed() {
    obstacleSpeed += obstacleSpeedIncremenet;
}

void Game::decreaseObstacleSpeed() {
    if ( obstacleSpeed > obstacleSpeedIncremenet ) {
        obstacleSpeed -= obstacleSpeedIncremenet;
    }
}

void Game::setPlayerShape( const std::string& shape ) {
    if ( shape == "Rhombus" ) {
        player.setPointCount( 4 );
        player.setPoint( 0, sf::Vector2f( 25, 0 ) );
        player.setPoint( 1, sf::Vector2f( 50, 25 ) );
        player.setPoint( 2, sf::Vector2f( 25, 50 ) );
        player.setPoint( 3, sf::Vector2f( 0, 25 ) );
    } else if ( shape == "Diamond" ) {
        player.setPointCount( 4 );
        player.setPoint( 0, sf::Vector2f( 25, 0 ) );
        player.setPoint( 1, sf::Vector2f( 50, 25 ) );
        player.setPoint( 2, sf::Vector2f( 25, 50 ) );
        player.setPoint( 3, sf::Vector2f( 0, 25 ) );
    } else if ( shape == "Square" ) {
        player.setPointCount( 4 );
        player.setPoint( 0, sf::Vector2f( 0, 0 ) );
        player.setPoint( 1, sf::Vector2f( 50, 0 ) );
        player.setPoint( 2, sf::Vector2f( 50, 50 ) );
        player.setPoint( 3, sf::Vector2f( 0, 50 ) );
    }
}

void Game::setPlayerColor( sf::Color color ) {
    playerFillColor = color;
    player.setFillColor( playerFillColor );
}

void Game::draw( sf::RenderWindow& window ) {
    window.draw( backgroundSprite1 );
    window.draw( backgroundSprite2 );

    if ( ( *pausePtr ) ) {
        window.draw( startingText );
    }

    window.draw( player );
    window.draw( obstacle );
    window.draw( score );
}

void Game::updateStats() {
    int totalTimePlayed = difftime( time( 0 ), startTime );
    int score = static_cast< int > ( scoreCount );
    Stats::updateSessionStats( score, totalTimePlayed );
}

void Game::resetStats() {
    startTime = time( 0 );
    scoreCount = 0;
}

void Game::updateScoreText() {
    int scoreToDisplay = static_cast< int >( scoreCount );
    score.setString( "Score: " + std::to_string( scoreToDisplay ) );
}

void Game::jump() {
    if ( *pausePtr ) {
        return;
    }

    if ( !( player.getPosition().y == playerStartingPosition.y ) ) {
        return;
    }

    soundPlayer.setBuffer( JumpAudio );
    soundPlayer.play();
    isJumping = true;
}