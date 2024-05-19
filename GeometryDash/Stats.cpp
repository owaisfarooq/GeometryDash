// Stats.cpp
#include <fstream>
#include "Stats.h"

Stats::Stats( float width, float height ) {
    if ( !font.loadFromFile( "AcherusGrotesque-Regular.otf" ) ) {
        // Handle error
    }
    highScoreFromFile = 0;
    totalTimePlayedFromFile = 0;
    totalScoreFromFile = 0;
    obstaclesHitFromFile = 0;
    loadStatsFromFile();
    statsText.setFont( font );
    statsText.setCharacterSize( 24 );
    statsText.setFillColor( sf::Color::White );
    statsText.setPosition( width / 10, height / 10 );
}
void Stats::loadStatsFromFile() {
    std::ifstream inFile( "score.txt" );
    inFile >> highScoreFromFile >> totalTimePlayedFromFile >> totalScoreFromFile >> obstaclesHitFromFile;
    inFile.close();
    
    std::string statsStr = "HighScore: " + std::to_string( highScoreFromFile ) + "\n\n\n";
    
    if ( totalTimePlayedFromFile > 60 ) {
        int minutes = totalTimePlayedFromFile / 60;
        int seconds = totalTimePlayedFromFile%60;
        statsStr += "TotalTimePlayed: " + std::to_string( minutes ) + "m " + std::to_string( seconds ) + "s " + "\n\n\n";
    } else {
        statsStr += "TotalTimePlayed: "  + std::to_string( totalTimePlayedFromFile ) + "s " + "\n\n\n";
    }
    
    statsStr += "TotalScore: " + std::to_string( totalScoreFromFile ) + "\n\n\n";
    statsStr += "NumberOfObstaclesHit: " + std::to_string( obstaclesHitFromFile ) + "\n\n\n";
    statsText.setString( statsStr );
}
void Stats::updateSessionStats( int scoreThisSession, int timePlayed ) {
    // Read stats from file
    std::ifstream inFile( "score.txt" );
    int highScoreFromFile = 0, totalTimePlayedFromFile = 0, totalScoreFromFile = 0, obstaclesHitFromFile = 0;
    inFile >> highScoreFromFile >> totalTimePlayedFromFile >> totalScoreFromFile >> obstaclesHitFromFile;
    inFile.close();

    // Update stats
    totalScoreFromFile += scoreThisSession;
    if ( highScoreFromFile < scoreThisSession ) {
        highScoreFromFile = scoreThisSession;
    }
    totalTimePlayedFromFile += timePlayed;
    obstaclesHitFromFile++;

    // Write updated stats to file
    std::ofstream outFile( "score.txt" );
    outFile << highScoreFromFile << " " << totalTimePlayedFromFile << " " << totalScoreFromFile << " " << obstaclesHitFromFile;
    outFile.close();
}

void Stats::draw( sf::RenderWindow& window ) {
    loadStatsFromFile();
    window.draw( statsText );
}