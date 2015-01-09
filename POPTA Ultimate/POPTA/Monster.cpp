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

double Monster::getX()//获取野怪x坐标
{
	return position_x;
}
double Monster::getY()//获取野怪y坐标
{
	return position_y;
}

void Monster::setPosition(double x,double y)//设定野怪位置
{
	position_x = x;
	position_y = y;
}


void Monster::Update(float fDeltaTime, DIRECTION direction)//更新显示野怪的函数
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

void Monster::checkTime()//检查时间关系
{
	if (1)
		monsterRevive();
}


void Monster::Move(float fDeltaTime)//野怪移动的函数
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
void Monster::monsterDie()//野怪死亡
{
	is_dead = true;
	dead_time = 0;
	toStartSite();
}

void Monster::monsterRevive()//野怪复活
{
	is_dead = false;
	setPosition(340,340);
}

double Monster::hero_position[2][2] = {{0,0},{0,0}};

void Monster::getHeroPosition(Hero* hero1, Hero* hero2)//设定英雄位置
{
	hero_position[0][0] = hero1->getX(); 
	hero_position[0][1] = hero1->getY();
	hero_position[1][0] = hero2->getX();
	hero_position[1][1] = hero2->getY();
}

int Monster::moveJudge()//判断区域内情景
{
	int hero = 0;//区域内英雄数
	int hero_no = 0;//英雄编号
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

DIRECTION Monster::directionJudge(int hero,int hero_no)//根据区域内有无英雄信息判断移动的方向
{
	DIRECTION direction;
	switch (hero)
	{
		//没有英雄在警戒范围内
	case 0:
		if (rand()%50 == 4) direction = DIRECTION(rand()%4);
		else direction = monster_direction;//有1/50的几率随机择向，否则维持原方向
		break;

		//有不少于一个英雄在警戒范围内
	default:
		hero = rand()%(hero+1);//随机选择跟随一个英雄或者不跟随
		if (hero == 0) {
			if (rand()%50 == 4) direction = DIRECTION(rand()%4);
			else direction = monster_direction;
		}else{
			if (rand()%50 == 4){//1/50的概率朝向英雄的方向
				if (hero_position[hero_no][0] > position_x && hero_position[hero_no][1] > position_y) direction = RIGHT;
				else if (hero_position[hero_no][0] <= position_x && hero_position[hero_no][1] > position_y) direction = DOWN;
				else if (hero_position[hero_no][0] <= position_x && hero_position[hero_no][1] <= position_y) direction = LEFT;
				else direction = UP;
			}else direction = monster_direction;//否则保持当前方向
		}
		break;
	}
	setDirection(direction);
	return direction;
}

void Monster::setDirection(DIRECTION direction)//设置怪物朝向
{
	if (monster_direction != direction)
	{
		dir_image[monster_direction]->Stop();
		monster_direction = direction;
		dir_image[monster_direction]->Play();
	}
}
DIRECTION Monster::getDirection()//得到怪物当前方向
{
	return monster_direction;
}

void Monster::setStartSite(double x, double y)//设置怪物出生点
{
	startPosition_x = x;
	startPosition_y = y;
}

void Monster::toStartSite()//设置怪物位置到出生点
{
	position_x = startPosition_x;
	position_y = startPosition_y;
}

bool Monster::isDead()//判断野怪是否死亡
{
	return is_dead;
}
bool Monster::isMonsterIn(DIRECTION direction,float fDeltaTime)//判断野怪移动后是否在野怪区内
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
void  Monster::wantReborn(double fDeltaTime)//判断野怪是否该重生
{
	dead_time += fDeltaTime;
	if(dead_time >= reborn_time)
		is_dead = false;
}
