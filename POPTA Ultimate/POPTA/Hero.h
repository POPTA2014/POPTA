#ifndef _HERO_H_
#define _HERO_H_
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeanim.h>
#include "Boom.h"
#include "Tools.h"
#include <string>
using namespace std;


//#define DOWN 0
//#define LEFT 1
//#define RIGHT 2
//#define Up   3
enum DIRECTION{NO=-1,DOWN, LEFT, RIGHT, UP};
//#define STAND 0
//#define WALK 1
enum PERSON_STATE{STAND, WALK};
enum OCCUPATION{Saber, Assassin, Basaker};

class Hero
{
private:
	double move_speed;							//�ƶ��ٶ�
	double position_x, position_y;					//Ӣ��λ��
	double startPosition_x, startPosition_y;    // Ӣ�۳�ʼλ�ã����ڳ�ʼ���Լ�Ӣ������Ķ�λ
	bool is_walking;                            //Ӣ����������
	bool is_dead;								//Ӣ���Ƿ�����
	double dead_time;								//�����ۼ�ʱ��
	double reborn_time;                          // ������ʱ��
	int boom_limit;								//ը����������
	int boom_number;							//Ŀǰ�ѷ���ը������
	int boom_lethality;							//ը������
	int tools_kind[10];							//ӵ�еĵ�������
	int tools_number;							//ӵ�еĵ�������
	bool is_skill_prepared;						//�����Ƿ����ʹ��
	char* soccupation;
	OCCUPATION occupation;                      //Ӣ�۵�ְҵ
	PERSON_STATE     person_state;		//�������ﾲֹ�����ƶ�
	hgeAnimation* dir_image[4]; //�ֱ��ƿ��ĸ������ͼƬ
	DIRECTION		person_direction;	//����ķ���
public:
	Hero();										//
	Hero(HTEXTURE tex, int nframes, float FPS, float w, float h);
	~Hero();									//
	void checkTime();							//������ʱ���ϵ
	void skillBegin();				//������Ч��Ӣ�����Ըı�
	virtual void skillEnd();;					//���ܽ�����Ӣ�ۻظ�ԭ����
	void heroMove(int direction);				//Ӣ���ƶ�
	void getTools(ToolsKind toolskind);				//�õ�����
	void heroDie();								//Ӣ������
	void heroRevive();							//Ӣ������
	bool isDead();                             //Ӣ���Ƿ��Ѿ�����
	void putBoom();								//����ը��
	bool canPutBoom();
	void setBoomLimit(int n);
	int getBoomLimit();
	void wantReborn(double fDeltaTime);                     // �ж�Ӣ���Ƿ������
	double getX();							//��ȡ��ǰӢ��xλ��
	double getY();							//��ȡ��ǰӢ��yλ��
	int getLethality();							//��ȡը������
	double getSpeed();
	void setX(double x);						//����Ӣ��xλ��
	void setY(double y);						//����Ӣ��yλ��
	void boomExp();
	void setDirection(DIRECTION direction);
	void Update(float fDeltaTime, DIRECTION direction = NO);
	void Render(float x = -1, float y = -1);
	void setOccupation(OCCUPATION occ);
	void Stop();
	void Play();
	void Play(DIRECTION directionh);
	void Move(float fDeltaTime);
	void set_person_state(PERSON_STATE _person_state);
	void placeBoom(hgeAnimation	*placeBoom, float fDeltaTime);
	bool isWalking() const;;
	void setStartSite(double x, double y);
	void toStartSite();                              // ��Ӣ�ۻص���ʼλ��
	double getReviveTime()const;                       // ��ø���ʱ��
	int    getLeftBomb() const;                       // ���ʣ���ը����
	char* getOccupation() const;

	PERSON_STATE get_person_state();
	DIRECTION getDirection(); 
	int Draw();
};

#endif

