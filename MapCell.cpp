#include "MapCell.h"
#include "Map.h"

void Cell::addBall(int clr){
    ball = new Ball;
    ball->x_cent = x_cent;
    ball->y_cent = y_cent;
    ball->color = clr;
}

void Cell::render(){
    if(!empty) {
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

void Cell::moveDown(double d) {
    if(!empty)
        ball->y_cent += d;
    y_cent += d;
}

void Cell::destroy() {
    if(!empty){
        delete ball;
        ball = nullptr;
    }
}