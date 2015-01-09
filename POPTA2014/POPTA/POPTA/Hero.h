#ifndef _HERO_H_
#define _HERO_H_

class Hero
{
private:
	double move_speed;							//�ƶ��ٶ�
	int position_x, position_y;					//Ӣ��λ��
	bool is_dead;								//Ӣ���Ƿ�����
	int dead_time;								//����ʱ��
	int bomb_limit;								//ը����������
	int bomb_number;							//Ŀǰ�ѷ���ը������
	int bomb_lethality;							//ը������
	int bomb_position_x, bomb_position_y;		//���ڷ���ը����λ��
	int put_bomb_time;							//���ڷ���ը����ʱ��
	bool has_rider;								//�Ƿ��������
	int tools_kind[10];							//ӵ�еĵ�������
	int tools_number;							//ӵ�еĵ�������
	int skill_using_time;						//����ʹ��ʱ��
	int skill_time;								//���ܳ���ʱ��
	int cold_time;								//������ȴʱ��
	bool is_skill_prepared;						//�����Ƿ����ʹ��

public:
	Hero();										//
	~Hero(){};									//
	void usingSkill();							//Ӣ��ʹ�ü���
	void checkTime();							//������ʱ���ϵ
	virtual void skillBegin(){};				//������Ч��Ӣ�����Ըı�
	virtual void skillEnd(){};					//���ܽ�����Ӣ�ۻظ�ԭ����
	void heroMove(int direction);				//Ӣ���ƶ�
	void getTools(int toolskind);				//�õ�����
	void heroDie();								//Ӣ������
	void heroRevive();							//Ӣ������
	bool putBomb();								//����ը��
	int getBombPositionX();						//��ȡ���ڷ���ը����xλ��
	int getBombPositionY();						//��ȡ���ڷ���ը����yλ��
	int getBombTime();							//��ȡ���ڷ���ը����ʱ��
	int getPositionX();							//��ȡ��ǰӢ��xλ��
	int getPositionY();							//��ȡ��ǰӢ��yλ��
	int getLethality();							//��ȡը������
	void setPositionX();						//����Ӣ��xλ��
	void setPositionY();						//����Ӣ��yλ��
};

#endif
