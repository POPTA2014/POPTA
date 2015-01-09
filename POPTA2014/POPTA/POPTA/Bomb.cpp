#include "Bomb.h"

Bomb::Bomb()
{
	queue_head = 0;
	number = 0;
}

void Bomb::addBomb(int x, int y, int belong, int lethality, int time)
{
	int tail;
	this->number++;
	tail = (this->queue_head + this->number) % 20;
	this->position_x[tail] = x;
	this->position_y[tail] = y;
	this->belong[tail] = belong;
	this->lethality[tail] = lethality;
	this->time[tail] = time;
}

bool Bomb::checkBomb()
{
	if (1) //check queue first bomb
	{
		blast_position_x = position_x[queue_head];
		blast_position_y = position_y[queue_head];
		blast_lethality = lethality[queue_head];
		blast_belong = belong[queue_head];
		queue_head ++;
		number --;
		return 1;
	}
	return 0;
}

int Bomb::getBlastPositionX()
{
	return blast_position_x;
}

int Bomb::getBlastPositionY()
{
	return blast_position_y;
}

int Bomb::getBlastLethality()
{
	return blast_lethality;
}

int Bomb::getBlastBelong()
{
	return blast_belong;
}