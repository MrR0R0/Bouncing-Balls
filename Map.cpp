#include "Map.h"
#include "TextureManager.h"

std::vector<Ball*> Map::fallingBalls;
int Map::cellNumber = 160;
int ind;

void Map::LoadMap(){
    srand(time(nullptr));
    map = new Cell[cellNumber];
    for(int row=0; row < cellNumber; row++) {
        for (int col = 0; col < 10; col++) {
            if(inMap(row, col)){
                ind = 10 * row + col;
                map[ind].x_cent = 60 * col + 30;
                if(row%2==0)
                    map[ind].x_cent += 30;
                map[ind].y_cent = 60 * row + 30 + initialY;
                map[ind].vx_cent = 0;
                map[ind].vy_cent = 0;
                if(col%4==2 && row<12){
                    map[ind].addBall(rand()%2+1);
                    nonEmptyCells.insert({row, col});
                }
            }
        }
    }
}

void Map::render() const{
    for(auto &i : nonEmptyCells) {
        ind = i.first * 10 + i.second;
        if(inScreen(map[ind].y_cent))
            map[ind].render();
    }
    for(auto &i : fallingBalls)
        i->render();
    for(auto &i : shootingBalls)
        i->render();
}

void Map::update() {
    for(int i=0; i < cellNumber; i++)
        map[i].update();
    for(auto &i : fallingBalls) {
        i->vy_cent = 20 > i->vy_cent + acceleration ? i->vy_cent + acceleration : 20;
        i->update();
    }
    updateShootingBalls();
    removeInvisibleBalls();

}

void Map::destroy() {
    for(int i=0; i<cellNumber; i++)
        map[i].destroy();
    delete[] map;
    map = nullptr;
    for(auto &i : fallingBalls){
        delete i;
        i = nullptr;
    }
    for(auto i : shootingBalls){
        delete i;
        i = nullptr;
    }
    nonEmptyCells.clear();
    fallingBalls.clear();
    fallingBallsCopy.clear();
    shootingBalls.clear();
}

bool Map::inMap(int x, int y) {
    if((x<cellNumber/10 && x>=0) && y>=0){
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
        ind = i.first*10 + i.second;
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
        ind = i.first*10 + i.second;
        if(!map[ind].empty && std::find(nonEmptyNeighbors.begin(), nonEmptyNeighbors.end(), i)==nonEmptyNeighbors.end()){
            nonEmptyNeighbors.insert(i);
            getNonEmptyNeighbors(i.first, i.second);
        }
    }
}

void Map::dropLooseBalls(){
    int x, y;
    for(int i=0; i<cellNumber; i++){
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

    for(auto i : shootingBalls){
        if(i->x_cent < -40 || i->x_cent > 640){
            delete i;
            i = nullptr;
        }
        else
            shootingBallsCopy.insert(i);
    }
    shootingBalls = shootingBallsCopy;
    shootingBallsCopy.clear();
}

void Map::addShootingBall(const double &angle, SDL_Rect &cannonRect) {
    Ball *newBallPointer = new Ball;
    auto *tmpAngle = new double;
    *tmpAngle = (90 - angle)* M_PI/180;
    newBallPointer->color = 1;
    newBallPointer->x_cent = cannonRect.x + cannonRect.w/2 + 1.3 * cannonRect.w/2 * cos(*tmpAngle);
    newBallPointer->y_cent = cannonRect.y + cannonRect.h/2 - 1.3 * cannonRect.h/2 * sin(*tmpAngle);
    newBallPointer->vx_cent = 2 * cos(*tmpAngle);
    newBallPointer->vy_cent = -2 * sin(*tmpAngle);
    delete tmpAngle;
    tmpAngle = nullptr;
    shootingBalls.insert(newBallPointer);
}

bool Map::inScreen(double &y) {
    if(y>-40)
        return true;
    return false;
}

std::pair<int, int> Map::getClosestEmptyCell(std::vector<std::pair<int, int>> cells, double x, double y){
    std::vector<std::pair<double, int>> distance;
    for(int i=0; i<cells.size(); i++) {
        ind = cells[i].first * 10 + cells[i].second;
        if(map[ind].empty)
            distance.emplace_back(pow((map[ind].x_cent - x), 2) + pow((map[ind].y_cent - y), 2), i);
    }
    std::sort(distance.begin(), distance.end());
    return cells[distance[0].second];
}

void Map::updateShootingBalls(){
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

    std::pair<int, int> closestCell;
    for(auto &ball : shootingBalls) {
        for (auto &i : nonEmptyCells) {
            ind = i.first * 10 + i.second;
            if(inMap(i.first, i.second)) {
                if (ball->nextMoveCollisionWithCell(map[ind].x_cent, map[ind].y_cent) == SDL_TRUE) {
                    closestCell = getClosestEmptyCell(immediateNeighbors(i.first, i.second), ball->x_cent, ball->y_cent);
                    map[closestCell.first * 10 + closestCell.second].addBall(ball->color);
                    newFilledCells.insert({closestCell.first, closestCell.second});
                    stationaryBalls.insert(ball);
                    break;
                }
            }
        }
    }

    nonEmptyCells.insert(newFilledCells.begin(), newFilledCells.end());
    newFilledCells.clear();

    for(auto ball : stationaryBalls){
        shootingBalls.erase(ball);
        delete ball;
        ball = nullptr;
    }
    stationaryBalls.clear();
}