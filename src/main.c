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

#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240
#define CLEAR_COLOR 0x747574FF
#define PI 3.1415926535

float px,py,pdx,pdy,pa, ps = 8; //player position
int mapX=8, mapY=8, mapS=32;
int map[]=
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

/*
void display()
{

}
*/
void init()
{
	px=100;
    py=100;
    pdx=cos(pa)*5; pdy=sin(pa)*5;
}


int main(int argc, char* argv[])
{  
    romfsInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
    C2D_Prepare();
	u32 clrClear = C2D_Color32(0x47, 0x75, 0x74, 0xFF);
    C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
    init();
    while (aptMainLoop())
	{
        hidScanInput();

        u32 kDown = hidKeysDown();
		u32 kHeld = hidKeysHeld();
		u32 kUp = hidKeysUp();

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