#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include "Map.h"
#include "Paths.h"
#include "Game.h"
#define mapSpeed 0.5

std::vector<Ball> Map::fallingBalls
std::set<std::pair<int, int>> Map::nonEmptyCells;
std::set<std::pair<int, int>> nonEmptyNeighbors;
std::set<std::pair<int, int>> sameColorNeighbors;
std::list<int> Map::ballQueue;

int Map::cellNumber = 180;
int ind;

void Map::LoadMap() {
    destroy();
    ceilingHeight = initialY - 10;
    setRectWithCenter(ceilingRect, 300, ceilingHeight, 600, 5);
    Ball::initPics();
    destructionChunk = Mix_LoadWAV(ballPopChunkPath);
    Cell cell;
    std::ifstream infile(generatedMapPath);
    std::string line, colorFromFile;
    int row = 0;
    while (std::getline(infile, line))
    {
        std::istringstream iss(line);
        for(int col=0; col<10; col++){
            iss >> colorFromFile;
            cell.ball.clear();
            if (row % 2 == 1) {
                cell.init(60 * col + 30, 60 * row + 30 + initialY, 0, mapSpeed);
            }
            if (row % 2 == 0) {
                cell.init(60 * col + 60, 60 * row + 30 + initialY, 0, mapSpeed);
            }
            if(inMap(row, col) && stoi(colorFromFile) != 0){
                cell.addBall(stoi(colorFromFile));
                nonEmptyCells.insert({row, col});
            }
            map.push_back(cell);
        }
        row++;
    }

    while(row < cellNumber/10){
        for(int col=0; col<10; col++){
            cell.ball.clear();
            if (row % 2 == 1) {
                cell.init(60 * col + 30, 60 * row + 30 + initialY, 0, mapSpeed);
            }
            if (row % 2 == 0) {
                cell.init(60 * col + 60, 60 * row + 30 + initialY, 0, mapSpeed);
            }
            map.push_back(cell);
        }
        row++;
    }
    ballQueue.clear();
    ballQueue.push_back(decideNextBallColor());
    SDL_Delay(1);
    ballQueue.push_back(decideNextBallColor());
}

