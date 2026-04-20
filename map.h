#ifndef MAP_H
#define MAP_H
#include "spot.h"
#include<vector>

const int ROW = 16;
const int COLUMN = 16;

const char WALL = '#';
const char ROAD = '.';
const char SPOT_FREE = 'P';
const char SPOT_TAKEN = 'X';
const char ENTRY = 'E';
const char EXIT_GATE = 'S';

//Funciones mapp.cpp
void initMap(char map[ROW][COLUMN]);
void showMap(char map[ROW][COLUMN]);
void updateMap(char map[ROW][COLUMN], std::vector<Spot>&spots);

#endif