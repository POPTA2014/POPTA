#ifndef _HERO_H_
#define _HERO_H_
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeanim.h>
#include "Boom.h"


//#define DOWN 0
//#define LEFT 1
//#define RIGHT 2
//#define Up   3
enum DIRECTION{NO=-1,DOWN, LEFT, RIGHT, UP};
//#define STAND 0
//#define WALK 1
enum PERSON_STATE{STAND, WALK};

class Hero
{
private:
	double move_speed;							//移动速度
	double position_x, position_y;					//英雄位置
	bool is_walking;                            //英雄是在行走
	bool is_dead;								//英雄是否死亡
	int dead_time;								//死亡时刻
	int boom_limit;								//炸弹数量限制
	int boom_number;							//目前已放置炸弹数量
	int boom_lethality;							//炸弹威力
	int boom_position_x, boom_position_y;		//正在放置炸弹的位置
	int put_boom_time;							//正在放置炸弹的时刻
	bool has_rider;								//是否具有坐骑
	int tools_kind[10];							//拥有的道具种类
	int tools_number;							//拥有的道具数量
	int skill_using_time;						//技能使用时刻
	int skill_time;								//技能持续时间
	int cold_time;								//技能冷却时间
	bool is_skill_prepared;						//技能是否可以使用
	PERSON_STATE     person_state;		//代表人物静止还是移动
	hgeAnimation* dir_image[4]; //分别掌控四个方向的图片
	DIRECTION		person_direction;	//人物的方向
public:
	Hero();										//
	Hero(HTEXTURE tex, int nframes, float FPS, float w, float h);
	~Hero();									//
	void usingSkill();							//英雄使用技能
	void checkTime();							//检查各种时间关系
	virtual void skillBegin();;				//技能起效，英雄属性改变
	virtual void skillEnd();;					//技能结束，英雄回复原属性
	void heroMove(int direction);				//英雄移动
	void getTools(int toolskind);				//得到道具
	void heroDie();								//英雄死亡
	void heroRevive();							//英雄重生
	void putBoom();								//放置炸弹
	bool canPutBoom();
	void setBoomLimit(int n);
	int getBoomLimit();
	double getPositionX();							//获取当前英雄x位置
	double getPositionY();							//获取当前英雄y位置
	int getLethality();							//获取炸弹威力
	void setPositionX(double x);						//设置英雄x位置
	void setPositionY(double y);						//设置英雄y位置
	void boomExp();
	void setDirection(DIRECTION direction);
	void Update(float fDeltaTime, DIRECTION direction = NO);
	void Render(float x = -1, float y = -1);
	void Stop();
	void Play();
	void Play(DIRECTION directionh);
	void Move(float fDeltaTime);
	void set_person_state(PERSON_STATE _person_state);
	void placeBoom(hgeAnimation	*placeBoom, float fDeltaTime);
	bool isWalking() const;;
	PERSON_STATE get_person_state();
	DIRECTION getDirection(); 
	int Draw();
};

#endif

