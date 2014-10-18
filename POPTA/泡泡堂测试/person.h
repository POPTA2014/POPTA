#pragma once
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeanim.h>

//#define DOWN 0
//#define LEFT 1
//#define RIGHT 2
//#define Up   3
enum DIRECTION{NO=-1,DOWN, LEFT, RIGHT, UP};
//#define STAND 0
//#define WALK 1
enum PERSON_STATE{STAND, WALK};
const float SPEED = 100;

class person
{
public:
	person(void);
	person(HTEXTURE tex, int nframes, float FPS, float w, float h);
	~person(void);
    void Walk(int direction);
	void setDirection(DIRECTION direction);
	void Update(float fDeltaTime, DIRECTION direction = NO);
	void Render(float x = -1, float y = -1);
	void Stop();
	void Play(DIRECTION directionh);
	void Move(float speed, float fDeltaTime);
	void setX(int x);
	void setY(int y);
	void set_person_state(PERSON_STATE _person_state);
	int getX();
	int getY();
	PERSON_STATE get_person_state();
	DIRECTION getDirection(); 
	int Draw();
private:
	//HTEXTURE	*img;	//�����ͼ��,�����ĸ�����������Ƶ�ͼ
	DIRECTION		person_direction;	//����ķ���
	double pX;                 //����ĺ�������λ��
	double pY;					//�������������λ��
	PERSON_STATE     person_state;		//�������ﾲֹ�����ƶ�
	hgeAnimation* dir_image[4]; //�ֱ��ƿ��ĸ������ͼƬ
};