void Map::render() {
    for (auto &i: nonEmptyCells) {
        ind = i.first * 10 + i.second;
        if (inScreen(map[ind].y_cent))
            map[ind].render();
    }
    for (auto &i: fallingBalls)
        i.render();
    for (auto &i: shootingBall)
        i.render();
    SDL_SetRenderDrawColor(Game::renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(Game::renderer, &ceilingRect);
    SDL_SetRenderDrawColor(Game::renderer, 255, 255, 255, 255);
}

void Map::update() {
    for (int i = 0; i < cellNumber; i++)
        if (inMap(i / 10, i % 10))
            map[i].update();
    for (auto &i: fallingBalls) {
        i.update(2);
    }
    ceilingHeight += mapSpeed;
    ceilingRect.y = (int)ceilingHeight;
    updateShootingBall();
    removeInvisibleBalls();
}

void Map::destroy() {
    for (auto &i: map)
        i.destroy();
    map.clear();
    sameColorNeighbors.clear();
    nonEmptyNeighbors.clear();
    nonEmptyCellsCopy.clear();
    checkedBalls.clear();
    nonEmptyCells.clear();
    shootingBall.clear();
    fallingBalls.clear();
    fallingBallsCopy.clear();
    Mix_FreeChunk(destructionChunk);
    destructionChunk = nullptr;
}

bool Map::inMap(int x, int y) {
    if ((x < cellNumber / 10 && x >= 0) && y >= 0) {
        if (x % 2 == 0 && y < 9)
            return true;
        if (x % 2 == 1 && y < 10)
            return true;
    }
    return false;
}

std::vector<std::pair<int, int>> Map::immediateNeighbors(int x, int y) {
    std::vector<std::pair<int, int>> neigh, n = {{0,  -1},
                                                 {1,  0},
                                                 {0,  1},
                                                 {-1, 0}};
    if (x % 2 == 0) {
        n.emplace_back(1, 1);
        n.emplace_back(-1, 1);
    } else {
        n.emplace_back(-1, -1);
        n.emplace_back(1, -1);
    }
    for (auto i: n) {
        if (inMap(x + i.first, y + i.second))
            neigh.emplace_back(x + i.first, y + i.second);
    }
    return neigh;
}

//also counts the cell itself
void Map::getSameColorNeighbors(int x, int y, int initialColor) {
    sameColorNeighbors.insert({x, y});
    for (auto &i: immediateNeighbors(x, y)) {
        ind = i.first * 10 + i.second;
        if (!map[ind].empty()) {
            if (haveTheSameColor(map[ind].ball[0].color, initialColor)) {
                if (sameColorNeighbors.find(i) == sameColorNeighbors.end()) {
                    sameColorNeighbors.insert(i);
                    getSameColorNeighbors(i.first, i.second,initialColor);
                }
            }
        }
    }
}

//also counts the cell itself
void Map::getNonEmptyNeighbors(int x, int y) {
    nonEmptyNeighbors.insert({x, y});
    for (auto i: immediateNeighbors(x, y)) {
        ind = i.first * 10 + i.second;
        if (!map[ind].empty() && nonEmptyNeighbors.find(i) == nonEmptyNeighbors.end()) {
            nonEmptyNeighbors.insert(i);
            getNonEmptyNeighbors(i.first, i.second);
        }
    }
}

bool Map::areLoose(std::set<std::pair<int, int>> &cells) {
    if (cells.empty())
        return false;
    if (std::all_of(cells.begin(), cells.end(), [](auto i){return i.first>0;}))
        return true;
    return false;
}

void Map::dropLooseBalls() {
    checkedBalls.clear();
    nonEmptyNeighbors.clear();
    vacatedCells.clear();
    for (auto &i: nonEmptyCells) {
        if (checkedBalls.find(i) == checkedBalls.end()) {
            getNonEmptyNeighbors(i.first, i.second);
            if (areLoose(nonEmptyNeighbors)) {
                vacatedCells.insert(nonEmptyNeighbors.begin(), nonEmptyNeighbors.end());
            }
            checkedBalls.insert(nonEmptyNeighbors.begin(), nonEmptyNeighbors.end());
            nonEmptyNeighbors.clear();
        }
    }
    Game::score += vacatedCells.size() * 10;
    for(auto &i : vacatedCells){
        map[i.first * 10 + i.second].dropBall(i.first, i.second);
    }
    vacatedCells.clear();
    checkedBalls.clear();
}

void Map::removeInvisibleBalls() {
    for (auto &i: fallingBalls) {
        if (!i.outOfScreen()) {
            fallingBallsCopy.emplace_back(i);
        }
    }
    fallingBalls = fallingBallsCopy;
    fallingBallsCopy.clear();

    for (auto &i: nonEmptyCells) {
        if (map[i.first * 10 + i.second].y_cent < 840) {
            nonEmptyCellsCopy.insert(i);
        }
    }
    nonEmptyCells = nonEmptyCellsCopy;
    nonEmptyCellsCopy.clear();

    if (!shootingBall.empty()) {
        if (shootingBall[0].outOfScreen())
            shootingBall.clear();
    }
}

void Map::addShootingBall(const double &angle, SDL_Rect &cannonRect) {
    double tmpAngle;
    tmpAngle = (90 - angle) * M_PI / 180;
    Ball newShootingBall(ballQueue.front(),
                         cannonRect.x + (int) (cannonRect.w / 2) + 1.3 * cannonRect.w / 2 * cos(tmpAngle),
                         cannonRect.y + (int) (cannonRect.h / 2) - 1.3 * cannonRect.h / 2 * sin(tmpAngle),
                         8 * cos(tmpAngle),
                         -8 * sin(tmpAngle));
    shootingBall.emplace_back(newShootingBall);
    ballQueue.pop_front();
    ballQueue.push_back(decideNextBallColor());
}

int Map::closestEmptyCell(std::pair<int, int> cell, std::pair<double, double> point) {
    std::vector<std::pair<double, int>> distanceIndexPair;
    double d;
    int index;
    std::vector<std::pair<int, int>> neighbors = immediateNeighbors(cell.first, cell.second);
    for (auto &i: neighbors) {
        index = i.first * 10 + i.second;
        if (map[index].empty()) {
            d = pow((map[index].x_cent - point.first), 2) + pow((map[index].y_cent - point.second), 2);
            d = sqrt(d);
            distanceIndexPair.emplace_back(d, index);
        }
    }
    if (distanceIndexPair.empty())
        return -1;
    std::sort(distanceIndexPair.begin(), distanceIndexPair.end());
    return distanceIndexPair[0].second;
}

void Map::checkBallForPoping(int x, int y) {

    if(map[10*x + y].ball[0].color == -3){
        for(int j=0; j<3; j++){
            for (auto &i: immediateNeighbors(x, y)) {
                if (inMap(i.first, i.second) && !map[i.first * 10 + i.second].empty()) {
                    map[i.first * 10 + i.second].renderBurn(j);
                }
            }
            SDL_RenderPresent(Game::renderer);
            SDL_Delay(50);
        }

        for (auto &i: immediateNeighbors(x, y)) {
            if (inMap(i.first, i.second) && !map[i.first * 10 + i.second].empty()) {
                map[i.first * 10 + i.second].popBall(i.first, i.second);
            }
        }
        SDL_RenderPresent(Game::renderer);
        map[10*x + y].popBall(x, y);
    }

    sameColorNeighbors.clear();
    getSameColorNeighbors(x, y, map[x*10 + y].ball[0].color);
    if (sameColorNeighbors.size() > 2) {
        Game::score += 2 * (int)pow(sameColorNeighbors.size(), 2);

        //Poping animation
        for(int j=0; j<3; j++){
            for (auto &i: sameColorNeighbors) {
                if (inMap(i.first, i.second) && map[i.first * 10 + i.second].ball[0].color < 32) {
                    map[i.first * 10 + i.second].renderPop(j);
                }
            }
            SDL_RenderPresent(Game::renderer);
            SDL_Delay(50);
        }

        for (auto &i: sameColorNeighbors) {
            if (inMap(i.first, i.second)) {
                if (map[i.first * 10 + i.second].ball[0].color < 32) {
                    Mix_PlayChannel(-1, destructionChunk, 0);
                    map[i.first*10 + i.second].popBall(i.first, i.second);
                }
                else
                    map[i.first * 10 + i.second].ball[0].color %= 32;
            }
        }
        double maxHeight = -1e3;
        for(auto i : nonEmptyCells){
            ind = i.first * 10 + i.second;
            maxHeight = maxHeight > map[ind].y_cent ? maxHeight : map[ind].y_cent;
        }
        if(maxHeight < 0){
            for(int i=0; i<cellNumber; i++){
                map[i].moveDown((int)-maxHeight);
            }
            ceilingHeight += -maxHeight;
        }
    }
    dropLooseBalls();
    sameColorNeighbors.clear();
}

void Map::updateShootingBall() {
    for (auto &i: shootingBall) {
        if (i.hitVerticalEdges())
            i.bounce();
        else
            i.update(0);
    }
    int closestCellIndex = -1;
    if (!shootingBall.empty()) {
        for (auto &i: nonEmptyCells) {
            ind = i.first * 10 + i.second;
            if (shootingBall[0].collisionWithCell(map[ind].x_cent, map[ind].y_cent)) {
                closestCellIndex = closestEmptyCell(i, shootingBall[0].nextCoordinate());
                if (closestCellIndex != -1)
                    break;
            }
        }
    }

    if (closestCellIndex != -1) {
        map[closestCellIndex].addBall(shootingBall[0].color);
        shootingBall.clear();
        nonEmptyCells.insert({closestCellIndex / 10, closestCellIndex % 10});
        checkBallForPoping(closestCellIndex / 10, closestCellIndex % 10);
    }

    else{
        if(!shootingBall.empty()){
            if(shootingBall[0].passedTheCeiling(ceilingHeight)){
                for(int i=0; i<10; i++){
                    if (shootingBall[0].collisionWithCell(map[i].x_cent, map[i].y_cent)) {
                        closestCellIndex = closestEmptyCell({0, i}, shootingBall[0].nextCoordinate());
                        if (closestCellIndex != -1)
                            break;
                    }
                }
            }
        }
        if (closestCellIndex != -1) {
            map[closestCellIndex].addBall(shootingBall[0].color);
            shootingBall.clear();
            nonEmptyCells.insert({closestCellIndex / 10, closestCellIndex % 10});
        }
    }

}

bool Map::passedTheBar(int yBar) const {
    for (auto &i: nonEmptyCells) {
        ind = i.first * 10 + i.second;
        if (map[ind].y_cent+30 > yBar)
            return true;
    }
    return false;
}

bool Map::onlyBlackBallsLeft(){
    for(auto &i: nonEmptyCells){
        if(map[i.first * 10 + i.second].ball[0].color != -1)
            return false;
    }
    return true;
}

int Map::decideNextBallColor() {
    cellColor.clear();
    for(auto &i : nonEmptyCells){
        ind = i.first * 10 + i.second;
        if(!map[ind].empty() && !map[ind].ball[0].outOfScreen())
            cellColor.push_back(map[ind].ball[0].color);
    }
    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());

    std::uniform_int_distribution<> distribution(1, 120);
    int rgb[5] = {0,0,0,0,0}, chance;
    chance = distribution(gen);
    if(chance > 107){
        return -3;
    }
    // red , green , blue , yellow , purple
    int x = (int)cellColor.size();
    if (x > 15) {
        for (int i = x-1 ; i >= x-15 ; i-- ) {
            if (cellColor[i] != -1) {
                for (int k = 0; k < 5; ++k) {
                    rgb[k] += (cellColor[i] >> k) & 1;
                }
            }
        }
    }
    else if (x>0) {
        for (int i = x-1 ; i >= 0 ; i--) {
            if (cellColor[i] != -1) {
                for (int k = 0; k < 5; ++k) {
                    rgb[k] += (cellColor[i] >> k) & 1;
                }
            }
        }
    }

    else {
        return 0;
    }
    int i  = 0 ;
    while(true){
        i ++;
        i = i % 5 ;
        if (chance - rgb[i] > 0 ) {
            chance -= rgb[i] ;
        }
        else {
            break ;
        }
    }
    x = (int)pow(2,i) ;
    return x;
}

#pragma clang diagnostic pop