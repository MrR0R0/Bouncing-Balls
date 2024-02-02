#include "Ball.h"
#include "TextureManager.h"
#include "Paths.h"

int Ball::cnst = 8;
SDL_Texture* Ball::lockPic;
SDL_Rect cellRect;

Ball::Ball(int c, double x, double y, double vx, double vy){
    color = c;
    x_cent = x;
    y_cent = y;
    vx_cent = vx;
    vy_cent = vy;
    std::string path, child;
    switch (color%32) {
        case 1:
            child = redBallPicPath;
            break;
        case 2:
            child = greenBallPicPath;
            break;
        case 4:
            child = blueBallPicPath;
            break;
        case 8:
            child = yellowBallPicPath;
            break;
        case 16:
            child = purpleBallPicPath;
            break;
        case 3:
            child = redGreenBallPicPath;
            break;
        case 5:
            child = redBlueBallPicPath;
            break;
        case 9:
            child = redYellowBallPicPath;
            break;
        case 17:
            child = redPurpleBallPicPath;
            break;
        case 6:
            child = greenBlueBallPicPath;
            break;
        case 10:
            child = greenYellowBallPicPath;
            break;
        case 18:
            child = greenPurpleBallPicPath;
            break;
        case 12:
            child = blueYellowBallPicPath;
            break;
        case 20:
            child = bluePurpleBallPicPath;
            break;
        case 24:
            child = yellowPurpleBallPicPath;
            break;
        default:
            break;
    }

    switch (Game::ballTheme){
        case Glass:
            path = "..\\assets\\theme1";
            break;
        case Marble:
            path = "..\\assets\\theme2";
            break;
        case Bowling:
            path = "..\\assets\\theme3";
            break;
    }
    if(color>32){
        lockPic = TextureManager::LoadTexture(lockPicPath);
    }
    path += child;
    ballPic = TextureManager::LoadTexture(path.c_str());
}

void Ball::render(){
    setRectWithCenter(ballRect, x_cent, y_cent, 60 + cnst, 60 + cnst);
    SDL_RenderCopy(Game::renderer, ballPic, nullptr, &ballRect);
    if(color>32){
        SDL_RenderCopy(Game::renderer, lockPic, nullptr, &ballRect);
    }
}

void Ball::update(double acceleration){
    vy_cent = acceleration + vy_cent < 20 ? acceleration + vy_cent : 20;
    x_cent += vx_cent;
    y_cent += vy_cent;
}

bool Ball::collisionWithCell(double xCentCell, double yCentCell){
    setRectWithCenter(cellRect, xCentCell, yCentCell, 60+cnst, 60+cnst);
    return SDL_HasIntersection(&cellRect, &ballRect);
}

bool Ball::hitVerticalEdges() const{
    if(x_cent + vx_cent >= 600 - 30 - (int)(cnst/2))
        return true;
    if(x_cent + vx_cent <= 30 + (int)(cnst/2))
        return true;
    return false;
}

void Ball::bounce(){
    vx_cent *= -1;
}

bool Ball::outOfScreen() const{
    if(x_cent < -40 || x_cent > 640)
        return true;
    if(y_cent < -40 || y_cent > 840)
        return true;
    return false;
}

std::vector<int> Ball::decodeColor(int c){
    std::set<int> colors = {1, 2, 4, 8, 16};
    if(colors.find(c) != colors.end())
        return {c, -1};

    for(int c1=1; c1<=c/2+1; c1*=2){
        if(colors.find(c - c1) != colors.end()){
            return {c1, c-c1};
        }
    }
    return {-1, -1};
}

bool Ball::haveTheSameColor(int anotherColor){
    for(int i : decodeColor(color%32)){
        for(int j : decodeColor(anotherColor%32)){
            if(i==j && i!=-1)
                return true;
        }
    }
    return false;
}