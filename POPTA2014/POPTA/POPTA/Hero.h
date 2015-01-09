#ifndef _HERO_H_
#define _HERO_H_

class Hero
{
private:
	double move_speed;							//移动速度
	int position_x, position_y;					//英雄位置
	bool is_dead;								//英雄是否死亡
	int dead_time;								//死亡时刻
	int bomb_limit;								//炸弹数量限制
	int bomb_number;							//目前已放置炸弹数量
	int bomb_lethality;							//炸弹威力
	int bomb_position_x, bomb_position_y;		//正在放置炸弹的位置
	int put_bomb_time;							//正在放置炸弹的时刻
	bool has_rider;								//是否具有坐骑
	int tools_kind[10];							//拥有的道具种类
	int tools_number;							//拥有的道具数量
	int skill_using_time;						//技能使用时刻
	int skill_time;								//技能持续时间
	int cold_time;								//技能冷却时间
	bool is_skill_prepared;						//技能是否可以使用

public:
	Hero();										//
	~Hero(){};									//
	void usingSkill();							//英雄使用技能
	void checkTime();							//检查各种时间关系
	virtual void skillBegin(){};				//技能起效，英雄属性改变
	virtual void skillEnd(){};					//技能结束，英雄回复原属性
	void heroMove(int direction);				//英雄移动
	void getTools(int toolskind);				//得到道具
	void heroDie();								//英雄死亡
	void heroRevive();							//英雄重生
	bool putBomb();								//放置炸弹
	int getBombPositionX();						//获取正在放置炸弹的x位置
	int getBombPositionY();						//获取正在放置炸弹的y位置
	int getBombTime();							//获取正在放置炸弹的时间
	int getPositionX();							//获取当前英雄x位置
	int getPositionY();							//获取当前英雄y位置
	int getLethality();							//获取炸弹威力
	void setPositionX();						//设置英雄x位置
	void setPositionY();						//设置英雄y位置
};

#endif
