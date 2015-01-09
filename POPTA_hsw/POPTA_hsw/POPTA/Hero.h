#ifndef _HERO_H_
#define _HERO_H_
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeanim.h>
#include "Boom.h"


//#define DOWN 0
//#define LEFT 1
//#define RIGHT 2
//#define Up   3
enum DIRECTION{NO=-1,DOWN, LEFT, RIGHT, UP};
//#define STAND 0
//#define WALK 1
enum PERSON_STATE{STAND, WALK};

class Hero
{
private:
	double move_speed;							//�ƶ��ٶ�
	double position_x, position_y;					//Ӣ��λ��
	bool is_walking;                            //Ӣ����������
	bool is_dead;								//Ӣ���Ƿ�����
	int dead_time;								//����ʱ��
	int boom_limit;								//ը����������
	int boom_number;							//Ŀǰ�ѷ���ը������
	int boom_lethality;							//ը������
	int boom_position_x, boom_position_y;		//���ڷ���ը����λ��
	int put_boom_time;							//���ڷ���ը����ʱ��
	bool has_rider;								//�Ƿ��������
	int tools_kind[10];							//ӵ�еĵ�������
	int tools_number;							//ӵ�еĵ�������
	int skill_using_time;						//����ʹ��ʱ��
	int skill_time;								//���ܳ���ʱ��
	int cold_time;								//������ȴʱ��
	bool is_skill_prepared;						//�����Ƿ����ʹ��
	PERSON_STATE     person_state;		//�������ﾲֹ�����ƶ�
	hgeAnimation* dir_image[4]; //�ֱ��ƿ��ĸ������ͼƬ
	DIRECTION		person_direction;	//����ķ���
public:
	Hero();										//
	Hero(HTEXTURE tex, int nframes, float FPS, float w, float h);
	~Hero();									//
	void usingSkill();							//Ӣ��ʹ�ü���
	void checkTime();							//������ʱ���ϵ
	virtual void skillBegin();;				//������Ч��Ӣ�����Ըı�
	virtual void skillEnd();;					//���ܽ�����Ӣ�ۻظ�ԭ����
	void heroMove(int direction);				//Ӣ���ƶ�
	void getTools(int toolskind);				//�õ�����
	void heroDie();								//Ӣ������
	void heroRevive();							//Ӣ������
	void putBoom();								//����ը��
	bool canPutBoom();
	void setBoomLimit(int n);
	int getBoomLimit();
	double getPositionX();							//��ȡ��ǰӢ��xλ��
	double getPositionY();							//��ȡ��ǰӢ��yλ��
	int getLethality();							//��ȡը������
	void setPositionX(double x);						//����Ӣ��xλ��
	void setPositionY(double y);						//����Ӣ��yλ��
	void boomExp();
	void setDirection(DIRECTION direction);
	void Update(float fDeltaTime, DIRECTION direction = NO);
	void Render(float x = -1, float y = -1);
	void Stop();
	void Play();
	void Play(DIRECTION directionh);
	void Move(float fDeltaTime);
	void set_person_state(PERSON_STATE _person_state);
	void placeBoom(hgeAnimation	*placeBoom, float fDeltaTime);
	bool isWalking() const;;
	PERSON_STATE get_person_state();
	DIRECTION getDirection(); 
	int Draw();
};

#endif

