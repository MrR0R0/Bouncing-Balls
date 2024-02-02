#include "MapCell.h"
#include "Map.h"


void Cell::init(double xCent, double yCent, double vxCent, double vyCent) {
    x_cent = xCent;
    y_cent = yCent;
    vx_cent = vxCent;
    vy_cent = vyCent;
}

void Cell::addBall(int clr){
    ball.clear();
    Ball b;
    b.init(clr, x_cent, y_cent, vx_cent, vy_cent);
    ball.emplace_back(b);
}

void Cell::render(){
    if(!empty()){
        ball[0].render();
    }
}

void Cell::dropBall(int x, int y) {
    if(!empty()) {
        Map::fallingBalls.emplace_back(ball[0]);
        Map::nonEmptyCells.erase({x, y});
        ball.clear();
    }
}

void Cell::update() {
    if(!empty())
        ball[0].update(0);
    y_cent += vy_cent;
}

void Cell::destroy() {
    ball.clear();
}