#include "MapCell.h"
#include "Map.h"

void Cell::addBall(int clr){
        ball = new Ball;
        ball->init(clr, x_cent, y_cent, vx_cent, vy_cent);
        empty = false;
}

void Cell::render() const{
    if(!empty){
        ball->render();
    }
}

void Cell::dropBall(int x, int y) {
    if(!empty) {
        empty = true;
        Map::fallingBalls.emplace_back(ball);
        Map::nonEmptyCells.erase({x, y});
        ball = nullptr;
    }
}

void Cell::update() {
    if(!empty)
        ball->update(0);
    y_cent += vy_cent;
}

void Cell::destroy() {
    if(!empty){
        delete ball;
        ball = nullptr;
    }
}

void Cell::init(double xCent, double yCent, double vxCent, double vyCent) {
    x_cent = xCent;
    y_cent = yCent;
    vx_cent = vxCent;
    vy_cent = vyCent;
}