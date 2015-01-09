#ifndef _MAP_H_
#define _MAP_H_

class Map
{
private:
	int * map_data;												//目前地图上的东西
	int * map_data_0;											//初始化地图上的东西，刷新地图时使用
	int length, width;											//地图的长宽
	int heroA_position_x;										//英雄A的x位置
	int heroA_position_y;										//英雄A的y位置
	int heroB_position_x;										//英雄B的x位置
	int heroB_position_y;										//英雄B的y位置
	int monster_position_x[5];									//怪兽的x位置
	int monster_position_y[5];									//怪兽的y位置

public:
	Map();
	~Map(){};
	bool loadMap(int mapname);									//载入地图，初始化map_data和map_data_0
	void addBomb(int x, int y);									//在地图上放置一个炸弹
	void setHeroPosition(int x, int y, int which);				//设置英雄的位置
	void setMonsterPosition(int x, int y, int which);			//设置怪兽的位置
	bool canReach(int x, int y);								//判断位置是否能够到达
};

#endif
