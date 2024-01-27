#include "Map.h"
#include "TextureManager.h"

std::vector<Ball*> Map::fallingBalls;

void Map::LoadMap(){
    int iter;
    for(int row=0; row < 12; row++) {
        for (int col = 0; col < 10; col++) {
            iter = 10 * row + col;
            map[iter].empty = false;
            map[iter].x_cent = 60 * col + 30;
            if(row%2==0){
                map[iter].x_cent += 30;
                if(col==9)
                    map[iter].empty = true;
            }
            map[iter].y_cent = 60 * row + 30 + initialY;
            map[iter].addBall(1);
        }
    }
    map[12].dropBall();
}

void Map::render(){
    for(auto i : fallingBalls) {
        i->render();
    }
    for(int i=0; i < 120; i++)
        map[i].render();
}

void Map::update() {
    for(int i=0; i < 120; i++){
        map[i].moveDown(0.5);
    }
    for(auto i : fallingBalls) {
        i->y_cent += 20;
    }
    for(auto i : fallingBalls){
        if(i->y_cent>840){
            delete i;
            i = nullptr;
        }
        else
            fCop.push_back(i);
    }
    fallingBalls = fCop;
    fCop.clear();
}