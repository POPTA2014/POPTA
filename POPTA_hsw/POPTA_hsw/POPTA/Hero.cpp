#include "Hero.h"

Hero::Hero()
{
}

Hero::Hero(HTEXTURE tex, int nframes, float FPS, float w, float h){
	is_dead = 0;
	boom_limit = 1;
	boom_number = 0;
	boom_lethality = 4;
	is_walking = false;
	has_rider = 0;
	tools_number = 0;
	is_skill_prepared = 1;
	person_direction = DOWN;
	move_speed = 100;
	for(int i = 0; i < 4; i++)
		dir_image[i] = new hgeAnimation(tex, nframes, FPS, 0, i * h, 100, 100);
}

void Hero::usingSkill()
{
	is_skill_prepared = 0;
	skillBegin();
	//set skill_using_time
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

void Hero::getTools(int toolskind)
{
}

void Hero::heroDie()
{
	is_dead = 1;
	//set dead_time
}

void Hero::heroRevive()
{
	is_dead = 0;
	boom_limit = 1;
	boom_number = 0;
	boom_lethality = 1;
	has_rider = 0;
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

double Hero::getPositionX()
{
	return position_x;
}

double Hero::getPositionY()
{
	return position_y;
}

void Hero::setPositionX(double x){
	position_x = x;
}

void Hero::setPositionY(double y){
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

}

void Hero::skillEnd()
{

}

bool Hero::isWalking() const
{
	return is_walking;
}
