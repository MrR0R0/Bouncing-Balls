#include "Map.h"
#include "TextureManager.h"

std::vector<Ball*> Map::fallingBalls;

void Map::LoadMap(){
    srand(time(nullptr));
    int iter;
    map = new Cell[120];
    for(int row=0; row < 12; row++) {
        for (int col = 0; col < 10; col++) {
            if(inMap(row, col)){
                iter = 10 * row + col;
                map[iter].x_cent = 60 * col + 30;
                if(row%2==0)
                    map[iter].x_cent += 30;
                map[iter].y_cent = 60 * row + 30 + initialY;
                map[iter].vx_cent = 0;
                map[iter].vy_cent = 0;
                map[iter].addBall(rand()%2+1);
            }
        }
    }

//    int xrand =  rand()%6+4;
//    int yrand = rand()%9;
//    //std::cout<< xrand << " " << yrand << std::endl;
//    getSameColorNeighbors(xrand, yrand);
//    for(auto i : sameColorNeighbors){
//        map[i.first*10+i.second].dropBall();
//    }
//    sameColorNeighbors.clear();
//    dropLooseBalls();
}

void Map::render() const{
    for(int i=0; i < 120; i++) {
        if(inScreen(map[i].x_cent, map[i].y_cent))
            map[i].render();
    }
    for(auto &i : fallingBalls)
        i->render();
    for(auto &i : shootingBalls)
        i->render();
}

void Map::update() {
    for(int i=0; i < 120; i++)
        map[i].update();
    for(auto &i : fallingBalls) {
        i->vy_cent = 20 > i->vy_cent + acceleration ? i->vy_cent + acceleration : 20;
        i->update();
    }
    for(auto &i : shootingBalls){
        if(i->x_cent + i->vx_cent >= 600 - 30 - Ball::cnst/2){
            i->x_cent = 600 - 30 - Ball::cnst/2;
            i->vx_cent *= -1;
        }
        else if(i->x_cent + i->vx_cent <= 30 + Ball::cnst/2){
            i->x_cent = 30 + Ball::cnst/2;
            i->vx_cent *= -1;
        }
        else
            i->update();
    }
    removeInvisibleBalls();
    for(auto j : shootingBalls) {
        for (int i = 0; i < 120; i++) {
            if(inMap(i/10, i%10) && !map[i].empty) {
                if (j->nextMoveCollisionWithCell(map[i].x_cent, map[i].y_cent) == SDL_TRUE) {
                    j->color = 4;
                }
            }
        }
    }
}

void Map::destroy() {
    for(int i=0; i<120; i++)
        map[i].destroy();
    delete[] map;
    map = nullptr;
    for(auto &i : fallingBalls){
        delete i;
        i = nullptr;
    }
    for(auto &i : shootingBalls){
        delete i;
        i = nullptr;
    }
    fallingBalls.clear();
    fallingBallsCopy.clear();
    shootingBalls.clear();
    shootingBallsCopy.clear();
}

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

void Map::removeInvisibleBalls() {
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

    for(auto &i : shootingBalls){
        if(i->x_cent < -40 || i->x_cent > 640){
            delete i;
            i = nullptr;
        }
        else
            shootingBallsCopy.emplace_back(i);
    }
    shootingBalls = shootingBallsCopy;
    shootingBallsCopy.clear();
}

void Map::addShootingBall(const double &angle, SDL_Rect &cannonRect) {
    Ball *newBallPointer = new Ball;
    double *tmpAngle = new double;
    *tmpAngle = (90 - angle)* M_PI/180;
    newBallPointer->color = 1;
    newBallPointer->x_cent = cannonRect.x + cannonRect.w/2 + 1.3 * cannonRect.w/2 * cos(*tmpAngle);
    newBallPointer->y_cent = cannonRect.y + cannonRect.h/2 - 1.3 * cannonRect.h/2 * sin(*tmpAngle);
    newBallPointer->vx_cent = 2 * cos(*tmpAngle);
    newBallPointer->vy_cent = -2 * sin(*tmpAngle);
    delete tmpAngle;
    tmpAngle = nullptr;
    shootingBalls.emplace_back(newBallPointer);
}

bool Map::inScreen(double &x, double &y) {
    if(y>-40)
        return true;
    return false;
}