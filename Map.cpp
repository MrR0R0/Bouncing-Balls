#pragma clang diagnostic push
#pragma ide diagnostic ignored "misc-no-recursion"

#include "Map.h"
#include "TextureManager.h"
#include "Paths.h"

std::vector<Ball> Map::fallingBalls;
std::set<std::pair<int, int>> Map::nonEmptyCells;
std::set<std::pair<int, int>> Map::sameColorNeighbors;
std::set<std::pair<int, int>> Map::nonEmptyNeighbors;

int Map::cellNumber = 160;
int ind;

void Map::LoadMap() {
    map.clear();
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
                cell.init(60 * col + 30, 60 * row + 30 + initialY, 0, 0.5);
            }
            if (row % 2 == 0) {
                cell.init(60 * col + 60, 60 * row + 30 + initialY, 0, 0.5);
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
                cell.init(60 * col + 30, 60 * row + 30 + initialY, 0, 0.5);
            }
            if (row % 2 == 0) {
                cell.init(60 * col + 60, 60 * row + 30 + initialY, 0, 0.5);
            }
            map.push_back(cell);
        }
        row++;
    }
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
}

void Map::update() {
    for (int i = 0; i < cellNumber; i++)
        if (inMap(i / 10, i % 10))
            map[i].update();
    for (auto &i: fallingBalls) {
        i.update(2);
    }
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
void Map::getSameColorNeighbors(int x, int y) {
    sameColorNeighbors.insert({x, y});
    for (auto &i: immediateNeighbors(x, y)) {
        ind = i.first * 10 + i.second;
        if (!map[ind].empty()) {
            if (map[ind].ball[0].haveTheSameColor(map[10 * x + y].ball[0].color)) {
                if (sameColorNeighbors.find(i) == sameColorNeighbors.end()) {
                    sameColorNeighbors.insert(i);
                    getSameColorNeighbors(i.first, i.second);
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
    for (auto &i: cells) {
        if (i.first == 0)
            return false;
    }
    return true;
}

void Map::dropLooseBalls() {
    checkedBalls.clear();
    nonEmptyNeighbors.clear();
    aboutToFall.clear();
    for (auto &i: nonEmptyCells) {
        if (checkedBalls.find(i) == checkedBalls.end()) {
            getNonEmptyNeighbors(i.first, i.second);
            if (areLoose(nonEmptyNeighbors)) {
                aboutToFall.insert(nonEmptyNeighbors.begin(), nonEmptyNeighbors.end());
            }
            checkedBalls.insert(nonEmptyNeighbors.begin(), nonEmptyNeighbors.end());
            nonEmptyNeighbors.clear();
        }
    }
    for(auto &i : aboutToFall){
        map[i.first * 10 + i.second].dropBall(i.first, i.second);
    }
    aboutToFall.clear();
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
    Ball newShootingBall(4,
                         cannonRect.x + (int) (cannonRect.w / 2) + 1.3 * cannonRect.w / 2 * cos(tmpAngle),
                         cannonRect.y + (int) (cannonRect.h / 2) - 1.3 * cannonRect.h / 2 * sin(tmpAngle),
                         8 * cos(tmpAngle),
                         -8 * sin(tmpAngle));
    shootingBall.emplace_back(newShootingBall);
}

bool Map::inScreen(double &y) {
    if (y > -40)
        return true;
    return false;
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

void Map::checkBallForFall(int x, int y) {
    sameColorNeighbors.clear();
    getSameColorNeighbors(x, y);
    if (sameColorNeighbors.size() > 2) {
        for (auto &i: sameColorNeighbors) {
            if (inMap(i.first, i.second)) {
                if (map[i.first * 10 + i.second].ball[0].color < 32)
                    map[i.first * 10 + i.second].dropBall(i.first, i.second);
                else
                    map[i.first * 10 + i.second].ball[0].color %= 32;
            }
        }
        dropLooseBalls();
    }
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
                closestCellIndex = closestEmptyCell(i, shootingBall[0].coordinate());
                if (closestCellIndex != -1)
                    break;
            }
        }
    }

    if (closestCellIndex != -1) {
        map[closestCellIndex].addBall(shootingBall[0].color);
        shootingBall.clear();
        nonEmptyCells.insert({closestCellIndex / 10, closestCellIndex % 10});
        checkBallForFall(closestCellIndex / 10, closestCellIndex % 10);
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

void Map::generateRandomMap() {
    int list[12][11];
    int chance  , randomcolor1 , randomcolor2 ;
    bool listcheck[12][10], L;


    for ( int i = 0; i < 12; i++ ) {
        for ( int j = 0; j < 10 ; j++ ) {
            listcheck[i][j] = true ;
        }
    }

    std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());

    std::uniform_int_distribution<> distribution(1, 100)  ;



    for ( int i = 0; i < 12 ; i++ ) {
        randomcolor1 = distribution(gen);
        list[i][10] = pow(2,randomcolor1%5) ;
        // cout << list [i][10] << " " ;
    }


    list [0][0] = list [0][1] = list [0][2]  = 2 ;
    list [0][3] = list [0][4] = 16 ;
    list [0][5] = list [0][6] = 1 ;
    list [0][7] = 34 ;
    list [0][8] = list [0][9] =  4;

    for (int i = 1 ; i < 12 ; i++) {
        for (int j = 0 ; j < 10 ; j++) {

            if (listcheck[i][j]) {

                chance = distribution(gen);
                randomcolor1 = distribution(gen);
                randomcolor2  = distribution(gen);
                //cout << chance <<  randomcolor1 << randomcolor2 << endl;

                if (chance < 15 && listcheck[i-1][j] ) {
                    list [i][j] = list [i-1][j] ;
                }

                else if (chance < 30) {
                    L = (listcheck[i-1][j] >> 5) & 1  ;

                    for (int k = 0; k < 5; ++k) {
                        if ((listcheck[i-1][j] >> k) & 1) {
                            list [i][j] = 32 * L + (1<<k) ;
                            break ;
                        }
                    }
                }


                else if (chance < 45 && listcheck[i-1][j+1] ) {
                    list [i][j] = list [i-1][j+1] ;
                }

                else if (chance < 60) {
                    L = (listcheck[i-1][j+1] >> 5) & 1  ;

                    for (int k = 0; k < 5; ++k) {
                        if ((listcheck[i-1][j+1] >> k) & 1) {
                            list [i][j] = 32 * L + (1<<k) ;
                            break ;
                        }
                    }
                }


                    // -1 havasam bashe


                else if (chance < 70) {
                    list [i][j] = 32  + (1<<randomcolor1%5) ;


                }

                else if (chance < 85 ) {
                    if (randomcolor2%5 == randomcolor1%5 ) {
                        list[i][j] =  (1<<(randomcolor1%5) ) ;
                    }
                    else {
                        list[i][j] =  (1<<(randomcolor2%5))  + (1<<(randomcolor1%5))  ;
                    }
                }

                else {
                    list[i][j] = (1<< ((randomcolor1%4) +1));
                }

            }
        }



    }

    for (int i = 0 ; i < 12 ; i++) {
        for (int j = 0; j < 11; j++) {
            randomcolor1 = distribution(gen);
            if (randomcolor1%17 == j ) {
                list [i][j] = 0 ;
            }
        }
    }


    std::ofstream outFile;
    outFile.open(generatedMapPath);

    for (int i = 0 ; i < 12 ; i++) {
        for (int j = 0; j < 10; j++) {
            outFile << list[i][j] << " " ;
        }
        outFile << std::endl ;

    }

    outFile.close();
}

#pragma clang diagnostic pop