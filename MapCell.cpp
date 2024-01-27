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
    empty = true;
    Map::fallingBalls.push_back(ball);
    ball = new Ball;
}

void Cell::moveDown(double d) {
    if(!empty)
        ball->y_cent += d;
    y_cent += d;
}