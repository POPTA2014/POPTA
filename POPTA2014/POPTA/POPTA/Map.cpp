#include <fstream>
#include "Map.h"
#include "Game.h"

Map::Map()
{
	map_data = NULL;
	map_data_0 = NULL;
}

bool Map::loadMap(int mapname)
{
	fstream file;
	file.open("map0.txt");
	if(! file)
		return 0;

	ifstream fin("map0.txt");
	fin >> length >> width;
	map_data = new int[length * width];
	for (int i = 0; i < length; i++)
		for (int j = 0; j < width; j++)
		{
			int index = i * length + j;
			char ch;
			fin >> ch;
			switch (ch)
			{
			case 'F':
				map_data[index] = 0;

			default:
				break;
			}
		}
		fin.close();
		map_data_0 = new int[length * width];
		for (int i = 0; i < length * width; i++)
			map_data_0[i] = map_data[i];
		return 1;
}

void Map::setHeroPosition(int x, int y, int which)
{
	if (which == 0)
	{
		heroA_position_x = x;
		heroA_position_y = y;
	}
	if (which == 1)
	{
		heroB_position_x = x;
		heroB_position_y = y;
	}
}

void Map::setMonsterPosition(int x, int y, int which)
{
	monster_position_x[which] = x;
	monster_position_y[which] = y;
}

void Map::addBomb(int x, int y)
{
	//map_data[x * length + y] = bomb;
}