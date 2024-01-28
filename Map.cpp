#include "Map.h"
#include "TextureManager.h"

std::vector<Ball*> Map::fallingBalls;

bool Map::inMap(int x, int y) {
    if((x<12 && x>=0) && y>=0){
        if(x%2==0 && y<9)
            return true;
        if(x%2==1 && y<10)
            return true;
    }
    return false;
}

std::vector<std::pair<int, int>> Map::immediateNeighbors(int x, int y) {
    std::vector<std::pair<int,int>> neigh, n = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};
    if(x%2==0){
        n.emplace_back(1, 1);
        n.emplace_back(-1, 1);
    }
    else{
        n.emplace_back(-1, -1);
        n.emplace_back(1, -1);
    }
    for(auto i : n){
        if(inMap(x+i.first, y+i.second))
            neigh.emplace_back(x+i.first, y+i.second);
    }
    return neigh;
}

void Map::getSameColorNeighbors(int x, int y){
    sameColorNeighbors.insert({x, y});
    for(auto i : immediateNeighbors(x, y)){
        int ind = i.first*10 + i.second;
        if(!map[ind].empty && map[ind].ball->color == map[10 * x + y].ball->color) {
            if (std::find(sameColorNeighbors.begin(), sameColorNeighbors.end(), i)==sameColorNeighbors.end()) {
                sameColorNeighbors.insert(i);
                getSameColorNeighbors(i.first, i.second);
            }
        }
    }
    return;
}

void Map::getNonEmptyNeighbors(int x, int y){
    nonEmptyNeighbors.insert({x, y});
    for(auto i : immediateNeighbors(x, y)){
        int ind = i.first*10 + i.second;
        if(!map[ind].empty && std::find(nonEmptyNeighbors.begin(), nonEmptyNeighbors.end(), i)==nonEmptyNeighbors.end()){
            nonEmptyNeighbors.insert(i);
            getNonEmptyNeighbors(i.first, i.second);
        }
    }
    return;
}

void Map::dropLooseBalls(){
    int x, y;
    for(int i=0; i<120; i++){
        x = i/10; y = i%10;
        if(inMap(x, y)){
            if(std::find(checkedBalls.begin(), checkedBalls.end(), std::make_pair(x,y))==checkedBalls.end()){
                getNonEmptyNeighbors(x, y);
                auto it = std::find_if(nonEmptyNeighbors.begin(), nonEmptyNeighbors.end(), [](const std::pair<int,int>& p ){ return p.first == 0; });
                if(it == nonEmptyNeighbors.end()){
                    for(auto j : nonEmptyNeighbors){
                        map[j.first * 10 + j.second].dropBall();
                    }
                }
                if(!nonEmptyNeighbors.empty()){
                    checkedBalls.insert(nonEmptyNeighbors.begin(), nonEmptyNeighbors.end());
                    nonEmptyNeighbors.clear();
                }
            }
        }
    }
    checkedBalls.clear();
}

void Map::LoadMap(){
    srand(time(0));
    int iter;
    map = new Cell[120];
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
            map[iter].addBall(rand()%2+1);
        }
    }

//    int xrand =  rand()%6+4;
//    int yrand = rand()%9;
//    std::cout<< xrand << " " << yrand << std::endl;
//    getSameColorNeighbors(xrand, yrand);
//    for(auto i : sameColorNeighbors){
//        map[i.first*10+i.second].dropBall();
//    }
//    sameColorNeighbors.clear();
    dropLooseBalls();
}

void Map::render(){
    for(int i=0; i < 120; i++)
        map[i].render();
    for(auto i : fallingBalls) {
        i->render();
    }
}

void Map::update() {
    for(int i=0; i < 120; i++){
        map[i].moveDown(0.5);
    }
    speed = 20 > speed +acceleration ? speed + acceleration : 20;
    for(auto &i : fallingBalls) {
        i->y_cent += speed;
    }
    for(auto &i : fallingBalls){
        if(i->y_cent>840){
            delete i;
            i = nullptr;
        }
        else
            fallingBallsCopy.emplace_back(i);
    }
    fallingBalls = fallingBallsCopy;
    fallingBallsCopy.clear();
}

void Map::destroy() {
    for(int i=0; i<120; i++)
        map[i].destroy();
    delete[] map;
    map = nullptr;
    for(int i=0; i<fallingBalls.size(); i++){
        delete fallingBalls[i];
        fallingBalls[i] = nullptr;
    }
    fallingBalls.clear();
    fallingBallsCopy.clear();
}