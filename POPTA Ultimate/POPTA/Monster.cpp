#include "Monster.h"
#include "Map.h"


Monster::Monster(void)
{
}
Monster::Monster(HTEXTURE tex,int nframes,float FPS,float w,float h)
{
	monster_direction = DOWN;
	//monster_state = WALK;
	move_speed = SPEED;
	is_dead = false;
	reborn_time = 20;
	dead_time = 0;
	setPosition(100,100);
	for(int i = 0; i < 4; i++)
		dir_image[i] = new hgeAnimation(tex,nframes,FPS,0,i*h,100,100);
}
Monster::~Monster(void)
{
	for(int i = 0; i < 4; i++)
		if(!dir_image[i])
			delete dir_image[i];
}

double Monster::getX()//��ȡҰ��x����
{
	return position_x;
}
double Monster::getY()//��ȡҰ��y����
{
	return position_y;
}

void Monster::setPosition(double x,double y)//�趨Ұ��λ��
{
	position_x = x;
	position_y = y;
}


void Monster::Update(float fDeltaTime, DIRECTION direction)//������ʾҰ�ֵĺ���
{
	if(direction == monster_direction || direction == NO)
		dir_image[monster_direction]->Update(fDeltaTime);
	else
		setDirection(direction);
}

void Monster::Render(float x,float y)
{
	if (x == -1 || y == -1)
	{
		dir_image[monster_direction]->Render(position_x-50, position_y-80);
	}
	else{
		position_x = x;
		position_y = y;
		dir_image[monster_direction]->Render(position_x-50, position_y-80);
	}
}

void Monster::checkTime()//���ʱ���ϵ
{
	if (1)
		monsterRevive();
}


void Monster::Move(float fDeltaTime)//Ұ���ƶ��ĺ���
{
	switch(monster_direction)
	{
	case LEFT:
		position_x -= SPEED * fDeltaTime;
		break;
	case DOWN:
		position_y += SPEED * fDeltaTime;
		break;
	case RIGHT:
		position_x += SPEED * fDeltaTime;
		break;
	case UP:
		position_y -= SPEED * fDeltaTime;
		break;
	default:
		break;
	}

}

void Monster::Play()
{
	dir_image[monster_direction]->Play();
}
void Monster::Play(DIRECTION direction)
{
	monster_direction = direction;
	dir_image[monster_direction]->Play();
}
void Monster::Stop()
{
	dir_image[monster_direction]->Stop();
}
void Monster::monsterDie()//Ұ������
{
	is_dead = true;
	dead_time = 0;
	toStartSite();
}

void Monster::monsterRevive()//Ұ�ָ���
{
	is_dead = false;
	setPosition(340,340);
}

double Monster::hero_position[2][2] = {{0,0},{0,0}};

void Monster::getHeroPosition(Hero* hero1, Hero* hero2)//�趨Ӣ��λ��
{
	hero_position[0][0] = hero1->getX(); 
	hero_position[0][1] = hero1->getY();
	hero_position[1][0] = hero2->getX();
	hero_position[1][1] = hero2->getY();
}

int Monster::moveJudge()//�ж��������龰
{
	int hero = 0;//������Ӣ����
	int hero_no = 0;//Ӣ�۱��
	for (int i=0;i<2;i++)
	{
		if (hero_position[i][0]>=5*BOX_WIDTH && hero_position[i][0]<=12*BOX_WIDTH&&
			hero_position[i][1]>=5*BOX_WIDTH && hero_position[i][1]<=12*BOX_WIDTH)
		{
			hero++;
			if (hero==2) hero_no = rand()%i;
			else hero_no = i;
		}
	}
	directionJudge(hero,hero_no);
	return hero;
}

DIRECTION Monster::directionJudge(int hero,int hero_no)//��������������Ӣ����Ϣ�ж��ƶ��ķ���
{
	DIRECTION direction;
	switch (hero)
	{
		//û��Ӣ���ھ��䷶Χ��
	case 0:
		if (rand()%50 == 4) direction = DIRECTION(rand()%4);
		else direction = monster_direction;//��1/50�ļ���������򣬷���ά��ԭ����
		break;

		//�в�����һ��Ӣ���ھ��䷶Χ��
	default:
		hero = rand()%(hero+1);//���ѡ�����һ��Ӣ�ۻ��߲�����
		if (hero == 0) {
			if (rand()%50 == 4) direction = DIRECTION(rand()%4);
			else direction = monster_direction;
		}else{
			if (rand()%50 == 4){//1/50�ĸ��ʳ���Ӣ�۵ķ���
				if (hero_position[hero_no][0] > position_x && hero_position[hero_no][1] > position_y) direction = RIGHT;
				else if (hero_position[hero_no][0] <= position_x && hero_position[hero_no][1] > position_y) direction = DOWN;
				else if (hero_position[hero_no][0] <= position_x && hero_position[hero_no][1] <= position_y) direction = LEFT;
				else direction = UP;
			}else direction = monster_direction;//���򱣳ֵ�ǰ����
		}
		break;
	}
	setDirection(direction);
	return direction;
}

void Monster::setDirection(DIRECTION direction)//���ù��ﳯ��
{
	if (monster_direction != direction)
	{
		dir_image[monster_direction]->Stop();
		monster_direction = direction;
		dir_image[monster_direction]->Play();
	}
}
DIRECTION Monster::getDirection()//�õ����ﵱǰ����
{
	return monster_direction;
}

void Monster::setStartSite(double x, double y)//���ù��������
{
	startPosition_x = x;
	startPosition_y = y;
}

void Monster::toStartSite()//���ù���λ�õ�������
{
	position_x = startPosition_x;
	position_y = startPosition_y;
}

bool Monster::isDead()//�ж�Ұ���Ƿ�����
{
	return is_dead;
}
bool Monster::isMonsterIn(DIRECTION direction,float fDeltaTime)//�ж�Ұ���ƶ����Ƿ���Ұ������
{
	int i,j;
	switch(direction){
	case LEFT:
		i = int(position_x - SPEED*fDeltaTime) / BOX_WIDTH;
		j = int(position_y) / BOX_WIDTH;
		if( i<5 ||j<5||i>12||j>12)
			return false;
		else
			return true;
		break;
	case RIGHT:
		i = int(position_x + SPEED*fDeltaTime) / BOX_WIDTH+1;
		j = int(position_y) / BOX_WIDTH;
		if( i<5 ||j<5||i>12||j>12)
			return false;
		else
			return true;
		break;
	case UP:
		i = int(position_x) / BOX_WIDTH;
		j = int(position_y - SPEED*fDeltaTime) / BOX_WIDTH;
		if( i<5 ||j<5||i>12||j>12)
			return false;
		else
			return true;
		break;
	case DOWN:
		i = int(position_x) / BOX_WIDTH;
		j = int(position_y + SPEED*fDeltaTime) / BOX_WIDTH+1;
		if( i<5 ||j<5||i>12||j>12)
			return false;
		else
			return true;
		break;
	default:
		return true;
		break;
	}
}
void  Monster::wantReborn(double fDeltaTime)//�ж�Ұ���Ƿ������
{
	dead_time += fDeltaTime;
	if(dead_time >= reborn_time)
		is_dead = false;
}
