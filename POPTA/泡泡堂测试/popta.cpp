#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeanim.h>
#include <math.h>
#include "person.h"
#include "map.h"


HGE *hge = 0;

// Some resource handles
HEFFECT		      snd;
HTEXTURE          tex1;
HTEXTURE          tex2;
HTEXTURE          tex;
hgeQuad           quad;

person			*player;
map				*Game_Map;
	
// Pointers to the HGE objects we will use
hgeGUI            *gui;
hgeFont           *fnt;
hgeSprite         *spr;
hgeSprite         *pic;

bool FrameFunc()
{
	DIRECTION dir = NO;
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;
	if(hge->Input_GetKeyState(HGEK_LEFT))
		dir = LEFT;
	else if(hge->Input_GetKeyState(HGEK_UP))
		dir = UP;
	else if(hge->Input_GetKeyState(HGEK_DOWN))
		dir = DOWN;
	else if(hge->Input_GetKeyState(HGEK_RIGHT))
		dir = RIGHT;

	float fDeltaTime = hge->Timer_GetDelta();

	if(dir == NO){
        player->Stop();
	}else{
        player->setDirection(dir);
        player->Move(SPEED, fDeltaTime);
        player->Update(fDeltaTime, dir);
	}

	return false;
}


bool RenderFunc()
{
	// Render graphics
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	fnt->printf(5, 5, HGETEXT_LEFT, "FPS:%d  x:%d  y:%d", hge->Timer_GetFPS(), player->getX(), player->getY());
	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 20; j++)
			pic->Render(i * 40, j * 40);
	player->Render();
	hge->Gfx_EndScene();

	return false;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd )
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "POPTA");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, MAP_SIZE[0]);
	hge->System_SetState(HGE_SCREENHEIGHT, MAP_SIZE[1]);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_USESOUND, false);

	int Ini_Stage[BOX_NUM][BOX_NUM] = {{0}};
	Game_Map = new map(hge, Ini_Stage);

	if(hge->System_Initiate()){
		tex1 = hge->Texture_Load("walk.png");
		pic = new hgeSprite(tex, 0, 0, BOX_WIDTH, BOX_LENGTH);
		fnt = new hgeFont("font1.fnt");
		player = new person(tex1, 4, 8, 100, 100);
		player->setX(400);
		player->setY(400);
		player->Play(LEFT);
		hge->System_Start();


		// Delete created objects and free loaded resources
		delete gui;
		delete fnt;
		delete spr;
		hge->Effect_Free(snd);
		hge->Texture_Free(tex1);
		hge->Texture_Free(tex2);
		hge->Texture_Free(quad.tex);
	}

	// Clean up and shutdown
	//hge->System_Shutdown();
	//hge->Release();
	return 0;
}
	







