#ifndef _BOMB_H_
#define _BOMB_H_

class Bomb
{
private:
	int position_x[20];													//ը��xλ��
	int position_y[20];													//ը��yλ��
	int belong[20];														//ը����˭���õ�
	int lethality[20];													//ը������
	int time[20];														//ը���ķ���ʱ��
	int queue_head;														//ը�����еĶ�ͷλ��
	int number;															//ը��������
	int blast_position_x;												//��ը��ը��xλ��
	int blast_position_y;												//��ը��ը��yλ��
	int blast_lethality;												//��ը��ը��������
	int blast_belong;													//��ը��ը����˭���õ�

public:
	Bomb();
	~Bomb(){};
	void addBomb(int x, int y, int belong, int lethality, int time);	//��ը�����������һ��ը��
	bool checkBomb();													//���ը���Ƿ�ը
	int getBlastPositionX();											//��ñ�ը��ը��xλ��
	int getBlastPositionY();											//��ñ�ը��ը��yλ��
	int getBlastLethality();											//��ñ�ը��ը��������
	int getBlastBelong();												//��ñ�ը��ը����˭���õ�
};

#endif
