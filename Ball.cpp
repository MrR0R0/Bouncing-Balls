#include "Ball.h"
#include "TextureManager.h"
#include "Paths.h"

void Ball::render(){
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
    setRectWithCenter(ballRect, x_cent, y_cent, 60, 60);
    ballPic = TextureManager::LoadTexture(path.c_str());
    SDL_RenderCopy(Game::renderer, ballPic, nullptr, &ballRect);
}

void Ball::fall() {

}