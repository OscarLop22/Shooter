#ifndef PLAYER_H
#define PLAYER_H

#include <3ds.h>


extern float playerX;
extern float playerY;
extern float pdx;
extern float pdy;
extern float playerAngle;
extern float playerSize;
extern float disT;
extern int fov;
extern int wall;

void initPlayer();
void drawPlayer();
void movePlayer(u32 kHeld);
void drawRays3D();
void drawWalls();

#endif