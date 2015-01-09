#ifndef _MAP_H_
#define _MAP_H_
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include "Hero.h"
#include <cmath>
#include <fstream>
using namespace std;

const int MAP_SIZE[2] = {1000, 680};
const int BOX_NUM = 17;
const int BOX_HEIGHT = 40;
const int BOX_WIDTH = 40;






class Map
{
public:
	Map(void);
	Map(HTEXTURE Maptexture );
	~Map(void);
	bool loadMap(int mapname);
	bool heroPass(double x, double y, DIRECTION d, int playerid = 0);				// 将人物的参数传给地图，判断任务是否能够通过
	bool isClamp(double x, double y, int playerid);                          // 判断英雄是否遇到夹子，如果遇到英雄将停留2s
	bool canBomb(int i, int j);									// 炸弹是否能够炸掉该块
	bool canBombPass(int i, int j);								// 炸弹是否能够穿过该块，如果不能，则在该块停止
	int bombHome(int i, int j);                                 // 判断被炸的是否为家，如果为Player1的家，返回1；如果为player2的家，返回2;否则返回0
	void Render();
	void setMap(int i, int j, int state);;                       // 改变map某个点的状态
private:
	int map_data0[BOX_NUM][BOX_NUM],map_data[BOX_NUM][BOX_NUM];							// 地图每个放个对应的参数
	hgeSprite *Mapimage[16];						// 地图的图片素材
};

#endif