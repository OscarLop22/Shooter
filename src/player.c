#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <citro2d.h>
#include <citro3d.h>

#include "world.h"

#define PI 3.1415926535


float px = 0;
float py = 0;
float pdx = 0;
float pdy = 0;
float pa = 0;
float ps = 0;


void initPlayer()
{
	px=100;
    py=100;
    pdx=cos(pa)*5; pdy=sin(pa)*5;
    ps=8;
}


void drawPlayer()
{
    float half = ps/2.0f;
    u32 clrRec1 = C2D_Color32(0x9A, 0x6C, 0xB9, 0xFF);
	u32 clrRec2 = C2D_Color32(0xFF, 0xFF, 0x2C, 0xFF);
	u32 clrRec3 = C2D_Color32(0xD8, 0xF6, 0x0F, 0xFF);
	u32 clrRec4 = C2D_Color32(0x40, 0xEA, 0x87, 0xFF);
    C2D_DrawRectangle(px-half, py-half, 0, ps, ps, clrRec1, clrRec2, clrRec3, clrRec4);

    u32 clrLine1 = C2D_Color32(0x9A, 0x6C, 0xB9, 0xFF);
    u32 clrLine2 = C2D_Color32(0xFF, 0xFF, 0x2C, 0xFF);

    C2D_DrawLine(px, py, clrLine1, px+pdx*5, py+pdy*5, clrLine2, 2, 0);
}

void movePlayer(u32 kHeld)
{
    if (kHeld & KEY_DUP) {px+=pdx; py+=pdy;}
    if (kHeld & KEY_DDOWN) {px-=pdx; py-=pdy;}
    if (kHeld & KEY_DLEFT) { pa-=0.1; if(pa<0){ pa+=2*PI; } pdx=cos(pa)*5; pdy=sin(pa)*5; }
    if (kHeld & KEY_DRIGHT) { pa+=0.1; if(pa>2*PI){ pa-=2*PI; } pdx=cos(pa)*5; pdy=sin(pa)*5; }


}


void drawRays3D()
{
    int r,mx,my,mp,dof; float rx,ry,ra,xo,yo;

    ra=pa;
    for(r=0;r<1;r++)
    {
        dof=0;
        float aTan=-1/tan(ra);
        if(ra>PI){ ry=(((int)py/mapS)*mapS)-0.0001; rx=(py-ry)*aTan+px; yo=-mapS; xo=-yo*aTan; }
        if(ra<PI){ ry=(((int)py/mapS)*mapS)+mapS; rx=(py-ry)*aTan+px; yo=mapS; xo=-yo*aTan; }
        if(ra==0 || ra==PI){ rx=px; ry=py; dof=mapX;}
        while(dof<mapX)
        {
            mx=(int)(rx)/mapS; my=(int)(ry)/mapS; mp=my*mapX+mx;
            if(mp<mapX*mapY && map[mp]==1) { dof=mapX; }
            else{ rx+=xo; ry+=yo; dof+=1;}
        }

        u32 clrLine1 = C2D_Color32(0xFF, 0x68, 0xA9, 0xFF);
        u32 clrLine2 = C2D_Color32(0xFF, 0xAF, 0x3C, 0xFF);

        C2D_DrawLine(px, py, clrLine1, rx, ry, clrLine2, 1, 0);

    }
}
