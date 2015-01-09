#include "Map.h"


Map::Map(void)
{
}

Map::Map(HTEXTURE Maptexture ){
	for(int i = 0; i < 16; i++)
		Mapimage[i] = new hgeSprite(Maptexture, 40*i, 0, 40, 40);
}

bool Map::loadMap(int mapname)
{
	fstream file;
	file.open("map0.txt");
	if(! file)
		return 0;

	ifstream fin("map0.txt");

	for (int i = 0; i < BOX_NUM; i++)
		for (int j = 0; j < BOX_NUM; j++)
		{
			char ch;
			fin >> ch;
			switch (ch)
			{
			case 'F':
				map_data[i][j] = 1;
				break;
			case '=':
				map_data[i][j] = 2;
				break;
			case '*':
				map_data[i][j] = 14;
				break;
			case '#':
				map_data[i][j] = 7;
				break;
			case '$':
				map_data[i][j] = 9; 
				break;
			case 'H':
				map_data[i][j] = 1;
				break;
			case '@':
				map_data[i][j] = 6;
				break;
			case 'M':
				map_data[i][j] = 5;
				break;
			case 'A':
				map_data[i][j] = 3;
				break;
			case 'B':
				map_data[i][j] = 4;
				break;
			default:
				break;
			}
		}
		fin.close();
		for (int i = 0; i < BOX_NUM; i++)
			for (int j = 0; j < BOX_NUM; j++)
			{
				map_data0[i][j] = map_data[i][j];
			}
			return 1;
}


Map::~Map(void)
{
}

void Map::Render(){
	for(int i = 0; i < BOX_NUM; i++)
		for(int j = 0; j < BOX_NUM; j++)
			Mapimage[map_data[i][j]]->Render(i*BOX_WIDTH, j *BOX_HEIGHT);

}



bool Map::heroPass(double x, double y, DIRECTION d)
{
	double px = x;
	double py = y;
	double delta;
	int i, j;
	switch(d){
	case LEFT:
		i = int(px - 20) / BOX_WIDTH;
		j = int(py) / BOX_WIDTH;
		delta = py - j * BOX_WIDTH;	
		if(x<=20 || map_data[i][j] > 6 || (delta > 22.2 && map_data[i][j+1] > 6))
			return false;
		else
			return true;
	case RIGHT:
		i = int(px + 20) / BOX_WIDTH;
		j = int(py) / BOX_WIDTH;
		delta = py - j * BOX_WIDTH;	
		if(i>= BOX_NUM || map_data[i][j] > 6 || (delta > 22.2 && map_data[i][j+1] > 6))
			return false;
		else
			return true;
	case UP:
		i = int(px) / BOX_WIDTH;
		j = int(py-20) / BOX_WIDTH;
		delta = px - i * BOX_WIDTH;	
		if(y<=20 || map_data[i][j] > 6 ||(delta > 22.2 && map_data[i+1][j] > 6))
			return false;
		else 
			return true;
	case DOWN:
		i = int(px) / BOX_WIDTH;
		j = int(py+20) / BOX_WIDTH;
		delta = px - i * BOX_WIDTH;	
		if(j>= BOX_NUM || map_data[i][j] > 6 || (delta > 22.2 && map_data[i+1][j] > 6))
			return false;
		else
			return true;
	case NO:
		return true;
	}
}

bool Map::canBomb(int i, int j)
{
	switch(map_data[i][j]){
	case 14:
	case 15:
		return true;
	default:
		return false;
	}
}

bool Map::canBombPass(int i, int j)
{
	if((map_data[i][j] < 7)||(map_data[i][j] >= 14))	
		return true;
	else
		return false;
}

void Map::setMap(int i, int j, int state)
{
	map_data[i][j] = state;
}

