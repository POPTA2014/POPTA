#ifndef _MAP_H_
#define _MAP_H_

class Map
{
private:
	int * map_data;												//Ŀǰ��ͼ�ϵĶ���
	int * map_data_0;											//��ʼ����ͼ�ϵĶ�����ˢ�µ�ͼʱʹ��
	int length, width;											//��ͼ�ĳ���
	int heroA_position_x;										//Ӣ��A��xλ��
	int heroA_position_y;										//Ӣ��A��yλ��
	int heroB_position_x;										//Ӣ��B��xλ��
	int heroB_position_y;										//Ӣ��B��yλ��
	int monster_position_x[5];									//���޵�xλ��
	int monster_position_y[5];									//���޵�yλ��

public:
	Map();
	~Map(){};
	bool loadMap(int mapname);									//�����ͼ����ʼ��map_data��map_data_0
	void addBomb(int x, int y);									//�ڵ�ͼ�Ϸ���һ��ը��
	void setHeroPosition(int x, int y, int which);				//����Ӣ�۵�λ��
	void setMonsterPosition(int x, int y, int which);			//���ù��޵�λ��
	bool canReach(int x, int y);								//�ж�λ���Ƿ��ܹ�����
};

#endif
