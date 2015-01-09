#ifndef _GAME_H_
#define _GAME_H_

#include <iostream>
#include "Hero.h"
#include "Map.h"
#include "Monster.h"
#include "Interface.h"
#include "Bomb.h"

using namespace std;

class Game
{
private:
	Map war_map;						//�����ͼ
	Hero * heroA;						//�������1��Ӣ��A������ѡ��Ӣ������
	Hero * heroB;						//�������2��Ӣ��B������ѡ��Ӣ������
	Monster * monster[5];				//����5ֻ���ޣ���������ɱ�
	Interface game_interface;			//����������������ʾ��������ȡ���̡������Ϣ
	Bomb bomb;						//��ը��

public:
	Game(){};				
	~Game(){};
	void gameStart();					//������Ϸ
	bool gameOver();					//������Ϸ
	bool warBegin();					//һ��ս����ʼ
	bool warEnd();						//һ��ս������
	bool loadMap(int mapname);			//�����ͼ
	void gamePause();					//��ͣ��Ϸ
	bool gameSave();					//�洢��Ϸ
	void dataClean();					//һ����Ϸ�������������
	void createHeroes();				//����Ӣ��
	void createMonsters();				//��������
	void checkBomb();					//���ը���Ƿ�ը
	void heroAction(int x);				//Ӣ�۶���
	void monsterAction(int x);			//���޶���
	void warProcess();					//ս������
};

#endif
