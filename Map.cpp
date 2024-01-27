#include "Map.h"
#include "TextureManager.h"

void Map::LoadMap(){
    int iter;
    for(int row=0; row < 20; row++) {
        for (int col = 0; col < 20; col++) {
            iter = 20 * row + col;
            map[iter].x_cent = 30 * col + 15;
            map[iter].y_cent = 30 * row + 15;
            map[iter].color = 1;
        }
    }
}

void Map::render(){
    for(int i=0; i < 400; i++)
        map[i].render();
}

void Map::update() {
    for(int i=0; i < 400; i++)
        map[i].y_cent+=10;
}