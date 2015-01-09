#pragma once
#include <hge.h>
#include "Map.h"
#include "Hero.h"

const float SPEED = 80;

class Monster//野怪类
{
public:
	Monster(void);
	Monster(HTEXTURE tex, int neframes, float FPS, float w, float h);
	~Monster(void);
	double getX();
	double getY();//获取野怪x,y坐标
	void setPosition(double x,double y);//设定野怪位置
	void Update(float fDeltaTime, DIRECTION direction);
	void Render(float x = -1, float y = -1);
	void checkTime();//检查时间关系
	void monsterDie();//野怪死亡函数
	void monsterRevive();//野怪复活函数
	void Move(float fDeltaTime);//野怪移动的函数
	void Play();
	void Play(DIRECTION monster_direction);
	void Stop();
	void getHeroPosition(Hero* hero1, Hero* hero2);//得到英雄位置信息
	int moveJudge();//判断区域内情景
	DIRECTION directionJudge(int hero,int hero_no);//根据区域内有无英雄判断野怪移动的方向
	DIRECTION getDirection();//得到怪物当前方向
	void setDirection(DIRECTION direction);//设置怪物方向
	void setStartSite(double x, double y);//设置怪物出生点
	void toStartSite();//设置怪物位置到出生点
	bool isDead();//判断野怪是否死亡
	bool isMonsterIn(DIRECTION direction,float fDeltaTime);//判断野怪移动后是否在野怪区内
	void wantReborn(double fDeltaTime);//判断野怪是否该重生

private:
	double position_x;
	double position_y;//野怪位置x,y
	double startPosition_x;
	double startPosition_y;//野怪出生位置x,y
	double move_speed;//野怪速度
	bool is_dead;
	double dead_time;
	double reborn_time;
	static double hero_position[2][2];//英雄位置信息
	DIRECTION monster_direction;//怪物方向
	hgeAnimation* dir_image[4];//分别掌控四个方向的图片
};


