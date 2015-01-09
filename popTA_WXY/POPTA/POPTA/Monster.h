#pragma once

class Monster//野怪类
{
public:
	Monster(void);//构造函数
	~Monster(void);
	double getPosition_x();
	double getPosition_y();//获取野怪x,y坐标
	void setPosition(double x,double y);//设定野怪位置
	void display();//显示野怪的函数
	void disappear();//野怪消失函数
	void move();//野怪移动的函数
	void die();//野怪死亡函数(调用野怪消失函数)

private:
	double position_x[10];//野怪位置x,初始化为10
	double position_y[10];//野怪位置y,初始化为10
};
