#ifndef WORLD_H
#define WORLD_H


extern int mapX;
extern int mapY;
extern int mapS;

extern int map[];


void initMapValues();

void generateMap();

void drawMap2D();

#endif