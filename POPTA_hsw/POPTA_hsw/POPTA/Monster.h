#pragma once

class Monster//Ұ����
{
public:
	Monster(void);//���캯��
	~Monster(void);
	double getPosition_x();
	double getPosition_y();//��ȡҰ��x,y����
	void setPosition(double x,double y);//�趨Ұ��λ��
	void display();//��ʾҰ�ֵĺ���
	void disappear();//Ұ����ʧ����
	void move();//Ұ���ƶ��ĺ���
	void die();//Ұ����������(����Ұ����ʧ����)

private:
	double position_x[10];//Ұ��λ��x,��ʼ��Ϊ10
	double position_y[10];//Ұ��λ��y,��ʼ��Ϊ10
};
