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
#include "menuitem.h"
#include "GUI_edit.h"
#include "Tools.h"
#include <cmath>

using namespace std;

struct Info{
	int hero1_info;
	int hero2_info;
	int map_info;
	OCCUPATION hero1_occ;
	OCCUPATION hero2_occ;
};

enum INFO{Pause=7,Rstart,Return};

class Game
{
private:
	
	HGE *hge;

	// Some resource handles
	HEFFECT		      snd;                     // �����������
	HEFFECT				snd1;
	HEFFECT				snd2;
	HEFFECT				snd3;
	HEFFECT             boomMusic;
	HEFFECT             placeMusic;
	HCHANNEL            channel;

	HTEXTURE          cur;                     // ����ͼƬ
	HTEXTURE          player1Pic;
	HTEXTURE		  player2Pic;
	HTEXTURE          monster1Pic;
	HTEXTURE		  monster2Pic;
	HTEXTURE          textool1;
	HTEXTURE          textool2;
    HTEXTURE          textool3;
	HTEXTURE          textool4;
	HTEXTURE          textool5;
	HTEXTURE          texPopo;
	HTEXTURE          texPopoDir;
	HTEXTURE          texPopoCen;
	HTEXTURE		  mapPic;
	HTEXTURE          gameInfo;

	Hero            *player1;
	Hero            *player2;
	Monster         *monster[5];
	bool            p1Bkey;          // ����ը���ļ��Ƿ񱻰��£���������£�ֱ�������ͷ�ǰ���ٷ��µ�ը����
	bool            p2Bkey;
	double          player1Clamp;
	double          player1ClampColdTime;    // �����Ӽе���ȴʱ��
	double          player2Clamp;
	double          player2ClampColdTime;
	bool            inGame;          // �Ƿ��ڽ�����Ϸ��������ǣ����ڽ��н������
	bool            isGameOver;        // ��Ϸ�Ƿ����
	Tools           *tools[100];
	Boom			*boom[100];
	HCHANNEL        boomChannel[100];
	int             BoomListHead,BoomListTail;
	PERSON_STATE    walkorstand;
	Map				*Game_Map;
	bool            toolsPlaced[100];//�жϵ��߷���
	bool            isPlace[100];	//�жϷ�������
	bool            isExplode[100];		//�жϷ�������
	bool            pause;               // ������Ϸ�Ƿ���ͣ
	double          gameTime;           // ��Ϸʱ��
	int             player1home;
	int             player2home;

	int             monsternum;          //�ܹ����޵�����
	int             toolsnum;            //�ܹ����ߵ�����

	// Pointers to the HGE objects we will use
	hgeGUI            *gui;
	hgeGUI            *gameGUI;
	hgeFont           *fnt;
	hgeSprite         *spr;

	// menu
	//--back pic
	HTEXTURE			back;
	HTEXTURE			back_1, back_2, back_3, back_4, button;

	hgeSprite           *gameInfoSprite;
	hgeSprite			*backSpr;
	hgeSprite			*back1Spr, *back2Spr, *back3Spr, *back4Spr;
	hgeSprite			*showSpr;
	
	hgeGUIText			*error_text;
	hgeGUIText          *herotype1;
	hgeGUIText          *herotype2;
	hgeGUIText           *player1Text;
	hgeGUIText           *player2Text;
	hgeGUIText           *map;
	hgeGUIText           *maptype;
	struct Info menu_info;
	
public:
	Game();
	~Game();
	void start();                                                 // ������Ϸ����ʼ
	void menuStart();                                             // ���濪ʼ
	void menuOver();
	void gameStart();
	void gameMenu(hgeGUI *gui);
	void gameOver();
	bool warBegin();
	bool warEnd();
	void loadMap();
	void gamePause();
	bool gameSave();
	void dataClean();
	void createHeroes();
	void createMonsters();
	void addBoom(int x, int y, int L, int w);
	void addTool(ToolsKind toolskind, int x, int y);
	void checkBoom();
	void initToolsList();
	void initBoomList();
	void heroAction();
	void monsterAction();
	void warProcess();
	bool bombHero(int boomIndex, double x, double y);                      // �ж���һ�����Ƿ���ը���ı�ը��Χ�ڣ�����ڣ��򷵻�true
	bool noOtherBomb(int x, int y);
	bool canHeroPassBomb(double x, double y, DIRECTION dir);                             //  �ж��Ƿ���ը����סӢ�ۣ�����У�Ӣ�۲��ܴ���
	static bool FrameFunc();
	static bool RenderFunc();
	bool menuFrameFunc();
	bool menuRenderFunc();
	bool gameFrameFunc();
	bool gameRenderFunc();
	bool heroHitMonster(Hero *p, Monster *m);
	bool heroHitTools(Hero *p, Tools *t);
	void bombTool(int i, int j);                                     // ը����ը������λ�õ�tool
	static Game* pThis;
};

hgeGUIText* getText(hgeGUIText *text, char * buff, DWORD color);//���ı����ڵ����ּ���ɫ��������




#endif
