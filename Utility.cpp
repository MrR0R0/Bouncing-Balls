#include "Utility.h"
#include "Paths.h"

std::vector<int> decodeColor(int c){
    std::set<int> colors = {1, 2, 4, 8, 16};
    if(colors.find(c) != colors.end())
        return {c, -1};

    for(int c1=1; c1<=c/2+1; c1*=2){
        if(colors.find(c - c1) != colors.end()){
            return {c1, c-c1};
        }
    }
    return {-1, -1};
}

void generateRandomMap() {
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
        list[i][10] = (int)pow(2,randomcolor1%5) ;
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

bool inScreen(double &y) {
    if (y > -40 && y < 840)
        return true;
    return false;
}

void setRectWithCenter(SDL_Rect &rect, double x, double y, double w, double h) {
    rect.x = (int)(x - w/2);
    rect.y = (int)(y - h/2);
    rect.w = (int)w;
    rect.h = (int)h;
}

void setRectWithCorner(SDL_Rect &rect, double x, double y, double w, double h){
    rect.x = (int)x;
    rect.y = (int)y;
    rect.w = (int)w;
    rect.h = (int)h;
}

bool pointInRect(SDL_Rect rect, int &x, int &y) {
    if((x >= rect.x && x <= rect.x+rect.w) && (y >= rect.y && y <= rect.y+rect.h))
        return true;
    return false;
}