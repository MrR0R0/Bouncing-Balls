#ifndef BOUNCINGBALLS_UTILITY_H
#define BOUNCINGBALLS_UTILITY_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <random>
#include <chrono>
#include <thread>
#include <cmath>


enum menuModes {
    Main, Modes, Settings, Sound, Score, Play, End, Pause
};
enum gameModes {
    Infinity, Random, Countdown
};
enum ballThemes {
    Bowling, Glass, Marble
};
enum endMenuMode {
    Write, Idle
};
enum endGameStatus {
    Won, Lost
};

std::vector<int> decodeColor(int c);

void generateRandomMap();

bool inScreen(double &y);

void setRectWithCenter(SDL_Rect &rect, double x, double y, double w, double h);

void setRectWithCorner(SDL_Rect &rect, double x, double y, double w, double h);

bool pointInRect(SDL_Rect rect, int &x, int &y);

bool haveTheSameColor(int color1, int color2);

#endif //BOUNCINGBALLS_UTILITY_H
