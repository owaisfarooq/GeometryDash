// Stats.h
#ifndef STATS_H
#define STATS_H

#include <SFML/Graphics.hpp>

class Stats {
public:
    Stats( float width, float height );
    void draw( sf::RenderWindow& window );

    static void updateSessionStats( int scoreThisSession, int timePlayed );
private:
    void loadStatsFromFile( );
    int highScoreFromFile, totalTimePlayedFromFile, totalScoreFromFile, obstaclesHitFromFile;
    sf::Font font;
    sf::Text statsText;
};

#endif // STATS_H