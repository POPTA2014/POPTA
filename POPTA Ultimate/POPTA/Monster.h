#pragma once
#include <hge.h>
#include "Map.h"
#include "Hero.h"

const float SPEED = 80;

class Monster//Ұ����
{
public:
	Monster(void);
	Monster(HTEXTURE tex, int neframes, float FPS, float w, float h);
	~Monster(void);
	double getX();
	double getY();//��ȡҰ��x,y����
	void setPosition(double x,double y);//�趨Ұ��λ��
	void Update(float fDeltaTime, DIRECTION direction);
	void Render(float x = -1, float y = -1);
	void checkTime();//���ʱ���ϵ
	void monsterDie();//Ұ����������
	void monsterRevive();//Ұ�ָ����
	void Move(float fDeltaTime);//Ұ���ƶ��ĺ���
	void Play();
	void Play(DIRECTION monster_direction);
	void Stop();
	void getHeroPosition(Hero* hero1, Hero* hero2);//�õ�Ӣ��λ����Ϣ
	int moveJudge();//�ж��������龰
	DIRECTION directionJudge(int hero,int hero_no);//��������������Ӣ���ж�Ұ���ƶ��ķ���
	DIRECTION getDirection();//�õ����ﵱǰ����
	void setDirection(DIRECTION direction);//���ù��﷽��
	void setStartSite(double x, double y);//���ù��������
	void toStartSite();//���ù���λ�õ�������
	bool isDead();//�ж�Ұ���Ƿ�����
	bool isMonsterIn(DIRECTION direction,float fDeltaTime);//�ж�Ұ���ƶ����Ƿ���Ұ������
	void wantReborn(double fDeltaTime);//�ж�Ұ���Ƿ������

private:
	double position_x;
	double position_y;//Ұ��λ��x,y
	double startPosition_x;
	double startPosition_y;//Ұ�ֳ���λ��x,y
	double move_speed;//Ұ���ٶ�
	bool is_dead;
	double dead_time;
	double reborn_time;
	static double hero_position[2][2];//Ӣ��λ����Ϣ
	DIRECTION monster_direction;//���﷽��
	hgeAnimation* dir_image[4];//�ֱ��ƿ��ĸ������ͼƬ
};


