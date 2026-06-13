#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>


int mapX=0, mapY=0, mapS=0;
int map[64] = {0};

void initMapValues()
{
    mapX=8, mapY=8, mapS=32;
}


void generateMap()
{
    int tmp[]=
        {
            1,1,1,1,1,1,1,1,
            1,0,0,0,0,0,0,1,
            1,0,0,0,1,1,0,1,
            1,0,0,0,0,0,0,1,
            1,1,1,1,0,0,0,1,
            1,0,0,1,0,0,0,1,
            1,0,0,0,0,0,0,1,
            1,1,1,1,1,1,1,1,

        };

    
    for (int i = 0; i < mapX*mapY; i++)
        map[i] = tmp[i];

}



void drawMap2D()
{
    int x,y,xo,yo;
    for(y=0;y<mapY;y++)
    {
        for(x=0;x<mapX;x++)
        {
            u32 clrWall1 = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
            u32 clrWall2 = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
            u32 clrWall3 = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
            u32 clrWall4 = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
            if(map[y*mapX+x]==1){
                clrWall1 = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
                clrWall2 = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
                clrWall3 = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
                clrWall4 = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
            }
            xo=x*mapS; yo=y*mapS;
            C2D_DrawRectangle(xo, yo, 0, mapS-1, mapS-1, clrWall1, clrWall2, clrWall3, clrWall4);

        }
    }
}