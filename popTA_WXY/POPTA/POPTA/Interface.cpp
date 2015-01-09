#include "Interface.h"


void Interface::createWindow()
{
	cout << "创建游戏窗口" << endl;
}

void Interface::showHomePage()
{
	cout << "显示游戏首页" << endl;
}

int Interface::getMapName()
{
	cout << "选择地图" << endl;
	int a;
	cin >> a;
	return a;
	return 0;
}

void Interface::refresh()
{
	cout << "界面刷新" << endl;
}
