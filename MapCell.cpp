#include "MapCell.h"

void Cell::render(){
    if(!empty) {
        ball->color = color;
        ball->render(x_cent, y_cent);
    }
}