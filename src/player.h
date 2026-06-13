#ifndef PLAYER_H
#define PLAYER_H

#include <3ds.h>


extern float px;
extern float py;
extern float pdx;
extern float pdy;
extern float pa;
extern float ps;


void initPlayer();

void drawPlayer();

void movePlayer(u32 kHeld);

void drawRays3D();

#endif