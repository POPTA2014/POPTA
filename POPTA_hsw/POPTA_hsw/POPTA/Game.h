#ifndef _GAME_H_
#define _GAME_H_
#include <iostream>
#include "Map.h"
#include "Hero.h"
#include "Monster.h"
#include "Interface.h"
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeanim.h>
#include <time.h>
#include "Boom.h"

using namespace std;

class Game
{
private:
	
	HGE *hge;

	// Some resource handles
	HEFFECT		      snd;
	HTEXTURE          player1Pic;
	HTEXTURE		  player2Pic;
	HTEXTURE          tex2;
	HTEXTURE          texPopo;
	HTEXTURE          texPopoDir;
	HTEXTURE          texPopoCen;
	HTEXTURE		  mapPic;
	hgeQuad           quad;

	Hero            *player1;
	Hero            *player2;
	bool            p1Bkey;          // ����ը���ļ��Ƿ񱻰��£���������£�ֱ�������ͷ�ǰ���ٷ��µ�ը����
	bool            p2Bkey;
	hgeAnimation	*placeBoom;
	hgeAnimation    *Popo;
	hgeAnimation    *effect;
	Boom			*boomP1;
	Boom			*boom[100];
	int             BoomListHead,BoomListTail;
	PERSON_STATE    walkorstand;
	Map				*Game_Map;
	bool            isPlace[100];	//�жϷ�������
	bool            isExplode[100];		//�жϷ�������
	int				boomNum_p1,boomNum_p2;

	// Pointers to the HGE objects we will use
	hgeGUI            *gui;
	hgeFont           *fnt;
	hgeSprite         *spr;
	hgeSprite         *pic;
	hgeSprite         *popoBoom;
	hgeSprite         *p[16];
	
	
public:
	Game(){ pThis = this;};
	~Game(){};
	void gameStart();
	bool gameOver();
	bool warBegin();
	bool warEnd();
	void loadMap();
	void gamePause();
	bool gameSave();
	void dataClean();
	void createHeroes();
	void createMonsters();
	void addBoom(int x, int y, int L, int w);
	void checkBoom();
	void initBoomList();
	void heroAction();
	void monsterAction();
	void warProcess();
	bool bombHero(int boomIndex, Hero* p);;                      // �ж�����Ƿ���ը���ı�ը��Χ�ڣ�����ڣ��򷵻�true
	bool noOtherBomb(int x, int y);
	bool canHeroPassBomb(int x, int y, DIRECTION dir);;          //  �ж��Ƿ���ը����סӢ�ۣ�����У�Ӣ�۲��ܴ���
	static bool gameFrameFunc();
	static bool gameRenderFunc();
	static Game* pThis;
};


#endif
