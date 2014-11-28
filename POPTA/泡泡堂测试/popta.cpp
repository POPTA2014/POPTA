#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeanim.h>
#include <math.h>
#include "person.h"
#include "map.h"
#include <time.h>


HGE *hge = 0;

// Some resource handles
HEFFECT		      snd;
HTEXTURE          tex1;
HTEXTURE          tex2;
HTEXTURE          tex;
HTEXTURE          texPopo;
HTEXTURE          effecttex;
HTEXTURE		  bigPopo;
HTEXTURE		  maptex;
hgeQuad           quad;

person			*player;
hgeAnimation	*placeBoom;
hgeAnimation    *Popo;
hgeAnimation    *effect;
PERSON_STATE     walkorstand;
map				*Game_Map;
bool            isWalking;
	
// Pointers to the HGE objects we will use
hgeGUI            *gui;
hgeFont           *fnt;
hgeSprite         *spr;
hgeSprite         *pic;
hgeSprite         *popoBoom;
hgeSprite         *p[16];
int index[20][20];
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
	else{
	};
	if(hge->Input_GetKeyState(HGEK_SPACE))           //place the boom
		;//
	else{
	};

float fDeltaTime = hge->Timer_GetDelta();

	if(dir == NO){
        player->Stop();
		isWalking = false;
		effect->Update(fDeltaTime);
		Popo->Update(fDeltaTime);
	}else{
		if(!isWalking)	
		{
			player->Play();
			effect->Play();
			Popo->Play();
		}
        player->setDirection(dir);
        player->Move(SPEED, fDeltaTime);
        player->Update(fDeltaTime, dir);
		isWalking = true;
		//effect->Stop();
		//Popo->Stop();
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
			p[index[i][j]]->Render(i * 40, j * 40);
	player->Render();
	effect->Render(140, 140);
	Popo->Render(280, 280);
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
	srand((unsigned)time(NULL));
	for(int i = 0; i < 20; i++)
		for(int j = 0; j < 20; j++)
			index[i][j] = rand() % 16;

	if(hge->System_Initiate()){
		tex1 = hge->Texture_Load("walk.png");
		tex = hge->Texture_Load("wall1.png");
		maptex = hge->Texture_Load("maptype1.png");
		pic = new hgeSprite(tex, 0, 0, BOX_WIDTH - 20, BOX_LENGTH);
		p[0] = new hgeSprite(tex, 0, 0, BOX_WIDTH - 20, BOX_LENGTH);
		fnt = new hgeFont("font1.fnt");
		player = new person(tex1, 4, 8, 100, 100);
		for(int i = 0; i < 16; i++){
			p[i] = new hgeSprite(maptex, 40*i, 0, 40, 40);
		}
		player->setX(400);
		player->setY(400);
		player->Play(LEFT);
		texPopo = hge->Texture_Load("Popo.png");
		bigPopo = hge->Texture_Load("BigPopo.png");
		effecttex = hge->Texture_Load("Explosion.png");
		placeBoom = new hgeAnimation(texPopo, 4, 8, 0, 0, 40, 40);
		effect = new hgeAnimation(effecttex, 14, 8, 0, 0, 40, 80);
		Popo = new hgeAnimation(bigPopo, 8, 8, 0, 0, 72, 72);
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
	







