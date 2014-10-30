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
	///boom
	void placeBoom();
	PERSON_STATE get_person_state();
	DIRECTION getDirection(); 
	int Draw();
private:
	//HTEXTURE	*img;	//人物的图像,包括四个方向各种姿势的图
	DIRECTION		person_direction;	//人物的方向
	double pX;                 //人物的横向坐标位置
	double pY;					//人物的纵向坐标位置
	PERSON_STATE     person_state;		//代表人物静止还是移动
	hgeAnimation* dir_image[4]; //分别掌控四个方向的图片
};


