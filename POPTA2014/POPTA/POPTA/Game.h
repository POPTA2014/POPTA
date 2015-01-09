#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include "Hero.h"
#include "Map.h"
#include "Monster.h"
#include "Interface.h"
#include "Bomb.h"

using namespace std;

class Game
{
private:
	Map war_map;						//定义地图
	Hero * heroA;						//定义玩家1的英雄A，可以选择英雄种类
	Hero * heroB;						//定义玩家2的英雄B，可以选择英雄种类
	Monster * monster[5];				//定义5只怪兽，怪兽种类可变
	Interface game_interface;			//定义界面对象，用于显示动画、获取键盘、鼠标信息
	Bomb bomb;						//定炸弹

public:
	Game(){};				
	~Game(){};
	void gameStart();					//启动游戏
	bool gameOver();					//结束游戏
	bool warBegin();					//一场战争开始
	bool warEnd();						//一场战争结束
	bool loadMap(int mapname);			//载入地图
	void gamePause();					//暂停游戏
	bool gameSave();					//存储游戏
	void dataClean();					//一场游戏结束，清除数据
	void createHeroes();				//创建英雄
	void createMonsters();				//创建怪兽
	void checkBomb();					//检查炸弹是否爆炸
	void heroAction(int x);				//英雄动作
	void monsterAction(int x);			//怪兽动作
	void warProcess();					//战争过程
};

#endif
