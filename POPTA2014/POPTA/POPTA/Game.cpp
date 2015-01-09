#include "Game.h"

void Game::gameStart()
{
	game_interface.createWindow();
	while (1)
	{
		game_interface.showHomePage();
		while (1)
		{
			if (warBegin())
			{
				if (! war_map.loadMap(game_interface.getMapName()))		//调用war_map的载入地图函数，对游戏地图进行初始化
					cout << "载入地图错误" << endl;
				createHeroes();
				createMonsters();
				warProcess();
				break;
			}
			if (gameOver())
				return ;
		}
		dataClean();
	}
}

bool Game::gameOver()
{
	return 0;
}

bool Game::warBegin()
{
	bool x;
	cout << "输入1开始战争" << endl;
	cin >> x;
	return x;
}

bool Game::warEnd()
{
	return 0;
}

bool Game::loadMap(int mapname)
{
	cout << "载入地图" << mapname << endl;
	return 1;
}

void Game::gamePause()
{
}

bool Game::gameSave()
{
	return 1;
}

void Game::dataClean()
{
}

void Game::createHeroes()
{
	cout << "创建英雄" << endl;
	heroA = new Hero();
	heroB = new Hero();
}

void Game::createMonsters()
{
	cout << "创建怪兽" << endl;
}

void Game::heroAction(int x)
{
	if (heroA->putBomb())
	{
		int x, y, l, t;
		x = heroA->getBombPositionX();
		y = heroA->getBombPositionY();
		t = heroA->getBombTime();
		l = heroA->getLethality();
		bomb.addBomb(x,y,1,l,t);
	}
	if (heroB->putBomb())
	{
		int x, y, l, t;
		x = heroB->getBombPositionX();
		y = heroB->getBombPositionY();
		t = heroB->getBombTime();
		l = heroB->getLethality();
		bomb.addBomb(x,y,2,l,t);
	}

}

void Game::monsterAction(int x)
{
}

void Game::warProcess()
{
	int x;
	while (! warEnd())
	{
		cin >> x;
		checkBomb();				//检查炸弹是够爆炸
		monsterAction(x);			//怪兽动作
		heroAction(x);				//英雄动作
		game_interface.refresh();	//刷新界面
		gamePause();				//判断游戏是否暂停
	}
}

void Game::checkBomb()
{
	if (bomb.checkBomb())
	{
	}
}