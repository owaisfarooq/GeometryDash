#include "stats.h"
#include "main.h"
#include <cstdlib>
#include <ctime>

Game::Game( int windowWidth, int windowHeight, bool* pause ) {
    startTime = time( 0 );
    isGodModeEnabled = false;
    srand( static_cast< unsigned int >( time( 0 ) ) ); // Initialize random seed
    setRandomObstacleShape();
    lastBonusAtScore = 0;
    pausePtr = pause;
    *pausePtr = true;
    
    font.loadFromFile( "AcherusGrotesque-Regular.otf" );

#pragma region Player settings
    player.setPointCount( 4 );
    player.setPoint( 0, sf::Vector2f( 0, 0 ) );
    player.setPoint( 1, sf::Vector2f( 50, 0 ) );
    player.setPoint( 2, sf::Vector2f( 50, 50 ) );
    player.setPoint( 3, sf::Vector2f( 0, 50 ) );
    playerFillColor = sf::Color::Green;
    player.setFillColor( playerFillColor );
    playerStartingPosition = sf::Vector2f( 100, windowHeight - 100 );
    player.setPosition( playerStartingPosition );
#pragma endregion

#pragma region Obstacle settings
    // Initialize random seed for obstacle shapes
    srand( static_cast< unsigned int >( time( 0 ) ) );
    // Initialize obstacle shapes
    obsticleStartingPosition = sf::Vector2f( windowWidth, windowHeight - 80 );
    setRandomObstacleShape();
#pragma endregion
    
#pragma region Score Heading settings
    score.setFont( font );
    score.setCharacterSize( 24 );
    score.setFillColor( sf::Color::White );
    score.setPosition( 100, 100 );
#pragma endregion
    
#pragma region instructions Text
    instructionsText.setFont( font );
    instructionsText.setCharacterSize( 24 );
    instructionsText.setFillColor( sf::Color::White );
    instructionsText.setString("Press Space to start / resume\nPress P to pause\nPress ESC to go to menu\nPress R to restart.");
    float textWidth = instructionsText.getLocalBounds().width;
    float textHeight = instructionsText.getLocalBounds().height;
    instructionsText.setPosition( ( windowWidth - textWidth ) / 2, ( windowHeight - textHeight ) / 2 );
#pragma endregion

#pragma region Audio Loading
    JumpAudio.loadFromFile( "Resources/audio/jump.wav" );
    BonusAudio.loadFromFile( "Resources/audio/Bonus.wav" );
    GameOverAudio.loadFromFile( "Resources/audio/Game-Over.wav" );
#pragma endregion

#pragma region Initalizing / setting values
    scoreCount = 0;
    jumpIncrement = 900.0f;
    maxJumpingHeight = 500.0f;
    isJumping = false;
    initialObstacleSpeed = 800.0f;
    obstacleSpeed = initialObstacleSpeed;
    obstacleSpeedIncrement = 200.0f;
#pragma endregion

#pragma region Background Settings
    backgroundTexture.loadFromFile( "Resources/images/Gamebackground.png" );
    backgroundSprite1.setTexture( backgroundTexture );
    backgroundSprite2.setTexture( backgroundTexture );
    backgroundSprite1.setPosition( 0, 0 );
    backgroundSprite2.setPosition( windowWidth, 0 );
    backgroundSpeed = 100.0f;
#pragma endregion

    updateScoreText();
}
void Game::setRandomObstacleShape() {
    int shapeType = rand() % 3; // Random number between 0 and 2

    switch ( shapeType ) {
    case 0:
        currentObstacle = &obstacleRect;
        obstacleRect.setSize( sf::Vector2f( 30, 20 ) );
        obstacleRect.setFillColor( sf::Color::Red );
        obstacleRect.setPosition( obsticleStartingPosition );
        break;
    case 1:
        currentObstacle = &obstacleCircle;
        obstacleCircle.setRadius( 15 );
        obstacleCircle.setFillColor( sf::Color::Magenta );
        obstacleCircle.setPosition( obsticleStartingPosition );
        break;
    case 2:
        currentObstacle = &obstacleTriangle;
        obstacleTriangle.setPointCount( 3 );
        obstacleTriangle.setPoint( 0, sf::Vector2f( 0, 30 ) );
        obstacleTriangle.setPoint( 1, sf::Vector2f( 30, 30 ) );
        obstacleTriangle.setPoint( 2, sf::Vector2f( 15, 0 ) );
        obstacleTriangle.setFillColor( sf::Color::Yellow );
        obstacleTriangle.setPosition( obsticleStartingPosition );
        break;
    }
}

void Game::update( float deltaTime ) {
    // Checking if user has lost ( by checking if user is touching obstacle )
    if ( isPlayerTouchingObstacle() ) {
        player.setFillColor( sf::Color::Red );
        soundPlayer.setBuffer( GameOverAudio );
        soundPlayer.play();
        *pausePtr = true;

        updateStats();
        resetStats();

    } else {
        moveBackground( deltaTime ); // for the background moving animation
        player.setFillColor( playerFillColor );
        scoreCount += 2.0f * deltaTime; // adding score
    }

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

    if ( currentObstacle->getPosition().x < -100 ) {
        resetObsticlePosition();
    }

    if ( int( scoreCount ) % 25 == 0 && scoreCount >= lastBonusAtScore + 25 ) {
        lastBonusAtScore = scoreCount;
        soundPlayer.setBuffer( BonusAudio );
        soundPlayer.play();
        increaseObstacleSpeed();
    }

    sf::Vector2f obstacleOldPosition = currentObstacle->getPosition();
    currentObstacle->move( -obstacleSpeed * deltaTime, 0 );


    updateScoreText();
}

void Game::moveBackground(float deltaTime) {
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
    if ( isGodModeEnabled ) return false;
    sf::FloatRect playerBounds = player.getGlobalBounds();
    sf::FloatRect obstacleBounds = currentObstacle->getGlobalBounds();
    return playerBounds.intersects( obstacleBounds );
}


void Game::reset() {
    startTime = time( 0 );
    scoreCount = 0;
    obstacleSpeed = initialObstacleSpeed;
    resetObsticlePosition();
    resetPlayerPosition();
}
void Game::toggleGodMode() {
    isGodModeEnabled = !isGodModeEnabled;
}
void Game::resetObsticlePosition() {
    setRandomObstacleShape();
}

void Game::resetPlayerPosition() {
    player.setPosition( playerStartingPosition );
}

void Game::increaseObstacleSpeed() {
    obstacleSpeed += obstacleSpeedIncrement;
}

void Game::decreaseObstacleSpeed() {
    if ( obstacleSpeed > obstacleSpeedIncrement ) {
        obstacleSpeed -= obstacleSpeedIncrement;
    }
}

void Game::setPlayerShape( const std::string& shape ) {
    if ( shape == "Circle" ) {
        player.setPointCount( 30 ); // Adjust the number of points for a smoother circle
        float radius = 25; // Adjust the radius as needed
        for ( int i = 0; i < 30; ++i ) {
            float angle = i * 2 * 3.14159 / 30;
            player.setPoint( i, sf::Vector2f( 25 + radius * std::cos( angle ), 25 + radius * std::sin( angle ) ) );
        }
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
        window.draw( instructionsText );
    }

    window.draw( player );
    window.draw( *currentObstacle );
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