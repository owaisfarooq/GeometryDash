#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "Game.h"
#include <string.h>
#include <ctime>
enum GameState {
    MENU,
    SETTINGS,
    INSTRUCTIONS,
    STATS,
    PLAYING
};