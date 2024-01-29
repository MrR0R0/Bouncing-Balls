#include "Ball.h"
#include "TextureManager.h"
#include "Paths.h"

bool Ball::collision;
SDL_Rect Ball::ballRectCopy;

int Ball::cnst = 8;

void Ball::init(int c, double x, double y, double vx, double vy){
    color = c;
    x_cent = x;
    y_cent = y;
    vx_cent = vx;
    vy_cent = vy;
    std::string path, child;
    if(color == 1) child = redBallPicPath;
    else if(color == 2) child = greenBallPicPath;
    else if(color == 4) child = blueBallPicPath;
    else if(color == 8) child = yellowBallPicPath;
    else if(color == 16) child = purpleBallPicPath;
    switch (Game::ballTheme){
        case Glass:
            path = "..\\assets\\theme1";
            break;
        case Marble:
            path = "..\\assets\\theme2";
            break;
        case Plastic:
            path = "..\\assets\\theme3";
            break;
    }
    path += child;
    ballPic = TextureManager::LoadTexture(path.c_str());
}

void Ball::render(){
    setRectWithCenter(ballRect, x_cent, y_cent, 60+cnst, 60+cnst);
    SDL_RenderCopy(Game::renderer, ballPic, nullptr, &ballRect);
}

void Ball::update() {
    x_cent += vx_cent;
    y_cent += vy_cent;
}

bool Ball::nextMoveCollisionWithCell(double xCentCell, double yCentCell) {
    auto *cellRect = new SDL_Rect;
    ballRectCopy = ballRect;
    ballRectCopy.x += vx_cent;
    ballRectCopy.y += vy_cent;
    setRectWithCenter(ballRect, x_cent, y_cent, 60, 60);
    setRectWithCenter(cellRect, xCentCell, yCentCell, 60, 60);
    collision = SDL_HasIntersection(cellRect, &ballRect);
    delete cellRect;
    cellRect = nullptr;
    return collision;
}