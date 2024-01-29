#include "MapCell.h"
#include "Map.h"

void Cell::addBall(int clr){
    ball = new Ball;
    ball->x_cent = x_cent;
    ball->y_cent = y_cent;
    ball->vx_cent = vx_cent;
    ball->vy_cent = vy_cent;
    ball->color = clr;
    empty = false;
}

void Cell::render() const{
    if(!empty){
        ball->render();
    }
}

void Cell::dropBall() {
    if(!empty) {
        empty = true;
        Map::fallingBalls.emplace_back(ball);
        ball = nullptr;
    }
}

void Cell::update() {
    if(!empty)
        ball->update();
    y_cent += vy_cent;
}

void Cell::destroy() {
    if(!empty){
        delete ball;
        ball = nullptr;
    }
}