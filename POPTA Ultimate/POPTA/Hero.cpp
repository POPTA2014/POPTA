#include "Hero.h"

Hero::Hero()
{
}

Hero::~Hero()
{
	for(int i = 0; i < 4; i++)
	{
		delete dir_image[i];
	}
}

Hero::Hero(HTEXTURE tex, int nframes, float FPS, float w, float h){
	is_dead = 0;
	dead_time = 0;
	reborn_time = 5;                  // 重生时间为3s
	boom_limit = 1;
	boom_number = 0;
	boom_lethality = 1;
	is_walking = false;
	tools_number = 0;
	is_skill_prepared = 1;
	soccupation = new char[10];
	person_direction = DOWN;
	move_speed = 150;
	for(int i = 0; i < 4; i++)
		dir_image[i] = new hgeAnimation(tex, nframes, FPS, 0, i * h, 100, 100);
}



void Hero::checkTime()
{
	if (1) //skill time is over
		skillEnd();
	if (1) //cold time is over
		is_skill_prepared = 1;
	if (1) //dead time is over
		heroRevive();
}

void Hero::heroMove(int direction)
{
}

void Hero::getTools(ToolsKind toolskind)
{
	switch (toolskind)
	{
	case NONE:
		break;
	case POP_ADD://加泡泡数量
		boom_limit++;
		break;
	case SPEED_ADD://加速度
		if(move_speed < MAX_SPEED)
			move_speed +=50;
		break;
	case POWER_ADD://加泡泡威力
		if(boom_lethality < MAX_POWER)
			boom_lethality++;
		break;
	case POWER_MAX://威力最大
		boom_lethality = MAX_POWER;
		break;
	case SPEED_MAX://速度最大
			move_speed = MAX_SPEED;
		break;
	default:
		break;
	}
}

void Hero::heroDie()
{
	is_dead = 1;
	dead_time = 0;
	boom_limit = 1;
	boom_lethality = 1;
	move_speed = 150;
	toStartSite();
	skillBegin();
	//set dead_time
}

void Hero::heroRevive()
{
	is_dead = 0;
	boom_limit = 1;
	boom_number = 0;
	boom_lethality = 1;
	tools_number = 0;
	is_skill_prepared = 1;
}

void Hero::putBoom()
{
	/*int x = BOX_HEIGHT*(int(position_x)/BOX_HEIGHT);
	int y = BOX_WIDTH*(int(position_y)/BOX_WIDTH);*/

	boom_number++;
}

void Hero::boomExp()
{
	boom_number--;
}

bool Hero::canPutBoom()
{
	return (boom_limit > boom_number);
}

double Hero::getX()
{
	return position_x;
}

double Hero::getY()
{
	return position_y;
}

void Hero::setX(double x){
	position_x = x;
}

void Hero::setY(double y){
	position_y = y;
}

void Hero::setBoomLimit(int n){
	boom_limit = n;
}

int Hero::getBoomLimit(){
	return boom_limit;
}

int Hero::getLethality()
{
	return boom_lethality;
}

void Hero::setDirection(DIRECTION direction){
	if (person_direction != direction)
	{
		dir_image[person_direction]->Stop();
		person_direction = direction;
		dir_image[person_direction]->Play();
	}
}

void Hero::Update(float fDeltaTime, DIRECTION direction){
	if(direction == person_direction || direction == NO)
		dir_image[person_direction]->Update(fDeltaTime);
	else
		setDirection(direction);
	is_walking = true;
}

void Hero::Render(float x, float y){
	if(x == -1 || y == -1)
		dir_image[person_direction]->Render(position_x-50, position_y-80);
	else{
		position_x = x;
		position_y = y;
		dir_image[person_direction]->Render(position_x-50, position_y-80);
	}
}


//place the boom

void Hero::placeBoom(hgeAnimation	*placeBoom, float fDeltaTime){ 
	placeBoom->Play();
	placeBoom->Update(fDeltaTime);
}



void Hero::Stop(){
	dir_image[person_direction]->Stop();
	is_walking = false;
}

void Hero::Play(){
	dir_image[person_direction]->Play();
}

void Hero::Play(DIRECTION direction){
	person_direction = direction;
	dir_image[person_direction]->Play();
}

void Hero::Move(float fDeltaTime){
	switch(person_direction){
	case LEFT:
		position_x -= move_speed * fDeltaTime;
		break;
	case DOWN:
		position_y += move_speed * fDeltaTime;
		break;
	case RIGHT:
		position_x += move_speed * fDeltaTime;
		break;
	case UP:
		position_y -= move_speed * fDeltaTime;
		break;
	default:
		break;
	}
}


DIRECTION Hero::getDirection(){
	return person_direction;
}

void Hero::skillBegin()
{
	switch(occupation){
	case Saber:
		boom_limit = 2;
		soccupation = "Saber";
		break;
	case Assassin:
		move_speed = 250;
		soccupation = "Assassin";
		break;
	case Basaker:
		boom_lethality = 2;
		soccupation = "Basaker";
		break;
	default:
		boom_limit = 2;
		soccupation = "Saber";
		break;
	}
}

void Hero::skillEnd()
{

}

bool Hero::isWalking() const
{
	return is_walking;
}

void Hero::setStartSite(double x, double y)
{
	startPosition_x = x;
	startPosition_y = y;
}

void Hero::toStartSite()
{
	position_x = startPosition_x;
	position_y = startPosition_y;
}

void Hero::wantReborn(double t)
{
	dead_time += t;
	if(dead_time >= reborn_time)
		is_dead = false;
}

bool Hero::isDead()
{
	return is_dead;
}

double Hero::getReviveTime() const
{
	if(dead_time < 0)
		return 0;
	else
		return reborn_time - dead_time;
}

int Hero::getLeftBomb() const
{
	return boom_limit - boom_number; 
}

void Hero::setOccupation(OCCUPATION occ)
{
	occupation = occ;
	skillBegin();
}

char* Hero::getOccupation() const
{
	return soccupation;
}

double Hero::getSpeed()
{
	return move_speed;
}


