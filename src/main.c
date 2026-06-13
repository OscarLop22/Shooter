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
    initMapValues();
    generateMap();
    initPlayer();

	u32 clrClear = C2D_Color32(0x47, 0x75, 0x74, 0xFF);

    while (aptMainLoop())
	{
        updateInput();

        movePlayer(kHeld);

        C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
        	C2D_TargetClear(top, clrClear);
			C2D_SceneBegin(top);
            //C3D_RenderTargetClear(top, C3D_CLEAR_ALL, CLEAR_COLOR, 0);
			//C3D_FrameDrawOn(top);
            
            drawMap2D();
            drawRays3D();
            drawPlayer();
      
        C3D_FrameEnd(0);

    }
    return 0;
}