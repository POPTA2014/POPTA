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
	bool heroPass(double x, double y, DIRECTION d);				// ������Ĳ���������ͼ���ж������Ƿ��ܹ�ͨ��
	bool canBomb(int i, int j);									// ը���Ƿ��ܹ�ը���ÿ�
	bool canBombPass(int i, int j);;								// ը���Ƿ��ܹ������ÿ飬������ܣ����ڸÿ�ֹͣ
	void Render();
	void setMap(int i, int j, int state);;                       // �ı�mapĳ�����״̬
private:
	int map_data0[BOX_NUM][BOX_NUM],map_data[BOX_NUM][BOX_NUM];							// ��ͼÿ���Ÿ���Ӧ�Ĳ���
	hgeSprite *Mapimage[16];						// ��ͼ��ͼƬ�ز�
};

#endif