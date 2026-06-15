#ifndef CTR_GFX_H
#define CTR_GFX_H

extern C3D_RenderTarget* top;
extern C3D_RenderTarget* bottom;
extern C2D_SpriteSheet spriteSheet;
extern C2D_Sprite sprites[100];


void initGraphics();
void loadSprites();
void freeSprites();

#endif