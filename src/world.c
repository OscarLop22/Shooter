#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>

#include "ctr_gfx.h"

int mapX=0, mapY=0, mapSize=0;
int map[64] = {0};


void initMapValues()
{
    mapX=8, mapY=8, mapSize=32;
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
            //u32 clrWall = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
		    C2D_Sprite* sprite = &sprites[x];

            C2D_SpriteFromSheet(sprite, spriteSheet, 1);
  

            if(map[y*mapX+x]==1){
                //clrWall = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);
                C2D_SpriteFromSheet(sprite, spriteSheet, 0);

            }
            xo=x*mapSize; yo=y*mapSize;

            //C2D_SpriteSetCenter(sprite, 0.5f, 0.5f);
            C2D_SpriteSetPos(sprite, xo, yo);
            C2D_SpriteSetRotation(sprite, 0);
            //sprite->dx = rand()*4.0f/RAND_MAX - 2.0f;
            //sprite->dy = rand()*4.0f/RAND_MAX - 2.0f;
            
            C2D_DrawSprite(sprite);
            //C2D_DrawRectangle(xo, yo, 0, mapS-1, mapS-1, clrWall, clrWall, clrWall, clrWall);

        }
    }
}
