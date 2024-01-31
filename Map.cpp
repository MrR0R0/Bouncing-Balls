#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"
#include "Map.h"
#include "TextureManager.h"

std::vector<Ball*> Map::fallingBalls;
std::set<std::pair<int, int>> Map::nonEmptyCells;
std::set<std::pair<int, int>> Map::sameColorNeighbors;
int Map::cellNumber = 160;
int ind;

void Map::LoadMap(){
    srand(time(nullptr));
    map = new Cell[cellNumber];
    for(int row=0; row < cellNumber; row++) {
        for (int col = 0; col < 10; col++) {
            if(inMap(row, col)){
                ind = 10 * row + col;
                if(row%2==1){
                    map[ind].init(60 * col + 30, 60 * row + 30 + initialY, 0, 0.5);
                }
                if(row%2==0){
                    map[ind].init(60 * col + 60, 60 * row + 30 + initialY, 0, 0.5);
                }
                if(col%4==2 && row<12){
                    map[ind].addBall(rand()%2+1+32);
                    nonEmptyCells.insert({row, col});
                }
            }
        }
    }
}

void Map::render(){
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

void Map::update(){
    for(int i=0; i < cellNumber; i++)
        map[i].update();
    for(auto &i : fallingBalls){
        i->update(2);
    }
    for(auto &i : newFilledCells){
        checkBallForFall(i.first, i.second);
    }
    newFilledCells.clear();
    dropLooseBalls();
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
    for(auto i : shootingBalls) {
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

//also counts the cell itself
void Map::getSameColorNeighbors(int x, int y){
    sameColorNeighbors.insert({x, y});
    for(auto &i : immediateNeighbors(x, y)){
        ind = i.first*10 + i.second;
        if(!map[ind].empty) {
            if(map[ind].ball->color == map[10 * x + y].ball->color){
                if (std::find(sameColorNeighbors.begin(), sameColorNeighbors.end(), i)==sameColorNeighbors.end()) {
                    sameColorNeighbors.insert(i);
                    getSameColorNeighbors(i.first, i.second);
                }
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
                        map[j.first * 10 + j.second].dropBall(j.first, j.second);
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
        if(i->hitBottom()) {
            delete i;
            i = nullptr;
        }
        else
            fallingBallsCopy.emplace_back(i);
    }
    fallingBalls = fallingBallsCopy;
    fallingBallsCopy.clear();

    for(auto i : shootingBalls){
        if(i->outOfScreen()) {
            delete i;
            i = nullptr;
        }
        else
            shootingBallsCopy.insert(i);
    }
    shootingBalls = shootingBallsCopy;
    shootingBallsCopy.clear();

    for(auto &i : nonEmptyCells){
        if(map[i.first*10+i.second].y_cent<840){
            nonEmptyCellsCopy.insert(i);
        }
    }
    nonEmptyCells = nonEmptyCellsCopy;
    nonEmptyCellsCopy.clear();
}

void Map::addShootingBall(const double &angle, SDL_Rect &cannonRect) {
    Ball *newBallPointer = new Ball;
    auto *tmpAngle = new double;
    *tmpAngle = (90 - angle)* M_PI/180;
    newBallPointer->init(1,
                         cannonRect.x + (int)(cannonRect.w/2) + 1.3 * cannonRect.w/2 * cos(*tmpAngle),
                         cannonRect.y + (int)(cannonRect.h/2) - 1.3 * cannonRect.h/2 * sin(*tmpAngle),
                         2 * cos(*tmpAngle),
                         -2 * sin(*tmpAngle));
    delete tmpAngle;
    tmpAngle = nullptr;
    shootingBalls.insert(newBallPointer);
}

bool Map::inScreen(double &y) {
    if(y>-40)
        return true;
    return false;
}

std::pair<int, int> Map::closestEmptyCell(std::pair<int, int> cell, std::pair<double, double> point) const{
    std::vector<std::pair<double, int>> distance;
    std::vector<std::pair<int, int>> neighbors = immediateNeighbors(cell.first, cell.second);
    for(int i=0; i<neighbors.size(); i++) {
        ind = neighbors[i].first * 10 + neighbors[i].second;
        if(map[ind].empty)
            distance.emplace_back(pow((map[ind].x_cent - point.first), 2) + pow((map[ind].y_cent - point.second), 2), i);
    }
    if(distance.empty())
        return std::make_pair(-1, -1);
    std::sort(distance.begin(), distance.end());
    return neighbors[distance[0].second];
}

void Map::checkBallForFall(int x, int y){
    getSameColorNeighbors(x, y);
    if(sameColorNeighbors.size()>2){
        for(auto &i : sameColorNeighbors)
            map[i.first*10 + i.second].dropBall(i.first, i.second);
    }
    sameColorNeighbors.clear();
}

void Map::updateShootingBalls(){

    for(auto i : shootingBalls){
        if(i->hitVerticalEdges())
            i->bounce();
        else
            i->update(0);
    }

    std::pair<int, int> closestCell;
    for(auto &ball : shootingBalls) {
        for (auto &i : nonEmptyCells) {
            ind = i.first * 10 + i.second;
            if (ball->collisionWithCell(map[ind].x_cent, map[ind].y_cent) == SDL_TRUE) {
                closestCell = closestEmptyCell({i.first, i.second}, ball->coordinate());
                if(closestCell != std::make_pair(-1, -1)) {
                    map[closestCell.first * 10 + closestCell.second].addBall(ball->color);
                    newFilledCells.insert({closestCell.first, closestCell.second});
                    stationaryBalls.insert(ball);
                    break;
                }
            }
        }
    }

    nonEmptyCells.insert(newFilledCells.begin(), newFilledCells.end());
    for(auto ball : stationaryBalls){
        shootingBalls.erase(ball);
        delete ball;
        ball = nullptr;
    }
    stationaryBalls.clear();
}

bool Map::passedTheBar(int yBar) const{
    for(auto &i : nonEmptyCells){
        ind = i.first * 10 + i.second;
        if(map[ind].y_cent > yBar)
            return true;
    }
    return false;
}

#pragma clang diagnostic pop