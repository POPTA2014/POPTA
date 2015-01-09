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
				if (! war_map.loadMap(game_interface.getMapName()))		//����war_map�������ͼ����������Ϸ��ͼ���г�ʼ��
					cout << "�����ͼ����" << endl;
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
	cout << "����1��ʼս��" << endl;
	cin >> x;
	return x;
}

bool Game::warEnd()
{
	return 0;
}

bool Game::loadMap(int mapname)
{
	cout << "�����ͼ" << mapname << endl;
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
	cout << "����Ӣ��" << endl;
	heroA = new Hero();
	heroB = new Hero();
}

void Game::createMonsters()
{
	cout << "��������" << endl;
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
		checkBomb();				//���ը���ǹ���ը
		monsterAction(x);			//���޶���
		heroAction(x);				//Ӣ�۶���
		game_interface.refresh();	//ˢ�½���
		gamePause();				//�ж���Ϸ�Ƿ���ͣ
	}
}

void Game::checkBomb()
{
	if (bomb.checkBomb())
	{
	}
}