#include "MapCell.h"

void Cell::render(){
    ball->color = color;
    ball->render(x_cent, y_cent);
}