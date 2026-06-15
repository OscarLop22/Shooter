#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include <3ds.h>
#include <citro2d.h>
#include <citro3d.h>


C3D_RenderTarget* top = 0;
C3D_RenderTarget* bottom = 0;
C2D_SpriteSheet spriteSheet;
C2D_Sprite sprites[100];


void initGraphics(){
    gfxInitDefault();

	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    
    C2D_Prepare();

    top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
  
}


void loadSprites()
{
    spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
	if (!spriteSheet) svcBreak(USERBREAK_PANIC);
}

void freeSprites()
{
    C2D_SpriteSheetFree(spriteSheet);

}