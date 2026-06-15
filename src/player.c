#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include <citro2d.h>
#include <citro3d.h>

#include "world.h"

#define PI 3.1415926535
#define P2 PI/2
#define P3 3*PI/2
#define DR 0.0174533 //one degree in radians

float playerX = 0;
float playerY = 0;
float pdx = 0;
float pdy = 0;
float playerAngle = 0;
float playerSize = 0;
float disT;
int fov = 90;
int wall = 0;

void initPlayer()
{
	playerX=100;
    playerY=100;
    pdx=cos(playerAngle)*5; pdy=sin(playerAngle)*5;
    playerSize=8;
}


void drawPlayer()
{
    float half = playerSize/2.0f;
    u32 clrRec1 = C2D_Color32(0x9A, 0x6C, 0xB9, 0xFF);
	u32 clrRec2 = C2D_Color32(0xFF, 0xFF, 0x2C, 0xFF);
	u32 clrRec3 = C2D_Color32(0xD8, 0xF6, 0x0F, 0xFF);
	u32 clrRec4 = C2D_Color32(0x40, 0xEA, 0x87, 0xFF);

    C2D_DrawRectangle(playerX-half, playerY-half, 0, playerSize, playerSize, clrRec1, clrRec2, clrRec3, clrRec4);

    u32 clrLine1 = C2D_Color32(0x9A, 0x6C, 0xB9, 0xFF);
    u32 clrLine2 = C2D_Color32(0xFF, 0xFF, 0x2C, 0xFF);

    C2D_DrawLine(playerX, playerY, clrLine1, playerX+pdx*5, playerY+pdy*5, clrLine2, 2, 0);
}

void movePlayer(u32 kHeld)
{
    if (kHeld & KEY_DUP) {playerX+=pdx/3; playerY+=pdy/3;}
    if (kHeld & KEY_DDOWN) {playerX-=pdx/3; playerY-=pdy/3;}
    if (kHeld & KEY_DLEFT) { playerAngle-=0.1; if(playerAngle<0){ playerAngle+=2*PI; } pdx=cos(playerAngle)*5; pdy=sin(playerAngle)*5; }
    if (kHeld & KEY_DRIGHT) { playerAngle+=0.1; if(playerAngle>2*PI){ playerAngle-=2*PI; } pdx=cos(playerAngle)*5; pdy=sin(playerAngle)*5; }

}

float dist(float ax, float ay, float bx, float by, float ang)
{
    return ( sqrt((bx-ax)*(bx-ax) + (by-ay)*(by-ay)));
}

void drawRays3D()
{
    int r,mx,my,mp,dof; float rayX,rayY,rayAngle,xo,yo;
    rayAngle=playerAngle-DR*30;

    if (rayAngle<0) { rayAngle+=2*PI;} if (rayAngle>2*PI) { rayAngle-=2*PI;} 

    for(r=0;r<60;r++)
    {
        u32 clrLine = C2D_Color32(0xFF, 0x77, 0x59, 0xAF);


        //Horizontal Lines
        dof=0;
        float disH=1000000,hx=playerX,hy=playerY;
        float aTan=-1/tan(rayAngle);
        if(rayAngle>PI){ rayY=(((int)playerY/mapSize)*mapSize)-0.0001; rayX=(playerY-rayY)*aTan+playerX; yo=-mapSize; xo=-yo*aTan; }
        if(rayAngle<PI){ rayY=(((int)playerY/mapSize)*mapSize)+mapSize; rayX=(playerY-rayY)*aTan+playerX; yo=mapSize; xo=-yo*aTan; }
        if(rayAngle==0 || rayAngle==PI){ rayX=playerX; rayY=playerY; dof=mapX;}
        
        while(dof<mapX)
        {
            mx=(int)(rayX)/mapSize; my=(int)(rayY)/mapSize; mp=my*mapX+mx;
            if(mp>0 && mp<mapX*mapY && map[mp]==1) { hx=rayX; hy=rayY; disH=dist(playerX, playerY, hx, hy, rayAngle); dof=mapX; }
            else{ rayX+=xo; rayY+=yo; dof+=1;}
        }

        //Vertical Lines
        dof=0;
        float disV=1000000,vx=playerX,vy=playerY;
        float nTan=-tan(rayAngle);
        if(rayAngle>P2 && rayAngle<P3){ rayX=(((int)playerX/mapSize)*mapSize)-0.0001; rayY=(playerX-rayX)*nTan+playerY; xo=-mapSize; yo=-xo*nTan; }
        if(rayAngle<P2 || rayAngle>P3){ rayX=(((int)playerX/mapSize)*mapSize)+mapSize; rayY=(playerX-rayX)*nTan+playerY; xo=mapSize; yo=-xo*nTan; }
        if(rayAngle==0 || rayAngle==PI){ rayX=playerX; rayY=playerY; dof=mapX;}
        
        while(dof<mapX)
        {
            mx=(int)(rayX)/mapSize; my=(int)(rayY)/mapSize; mp=my*mapX+mx;
            if(mp>0 && mp<mapX*mapY && map[mp]==1) { vx=rayX; vy=rayY; disV=dist(playerX, playerY, vx, vy, rayAngle); dof=mapX; }
            else{ rayX+=xo; rayY+=yo; dof+=1;}
        }

        if(disV<disH){ rayX=vx; rayY=vy; disT=disV; }
        if(disV>disH){ rayX=hx; rayY=hy; disT=disH; clrLine = C2D_Color32(0xFF, 0x77, 0x59, 0xCF); }

        u32 clrLine1 = C2D_Color32(0xFF, 0x68, 0xA9, 0xFF);
        u32 clrLine2 = C2D_Color32(0xFF, 0xAF, 0x3C, 0xFF);

        //C2D_DrawLine(playerX, playerY, clrLine1, rayX, rayY, clrLine2, 1, 0);

        //3D Walls
        float ca=playerAngle-rayAngle; 
        if (ca<0) { ca+=2*PI;} if (ca>2*PI) { ca-=2*PI;} disT=disT*cos(ca); 
        
        float lineH=(mapSize*240)/disT; //Line height
        if(lineH>240){lineH=240;}

        float lineO=160-lineH/2; //Offset
            
        

        C2D_DrawLine(r*8, lineO, clrLine, r*8, lineH+lineO, clrLine, 8, 0);
        
        rayAngle+=DR;
        if (rayAngle<0) { rayAngle+=2*PI;} if (rayAngle>2*PI) { rayAngle-=2*PI;} 

    }

}

