#ifndef _HERO_H_
#define _HERO_H_
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeanim.h>
#include "Boom.h"
#include "Tools.h"
#include <string>
using namespace std;


//#define DOWN 0
//#define LEFT 1
//#define RIGHT 2
//#define Up   3
enum DIRECTION{NO=-1,DOWN, LEFT, RIGHT, UP};
//#define STAND 0
//#define WALK 1
enum PERSON_STATE{STAND, WALK};
enum OCCUPATION{Saber, Assassin, Basaker};

class Hero
{
private:
	double move_speed;							//移动速度
	double position_x, position_y;					//英雄位置
	double startPosition_x, startPosition_y;    // 英雄初始位置，用于初始化以及英雄死后的定位
	bool is_walking;                            //英雄是在行走
	bool is_dead;								//英雄是否死亡
	double dead_time;								//死亡累计时间
	double reborn_time;                          // 重生的时间
	int boom_limit;								//炸弹数量限制
	int boom_number;							//目前已放置炸弹数量
	int boom_lethality;							//炸弹威力
	int tools_kind[10];							//拥有的道具种类
	int tools_number;							//拥有的道具数量
	bool is_skill_prepared;						//技能是否可以使用
	char* soccupation;
	OCCUPATION occupation;                      //英雄的职业
	PERSON_STATE     person_state;		//代表人物静止还是移动
	hgeAnimation* dir_image[4]; //分别掌控四个方向的图片
	DIRECTION		person_direction;	//人物的方向
public:
	Hero();										//
	Hero(HTEXTURE tex, int nframes, float FPS, float w, float h);
	~Hero();									//
	void checkTime();							//检查各种时间关系
	void skillBegin();				//技能起效，英雄属性改变
	virtual void skillEnd();;					//技能结束，英雄回复原属性
	void heroMove(int direction);				//英雄移动
	void getTools(ToolsKind toolskind);				//得到道具
	void heroDie();								//英雄死亡
	void heroRevive();							//英雄重生
	bool isDead();                             //英雄是否已经死亡
	void putBoom();								//放置炸弹
	bool canPutBoom();
	void setBoomLimit(int n);
	int getBoomLimit();
	void wantReborn(double fDeltaTime);                     // 判断英雄是否该重生
	double getX();							//获取当前英雄x位置
	double getY();							//获取当前英雄y位置
	int getLethality();							//获取炸弹威力
	double getSpeed();
	void setX(double x);						//设置英雄x位置
	void setY(double y);						//设置英雄y位置
	void boomExp();
	void setDirection(DIRECTION direction);
	void Update(float fDeltaTime, DIRECTION direction = NO);
	void Render(float x = -1, float y = -1);
	void setOccupation(OCCUPATION occ);
	void Stop();
	void Play();
	void Play(DIRECTION directionh);
	void Move(float fDeltaTime);
	void set_person_state(PERSON_STATE _person_state);
	void placeBoom(hgeAnimation	*placeBoom, float fDeltaTime);
	bool isWalking() const;;
	void setStartSite(double x, double y);
	void toStartSite();                              // 让英雄回到初始位置
	double getReviveTime()const;                       // 获得复活时间
	int    getLeftBomb() const;                       // 获得剩余的炸弹量
	char* getOccupation() const;

	PERSON_STATE get_person_state();
	DIRECTION getDirection(); 
	int Draw();
};

#endif

