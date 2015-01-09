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
	HEFFECT		      snd;                     // 鼠标点击的声音
	HEFFECT				snd1;
	HEFFECT				snd2;
	HEFFECT				snd3;
	HEFFECT             boomMusic;
	HEFFECT             placeMusic;
	HCHANNEL            channel;

	HTEXTURE          cur;                     // 鼠标的图片
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
	bool            p1Bkey;          // 检测放炸弹的键是否被按下，如果被按下，直到键被释放前不再放新的炸弹。
	bool            p2Bkey;
	double          player1Clamp;
	double          player1ClampColdTime;    // 被夹子夹的冷却时间
	double          player2Clamp;
	double          player2ClampColdTime;
	bool            inGame;          // 是否在进行游戏，如果不是，则在进行界面操作
	bool            isGameOver;        // 游戏是否结束
	Tools           *tools[100];
	Boom			*boom[100];
	HCHANNEL        boomChannel[100];
	int             BoomListHead,BoomListTail;
	PERSON_STATE    walkorstand;
	Map				*Game_Map;
	bool            toolsPlaced[100];//判断道具放置
	bool            isPlace[100];	//判断放置泡泡
	bool            isExplode[100];		//判断放置泡泡
	bool            pause;               // 表征游戏是否被暂停
	double          gameTime;           // 游戏时间
	int             player1home;
	int             player2home;

	int             monsternum;          //总共怪兽的数量
	int             toolsnum;            //总共道具的数量

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
	void start();                                                 // 整个游戏程序开始
	void menuStart();                                             // 界面开始
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
	bool bombHero(int boomIndex, double x, double y);                      // 判断玩家或怪兽是否在炸弹的爆炸范围内，如果在，则返回true
	bool noOtherBomb(int x, int y);
	bool canHeroPassBomb(double x, double y, DIRECTION dir);                             //  判断是否有炸弹挡住英雄，如果有，英雄不能穿过
	static bool FrameFunc();
	static bool RenderFunc();
	bool menuFrameFunc();
	bool menuRenderFunc();
	bool gameFrameFunc();
	bool gameRenderFunc();
	bool heroHitMonster(Hero *p, Monster *m);
	bool heroHitTools(Hero *p, Tools *t);
	void bombTool(int i, int j);                                     // 炸弹会炸掉经过位置的tool
	static Game* pThis;
};

hgeGUIText* getText(hgeGUIText *text, char * buff, DWORD color);//对文本框内的文字及颜色进行设置




#endif
