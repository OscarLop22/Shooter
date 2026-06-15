//using namespace std;

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <citro2d.h>
#include <citro3d.h>
#include <3ds.h>

#include "input.h"
#include "ctr_gfx.h"
#include "world.h"
#include "player.h"

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240
#define CLEAR_COLOR 0x747574FF


int main(int argc, char* argv[])
{  
    romfsInit();
    initGraphics();
    loadSprites();
    initMapValues();
    initPlayer();

    generateMap();

	u32 clrClear = C2D_Color32(0x47, 0x75, 0x74, 0xFF);

    while (aptMainLoop())
	{
        updateInput();

        movePlayer(kHeld);

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
            C2D_TargetClear(bottom, clrClear);
			C2D_SceneBegin(bottom);
            drawMap2D();
            drawPlayer();

        	C2D_TargetClear(top, clrClear);
			C2D_SceneBegin(top);
 
            //drawWalls();
            
            drawRays3D();


        C3D_FrameEnd(0);

    }
    freeSprites();
    return 0;
}