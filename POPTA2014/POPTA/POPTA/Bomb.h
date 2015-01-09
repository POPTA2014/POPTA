#ifndef _BOMB_H_
#define _BOMB_H_

class Bomb
{
private:
	int position_x[20];													//炸弹x位置
	int position_y[20];													//炸弹y位置
	int belong[20];														//炸弹是谁放置的
	int lethality[20];													//炸弹威力
	int time[20];														//炸弹的放置时刻
	int queue_head;														//炸弹队列的对头位置
	int number;															//炸弹的数量
	int blast_position_x;												//爆炸的炸弹x位置
	int blast_position_y;												//爆炸的炸弹y位置
	int blast_lethality;												//爆炸的炸弹的威力
	int blast_belong;													//爆炸的炸弹是谁放置的

public:
	Bomb();
	~Bomb(){};
	void addBomb(int x, int y, int belong, int lethality, int time);	//向炸弹队列里添加一个炸弹
	bool checkBomb();													//检测炸弹是否爆炸
	int getBlastPositionX();											//获得爆炸的炸弹x位置
	int getBlastPositionY();											//获得爆炸的炸弹y位置
	int getBlastLethality();											//获得爆炸的炸弹的威力
	int getBlastBelong();												//获得爆炸的炸弹是谁放置的
};

#endif
