#include "Hero.h"
#include "Game.h"

Hero::Hero()
{
	is_dead = 0;
	bomb_limit = 1;
	bomb_number = 0;
	bomb_lethality = 1;
	has_rider = 0;
	tools_number = 0;
	is_skill_prepared = 1;
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
	bomb_limit = 1;
	bomb_number = 0;
	bomb_lethality = 1;
	has_rider = 0;
	tools_number = 0;
	is_skill_prepared = 1;
}

bool Hero::putBomb()
{
	if (bomb_number == bomb_limit)
		return false;
	bomb_position_x = position_x;
	bomb_position_y = position_y;
	//set put_bomb_time
	bomb_number++;
	return true;
}

int Hero::getPositionX()
{
	return position_x;
}

int Hero::getPositionY()
{
	return position_y;
}

int Hero::getBombPositionX()
{
	return bomb_position_x;
}

int Hero::getBombPositionY()
{
	return bomb_position_y;
}

int Hero::getBombTime()
{
	return put_bomb_time;
}

int Hero::getLethality()
{
	return bomb_lethality;
}
