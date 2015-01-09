#include "Game.h"

Game* Game::pThis;

Game::Game()
{
	pThis = this;
	monsternum = 5;
	toolsnum = 0;
	p1Bkey = false;
	p2Bkey = false;
	inGame = false;
	isGameOver = false;
}

Game::~Game()
{
	// Delete created objects and free loaded resources
	menuOver();

}


void Game::start()
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC,RenderFunc);
	hge->System_SetState(HGE_TITLE, "POPTA");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, MAP_SIZE[0]);
	hge->System_SetState(HGE_SCREENHEIGHT, MAP_SIZE[1]);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_USESOUND, true);
	srand((unsigned)time(NULL));

	if(hge->System_Initiate()){
		snd1 = hge->Effect_Load("picture/bg1.mp3");
		snd2= hge->Effect_Load("picture/bg2.mp3");
		snd3= hge->Effect_Load("picture/bg3.mp3");
		boomMusic = hge->Effect_Load("picture/boom.mp3");
		placeMusic = hge->Effect_Load("picture/place.mp3");
		snd = hge->Effect_Load("picture/menu.wav");
		menuStart();
		hge->System_Start();
		menuOver();
		gameOver();
	}
	hge->System_Shutdown();
	hge->Release();
}

void Game::menuStart()
{
	cur = hge->Texture_Load("picture/cursor.png");
	
	back = hge->Texture_Load("picture/background.jpg");
	back_1 = hge->Texture_Load("picture/hero.png");
	back_2 = hge->Texture_Load("picture/map.png");
	back_3 = hge->Texture_Load("picture/start_0.png");
	back_4 = hge->Texture_Load("picture/error.png");
	button = hge->Texture_Load("picture/button.jpg");
	// Load the font, create the cursor sprite
	fnt=new hgeFont("picture/font1.fnt");
	spr=new hgeSprite(cur,0,0,32,32);

	//-back spr
	backSpr = new hgeSprite(back, 0, 0, MAP_SIZE[0], MAP_SIZE[1]);

	back1Spr = new hgeSprite(back_1, 0, 0, MAP_SIZE[0], MAP_SIZE[1]);
	back2Spr = new hgeSprite(back_2, 0, 0, MAP_SIZE[0], MAP_SIZE[1]);
	back3Spr = new hgeSprite(back_3, 0, 0, MAP_SIZE[0], MAP_SIZE[1]);
	back4Spr = new hgeSprite(back_4, 0, 0, MAP_SIZE[0], MAP_SIZE[1]);

	showSpr = backSpr;

	menu_info.hero1_info = 0;
	menu_info.hero2_info = 0;
	menu_info.map_info = 0;

	// Create and initialize the GUI
	gui=new hgeGUI();

	GUI_edit::edit_init(gui, fnt, snd,button);
	GUI_edit::edit_show(gui, GUI_ID_FIRST_H);

	//gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
	gui->SetCursor(spr);
	gui->SetFocus(1);
	gui->Enter();
}

void Game::menuOver()                                    // 释放各种对象
{
	hge->Effect_Free(snd);
	hge->Texture_Free(back);
	hge->Texture_Free(back_1);
	hge->Texture_Free(back_2);
	hge->Texture_Free(back_3);
	hge->Texture_Free(cur); 	
	delete gui;
	delete fnt;
	delete spr;
}

void Game::gameStart()
{
	gameInfo = hge->Texture_Load("picture/interface_1.jpg");
	gameGUI = new hgeGUI();
	gameInfoSprite = new hgeSprite(gameInfo, 0, 0, 1000, 680);
	//gameGUI->SetNavMode(HGEGUI_NONAVKEYS);
	gameGUI->SetCursor(spr);
	//gameGUI->SetFocus(11);
	gameMenu(gameGUI);
	loadMap();
	createHeroes();
	createMonsters();
	initBoomList();
	initToolsList();
	player1home = 2;
	player2home = 2;
	player1ClampColdTime = 0;
	player2ClampColdTime = 0;
	isGameOver = false;
	pause = false;
	gameTime = 0;
}

void Game::gameOver()
{
	delete player1;
	delete player2;
	for(int i = 0; i < monsternum; i++){
		delete monster[i];
	}
	for(int i = 0; i < 100; i++){
		delete boom[i];
	}
	for(int i = 0; i < 100; i++){
		delete tools[i];
	}
	hge->Texture_Free(player1Pic);
	hge->Texture_Free(player2Pic);
	hge->Texture_Free(monster1Pic);
	hge->Texture_Free(monster2Pic);
	hge->Texture_Free(textool1);
	hge->Texture_Free(textool2);
	hge->Texture_Free(textool3);
	hge->Texture_Free(textool4);
	hge->Texture_Free(textool5);
	hge->Texture_Free(texPopo);
	hge->Texture_Free(texPopoDir);
	hge->Texture_Free(texPopoCen);
	hge->Texture_Free(mapPic);
	delete Game_Map;
}

void Game::loadMap()
{
	if(menu_info.map_info == 1)
		mapPic = hge->Texture_Load("picture/maptype1.png");
	else if(menu_info.map_info == 3)
		mapPic = hge->Texture_Load("picture/maptype3.png");
	else
		mapPic = hge->Texture_Load("picture/maptype2.png");
	Game_Map = new Map(mapPic);
	Game_Map->loadMap(0);
}

void Game::createHeroes()
{
	fnt = new hgeFont("picture/font1.fnt");
	player1Pic = hge->Texture_Load("picture/player1.png");
	player2Pic = hge->Texture_Load("picture/player2.png");
	player1 = new Hero(player1Pic, 4, 8, 100, 100);
	player1->setStartSite(20,20);
	player1->toStartSite();
	player1->Play(DOWN);
	player1->setOccupation(menu_info.hero1_occ);
	player2 = new Hero(player2Pic, 4, 8, 100, 100);
	player2->setStartSite(660, 660);
	player2->toStartSite();
	player2->Play(DOWN);
	player2->setOccupation(menu_info.hero2_occ);
}

void Game::createMonsters()
{
	fnt = new hgeFont("picture/font1.fnt");
	monster1Pic = hge->Texture_Load("picture/monster1.png");
	monster2Pic = hge->Texture_Load("picture/monster2.png");
	monster[0] = new Monster(monster1Pic, 4, 8, 100, 100);
	monster[1] = new Monster(monster2Pic, 4, 8, 100, 100);
	monster[2] = new Monster(monster1Pic, 4, 8, 100, 100);
	monster[3] = new Monster(monster2Pic, 4, 8, 100, 100);
	monster[4] = new Monster(monster1Pic, 4, 8, 100, 100);
	monster[0]->setStartSite(340,340);monster[0]->Play(DOWN);
	monster[1]->setStartSite(220,460);monster[1]->Play(UP);
	monster[2]->setStartSite(460,220);monster[2]->Play(LEFT);
	monster[3]->setStartSite(220,220);monster[3]->Play(RIGHT);
	monster[4]->setStartSite(460,460);monster[4]->Play(DOWN);
	for(int i = 0; i < monsternum; i++)
		monster[i]->toStartSite();
}

void Game::addBoom(int x, int y, int L, int w)	//L[5] = {int up,int down,int left,int right , int L};
{
	int index = BoomListTail;
    BoomListTail = (BoomListTail + 1) % 100;

	isPlace[index] = 1;
	hge->Effect_Play(placeMusic);
	boom[index]->setBoom(x,y,L,w);//爆炸长度与方向
	boom[index]->setDelay(1200);
	boom[index]->setBoomT(0);	//获取安放popo时间
	boom[index]->placeBoom();	//放置泡泡动作
}
void Game::addTool(ToolsKind toolskind, int x, int y)
{
	int index;
	for(index = 0; index < 100; index++)
		if(!toolsPlaced[index])
			break;
	toolsnum++;
	toolsPlaced[index] = true;
	tools[index]->setTool(toolskind,x,y);//道具类型和位置
	switch (toolskind)
	{
	case NONE:
		break;
	case POP_ADD:
		tools[index]->setTex(textool1);
		break;
	case SPEED_ADD:
		tools[index]->setTex(textool2);
		break;
	case POWER_ADD:
		tools[index]->setTex(textool3);
		break;
	case POWER_MAX:
		tools[index]->setTex(textool4);
		break;
	case SPEED_MAX:
		tools[index]->setTex(textool5);
		break;
	default:
		break;
	}
	tools[index]->placeTool();
}
void Game::checkBoom()
{
}

void Game::initBoomList()
{
	BoomListHead = 0;
	BoomListTail = 0;
	
	texPopo = hge->Texture_Load("picture/Popo.png");
	texPopoDir = hge->Texture_Load("picture/explosionDir.png");
	texPopoCen = hge->Texture_Load("picture/explosionCen.png");

	for (int i = 0; i < 100; i++)
	{
		isExplode[i] = 0;
		isPlace[i] = 0;
		boom[i] = new Boom(texPopo, 4, 8, 0, 0, 42, 40);	//hgeAnimation(  HTEXTURE tex,  int nframes,  float FPS,  float x,  float y,  float w,  float h);
		boom[i]->boomExpDir(texPopoDir);	//
		boom[i]->boomExpCen(texPopoCen, 3, 8, 0, 0, 40, 40);
	}
}
void Game::initToolsList()
{
	textool1 = hge->Texture_Load("picture/tool1.png");
	textool2 = hge->Texture_Load("picture/tool2.png");
	textool3 = hge->Texture_Load("picture/tool3.png");
	textool4 = hge->Texture_Load("picture/tool4.png");
	textool5 = hge->Texture_Load("picture/tool5.png");

	for (int i = 0; i < 100; i++)
	{
		toolsPlaced[i] = 0;
		tools[i] = new Tools(textool1, 4, 8, 0, 0, 42, 42);	//hgeAnimation(  HTEXTURE tex,  int nframes,  float FPS,  float x,  float y,  float w,  float h);
	}
}

bool Game::FrameFunc()
{
	if(!pThis->inGame)
		pThis->menuFrameFunc();
	else
		pThis->gameFrameFunc();
	return false;
}

bool Game::RenderFunc()
{
	pThis->hge->Gfx_BeginScene();
	if(!pThis->inGame)
		pThis->menuRenderFunc();
	else
		pThis->gameRenderFunc();
	pThis->hge->Gfx_EndScene();
	return false;
}

bool Game::menuFrameFunc()
{
	float dt=hge->Timer_GetDelta();
	static float t=0.0f;
	int id = 0;
	static int lastid=0;

	// If ESCAPE was pressed, tell the GUI to finish
	if(hge->Input_GetKeyState(HGEK_ESCAPE)) { lastid=5; gui->Leave(); }

	// We update the GUI and take an action if
	// one of the menu items was selected
	id=gui->Update(dt);
	if(id == -1)
	{
		switch(lastid)
		{
		case GUI_ID_play:    //点击Play后，直接载入一个地图
			{
				inGame = true;
				lastid = 100;
				gameStart();
				break;
			}

		case GUI_ID_hero:
			{
				showSpr = back1Spr;

				menu_info.hero1_info = 0;
				menu_info.hero2_info = 0;

				player1Text = new hgeGUIText(60, 120, 47, 50, 40, fnt);
				player1Text->bStatic;
				player1Text->SetText("Player1 :");
				player1Text->SetColor(0xFFFF7F00);

				herotype1 = new hgeGUIText(61, 230, 47, 400, 40, fnt);
				herotype1->bStatic;
				herotype1->SetText("NULL");
				herotype1->SetColor(0xFFFF7F00);

				gui->AddCtrl(player1Text);
				gui->AddCtrl(herotype1);

				player2Text = new hgeGUIText(62, 120, 334, 60, 40, fnt);
				player2Text->bStatic;
				player2Text->SetText("Player2 :");
				player2Text->SetColor(0xFFFF7F00);

				herotype2 = new hgeGUIText(63, 230, 334, 400, 40, fnt);
				herotype2->bStatic;
				herotype2->SetText("NULL");
				herotype2->SetColor(0xFFFF7F00);

				gui->AddCtrl(player2Text);
				gui->AddCtrl(herotype2);

				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}
		case GUI_ID_map:
			{
				showSpr = back2Spr;

				menu_info.map_info = 0;

				map = new hgeGUIText(64, 120, 70, 60, 40, fnt);
				map->bStatic;
				map->SetText("Map :");
				map->SetColor(0xFFFF7F00);

				maptype = new hgeGUIText(65, 260, 70, 80, 40, fnt);
				maptype->bStatic;
				maptype->SetText("NULL");
				maptype->SetColor(0xFFFF7F00);

				gui->AddCtrl(map);
				gui->AddCtrl(maptype);

				GUI_edit::edit_show(gui, GUI_ID_MAP_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}
		case GUI_ID_playreturn:
			{
				showSpr = backSpr;
				gui->DelCtrl(1);
				GUI_edit::edit_show(gui, GUI_ID_FIRST_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}
		case GUI_ID_hero1:
			{
				menu_info.hero1_info = 1;
				menu_info.hero1_occ = Saber;
				herotype1->SetText("Saber");

				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();

				break;
			}

		case GUI_ID_hero2:
			{
				menu_info.hero1_info = 1;
				herotype1->SetText("Locked");

				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}

		case GUI_ID_hero3:
			{
				menu_info.hero1_info = 1;

				herotype1->SetText("Locked");

				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}

		case GUI_ID_hero4:
			{
				menu_info.hero1_info = 1;

				herotype1->SetText("Locked");

				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}

		case GUI_ID_hero5:
			{
				menu_info.hero1_info = 5;

				herotype1->SetText("Assasin");
				menu_info.hero1_occ = Assassin;
				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}

		case GUI_ID_hero6:
			{
				menu_info.hero1_info = 6;
				herotype1->SetText("Basaker");
				menu_info.hero1_occ = Basaker;
				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}
		case GUI_ID_hero7:
			{
				menu_info.hero2_info = 1;

				herotype2->SetText("Saber");
				menu_info.hero2_occ = Saber;
				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();

				break;
			}
		case GUI_ID_hero8:
			{
				menu_info.hero2_info = 1;

				herotype2->SetText("Locked");

				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();

				break;
			}
		case GUI_ID_hero9:
			{
				menu_info.hero2_info = 1;

				herotype2->SetText("Locked");

				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();

				break;
			}

		case GUI_ID_hero10:
			{
				menu_info.hero2_info = 1;

				herotype2->SetText("Locked");

				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}

		case GUI_ID_hero11:
			{
				menu_info.hero2_info = 5;

				herotype2->SetText("Assasin");
				menu_info.hero2_occ = Assassin;
				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}

		case GUI_ID_hero12:
			{
				menu_info.hero2_info = 6;
				herotype2->SetText("Basaker");
				menu_info.hero2_occ = Basaker;
				GUI_edit::edit_show(gui, GUI_ID_HERO_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}
		case GUI_ID_heroConfirm:
			{
				if (menu_info.hero1_info == 0 || menu_info.hero2_info == 0)
				{
					GUI_edit::edit_show(gui, GUI_ID_HERO_H);
					gui->SetFocus(1);
					gui->Enter();
				}
				else {
					showSpr = backSpr;
					gui->DelCtrl(1);
					GUI_edit::edit_show(gui, GUI_ID_FIRST_H);
					gui->SetFocus(1);
					gui->Enter();
					gui->DelCtrl(60);
					gui->DelCtrl(61);
					gui->DelCtrl(62);
					gui->DelCtrl(63);
				}
				break;
			}

		case GUI_ID_map1:
			{
				menu_info.map_info = 1;

				maptype->SetText("snow");

				GUI_edit::edit_show(gui, GUI_ID_MAP_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}
		case GUI_ID_map2:
			{
				menu_info.map_info = 2;

				maptype->SetText("grassland");

				GUI_edit::edit_show(gui, GUI_ID_MAP_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}
		case GUI_ID_map3:
			{
				menu_info.map_info = 3;

				maptype->SetText("sand");

				GUI_edit::edit_show(gui, GUI_ID_MAP_H);
				gui->SetFocus(1);
				gui->Enter();
				break;
			}
		case GUI_ID_mapConfirm:
			{
				if (menu_info.map_info == 0 )
				{
					GUI_edit::edit_show(gui, GUI_ID_MAP_H);
					gui->SetFocus(1);
					gui->Enter();
				}
				else {
					showSpr = backSpr;
					gui->DelCtrl(1);
					GUI_edit::edit_show(gui, GUI_ID_FIRST_H);
					gui->SetFocus(1);
					gui->Enter();

					gui->DelCtrl(64);
					gui->DelCtrl(65);
				}
				break;
			}
		case GUI_ID_exit:
			{
							_exit(0);
			}
		default:
			gui->Enter();	
		}
	}
	else if(id) { lastid=id; gui->Leave(); }

	// Here we update our background animation

	return false;
}

bool Game::menuRenderFunc()
{
	showSpr->Render(0, 0);
	gui->Render();
	fnt->SetColor(0xFFFFFFFF);
	fnt->SetScale(1.1);
	return false;
}

bool Game::gameFrameFunc()
{
	float fDeltaTime = hge->Timer_GetDelta();
	//  这边负责右边的界面
	int id;
	static int lastid=0;
	// If ESCAPE was pressed, tell the GUI to finish
	if(hge->Input_GetKeyState(HGEK_ESCAPE)) { lastid=5; gameGUI->Leave(); }

	// We update the GUI and take an action if
	// one of the menu items was selected
	id=gameGUI->Update(fDeltaTime);
	if(id == -1)
	{
		switch(lastid)
		{
		case 11:
			if (!channel)  channel = hge->Effect_Play(snd1);   //关闭其他的背景音乐，播放snd1
			else
			{
				hge->Channel_Stop(channel);
				channel = hge->Effect_Play(snd1);
			}

			gameGUI->Enter();
			break;
		case 12:
			if (!channel)  channel = hge->Effect_Play(snd2); //关闭其他的背景音乐，播放snd2
			else
			{
				hge->Channel_Stop(channel);
				channel = hge->Effect_Play(snd2);
			}

			gameGUI->Enter();
			break;
		case 13:
			if (!channel)  channel = hge->Effect_Play(snd3); //关闭其他的背景音乐，播放snd3
			else
			{
				hge->Channel_Stop(channel);
				channel = hge->Effect_Play(snd3);
			}

			gameGUI->Enter();
			break;
		case 14:
			if (channel)  hge->Channel_Stop(channel); //关闭所有的背景音乐

			gameGUI->Enter();
			break;
		case 15:
			pause = !pause;
			//return (Pause);   //点击暂停按钮后，返回Pause参数
			gameGUI->Enter();
			break;
		case 16:
			gameOver();
			gameStart();
			//return (Rstart); //点击重新开始按钮后，返回Restart参数
			gameGUI->Enter();
			break;
		case 17:
			inGame = false;
			//return (Return);  //点击返回按钮后，返回Return参数
			break;

		case 18: return true;
		}
	}
	else if(id) { lastid=id; gameGUI->Leave(); }
	// 右边的界面结束

	if(player1home == 0 || player2home == 0)
		isGameOver = true;
	if(isGameOver)
		pause = true;
	if(pause)
		return false;
	gameTime += fDeltaTime;
	


	DIRECTION dirPlayer1 = NO;
	DIRECTION dirPlayer2 = NO;
	if(hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;
	if(hge->Input_GetKeyState(HGEK_A))
		dirPlayer1 = LEFT;
	else if(hge->Input_GetKeyState(HGEK_W))
		dirPlayer1 = UP;
	else if(hge->Input_GetKeyState(HGEK_S))
		dirPlayer1 = DOWN;
	else if(hge->Input_GetKeyState(HGEK_D))
		dirPlayer1 = RIGHT;

	if(hge->Input_GetKeyState(HGEK_LEFT))
		dirPlayer2 = LEFT;
	else if(hge->Input_GetKeyState(HGEK_UP))
		dirPlayer2 = UP;
	else if(hge->Input_GetKeyState(HGEK_DOWN))
		dirPlayer2 = DOWN;
	else if(hge->Input_GetKeyState(HGEK_RIGHT))
		dirPlayer2 = RIGHT;

	

	
	
	//Monsters
	for(int i = 0; i < monsternum; i++)
	{
		if(monster[i]->isDead())
			monster[i]->wantReborn(fDeltaTime);
		else{
			monster[i]->getHeroPosition(player1,player2);//获取英雄位置信息
			monster[i]->moveJudge();//判断下一步走法与走向
			DIRECTION dirMonster1 = monster[i]->getDirection();
			if(dirMonster1 == NO){
				monster[i]->Stop();
			}else{
				while(!(Game_Map->heroPass(monster[i]->getX(),monster[i]->getY(),monster[i]->getDirection())&&
					canHeroPassBomb(monster[i]->getX(),monster[i]->getY(),monster[i]->getDirection())&&
					monster[i]->isMonsterIn(dirMonster1,fDeltaTime)))
				{
					dirMonster1 = DIRECTION (rand()%4);
					/*if ((dirMonster1+1)>3) dirMonster1 = DOWN;
					else dirMonster1 = DIRECTION (dirMonster1+1);顺序改换方向也可以*/
					monster[i]->setDirection(dirMonster1);
				}
				monster[i]->Move(fDeltaTime);//下一步可行则走
				monster[i]->Play();
				}
				monster[i]->Update(fDeltaTime, dirMonster1);
			}
		}


	//Players
	if(Game_Map->isClamp(player1->getX(), player1->getY(),1) && player1ClampColdTime <= 0)					// 人物是否被夹子夹住，如果被夹住，停留2s
	{
		player1Clamp = 2;
		player1ClampColdTime = 10;
	}
	if(player1Clamp > 0)
		player1Clamp -= fDeltaTime;
	else{
		player1ClampColdTime -= fDeltaTime;
	if(player1->isDead())
		player1->wantReborn(fDeltaTime);
	else{
	if(dirPlayer1 == NO){
		player1->Stop();
	}else{
		if(! player1->isWalking())	
		{
			player1->Play();
		}
		player1->setDirection(dirPlayer1);
		if( Game_Map->heroPass( player1->getX(), player1->getY(), player1->getDirection(),1)&&
			canHeroPassBomb(player1->getX(), player1->getY(), player1->getDirection()))
			player1->Move(fDeltaTime);
		player1->Update(fDeltaTime, dirPlayer1);
	}
	}
	}
	
	if(Game_Map->isClamp(player2->getX(), player2->getY(),2) && player2ClampColdTime <= 0)
	{
		player2Clamp = 2;
		player2ClampColdTime = 10;
	}
	if(player2Clamp > 0)
		player2Clamp -= fDeltaTime;
	else{
		player2ClampColdTime -= fDeltaTime;
	if(player2->isDead())
		player2->wantReborn(fDeltaTime);
	else{
	if(dirPlayer2 == NO){
		player2->Stop();
	}else{
		if(! player2->isWalking())	
		{
			player2->Play();
		}
		player2->setDirection(dirPlayer2);
		if( Game_Map->heroPass( player2->getX(), player2->getY(), player2->getDirection(),2) &&
			canHeroPassBomb(player2->getX(), player2->getY(), player2->getDirection()))
			player2->Move(fDeltaTime);
		player2->Update(fDeltaTime, dirPlayer2);
	}
	}
	}

	// 判断玩家是否碰上怪物，如果碰上，则返回初始点
	// player1
	for(int i = 0 ; i < monsternum; i++){
		if(!monster[i]->isDead())
		if(heroHitMonster(player1, monster[i]))
		{
			player1->heroDie();
		}
	}
	// player2
	for(int i = 0 ; i < monsternum; i++){
		if(!monster[i]->isDead())
		if(heroHitMonster(player2, monster[i]))
		{
			player2->heroDie();
		}
	}
	// 判断玩家是否碰上道具，如果碰上，则设定功能，道具消失
	// player1
	for(int i = 0 ; i < 100; i++){
		if(toolsPlaced[i]==true)
		if(heroHitTools(player1, tools[i]))
		{
			player1->getTools(tools[i]->getToolsKind());
			toolsnum--;
			toolsPlaced[i] = false;
			//道具消失
		}
	}
	// player2
	for(int i = 0 ; i < 100; i++){
		if(toolsPlaced[i]==true)
		if(heroHitTools(player2, tools[i]))
		{
			player2->getTools(tools[i]->getToolsKind());
			toolsnum--;
			toolsPlaced[i] = false;
			//道具消失
		}
	}

	if(hge->Input_GetKeyState(HGEK_SPACE)){           //place the boom
		if((!player1->isDead())&&(!p1Bkey)&&(player1->canPutBoom()))	//是否按下，是否能放
		{
			int L;	//爆炸的四方向可通过距离	L[5] = {int up,int down,int left,int right , int L};
			int i = int((player1->getX())/BOX_HEIGHT);
			int j = int((player1->getY())/BOX_WIDTH);
			int x = BOX_HEIGHT*i;
			int y = BOX_WIDTH*j;
			L = player1->getLethality();
			if(noOtherBomb(x,y))
			{
			addBoom(x,y,L,1);
			player1->putBoom();	//当下P1放置的popo记号自增1
			}
		}
		
	
	}
	if(hge->Input_KeyDown(HGEK_SPACE))
		p1Bkey = true;
	if(hge->Input_KeyUp(HGEK_SPACE))
		p1Bkey = false;
	if(hge->Input_GetKeyState(HGEK_ENTER)) {
		if ((!player2->isDead())&&(!p2Bkey)&&(player2->canPutBoom()))
		{
			int L;	//爆炸的四方向可通过距离	L[5] = {int up,int down,int left,int right , int L};
			int i = int((player2->getX())/BOX_HEIGHT);
			int j = int((player2->getY())/BOX_WIDTH);
			int x = BOX_HEIGHT*i;
			int y = BOX_WIDTH*j;
			L = player2->getLethality();
			if(noOtherBomb(x,y))
			{
			addBoom(x,y,L,2);
			player2->putBoom();
			}
		}
	};
	if(hge->Input_KeyDown(HGEK_ENTER))
		p2Bkey = true;
	if(hge->Input_KeyUp(HGEK_ENTER))
		p2Bkey = false;

	/*while ((BoomListHead != BoomListTail)
		&&(isExplode[BoomListHead] == 0)&&(isPlace[BoomListHead] == 0))
		BoomListHead = (BoomListHead + 1) % 100;*/
	
	int index = BoomListHead;
	while (index != BoomListTail)
	{
		if (isExplode[index])
		{
			boom[index]->updataPopoCen(fDeltaTime);
			boom[index]->updataPopoDir(fDeltaTime);
			boom[index]->setBoomExpT(boom[index]->getBoomExpT()+1);
			if(boom[index]->getBoomExpT() == 1)
				hge->Effect_Play(boomMusic);
			if(boom[index]->getBoomExpT() == 20)
			{
				if(bombHero(index, player1->getX(), player1->getY()))
				{
					player1->heroDie();
				}
				if(bombHero(index, player2->getX(), player2->getY()))
				{
					player2->heroDie();
				}
				for(int i = 0; i < monsternum; i++){
					if(bombHero(index, monster[i]->getX(), monster[i]->getY()))
					{
						int x = int((monster[i]->getX())/BOX_HEIGHT)*BOX_HEIGHT;
						int y = int((monster[i]->getY())/BOX_WIDTH)*BOX_WIDTH;
						addTool(ToolsKind(rand()%5+1),x,y);//道具种类随机
						monster[i]->monsterDie();
					}
				}
			}
			if(boom[index]->getBoomExpT() == 300)
			{
				isExplode[index] = 0;
				boom[index]->stopPopoCen();	//POPO爆炸停止
				boom[index]->stopPopoDir();
				if (boom[index]->getWhose() == 1)
					player1->boomExp();
				else
					player2->boomExp();
				int L[4];
				boom[index]->getBoomExp(L);
				int i = boom[index]->getpopX()/BOX_WIDTH;
				int j = boom[index]->getpopY()/BOX_HEIGHT;
				if(Game_Map->canBomb(i,j-L[0]))						// 如果炸弹爆炸末端的箱子可以被炸掉，那就应该改变对应的状态
					Game_Map->setMap(i,j-L[0],2);
				if(Game_Map->bombHome(i,j-L[0]-1) == 1)               // P判断被炸的是否为家，如果为家，相应的减1;
					player1home--;
				else if(Game_Map->bombHome(i,j-L[0]-1) == 2)
					player2home--;
				if(Game_Map->canBomb(i,j+L[1]))
					Game_Map->setMap(i,j+L[1],2);
				if(Game_Map->bombHome(i,j+L[1]+1) == 1)               // P判断被炸的是否为家，如果为家，相应的减1;
					player1home--;
				else if(Game_Map->bombHome(i,j+L[1]+1) == 2)
					player2home--;
				if(Game_Map->canBomb(i-L[2],j))
					Game_Map->setMap(i-L[2],j,2);
				if(Game_Map->bombHome(i-L[2]-1,j) == 1)               // P判断被炸的是否为家，如果为家，相应的减1;
					player1home--;
				else if(Game_Map->bombHome(i-L[2]-1,j) == 2)
					player2home--;
				if(Game_Map->canBomb(i+L[3],j))
					Game_Map->setMap(i+L[3],j,2);
				if(Game_Map->bombHome(i+L[3]+1,j) == 1)               // P判断被炸的是否为家，如果为家，相应的减1;
					player1home--;
				else if(Game_Map->bombHome(i+L[3]+1,j) == 2)
					player2home--;
				
			}
		}
		if (isPlace[index])
		{
			boom[index]->stopPopoCen();	//测试
			boom[index]->updataPopo(fDeltaTime);
			boom[index]->setBoomT(boom[index]->getBoomT()+1);
			if(boom[index]->getBoomT() == boom[index]->getDelay())
			{
				boom[index]->stopPopo();	//POPO爆炸
				boom[index]->setBoomExpT(0);
				isExplode[index] = 1;
				isPlace[index] = 0;
				// 确定炸弹的范围
				int L[4]={};
				int i = boom[index]->getpopX()/BOX_WIDTH;
				int j = boom[index]->getpopY()/BOX_HEIGHT;
				while((L[0]<boom[index]->getboomLength())&&(Game_Map->canBombPass(i,j-L[0]-1))){
					L[0]++;
					if(Game_Map->canBomb(i,j-L[0]))
						break;
					bombTool(i,j-L[0]);
				}
				while((L[1]<boom[index]->getboomLength())&&(Game_Map->canBombPass(i,j+L[1]+1))){
					L[1]++;
					if(Game_Map->canBomb(i,j+L[1]))
						break;
					bombTool(i,j+L[1]);
				}
				while((L[2]<boom[index]->getboomLength())&&(Game_Map->canBombPass(i-L[2]-1,j))){
					L[2]++;
					if(Game_Map->canBomb(i-L[2],j))
						break;
					bombTool(i-L[2],j);
				}
				while((L[3]<boom[index]->getboomLength())&&(Game_Map->canBombPass(i+L[3]+1,j))){
					L[3]++;
					if(Game_Map->canBomb(i+L[3],j))
						break;
					bombTool(i+L[3],j);
				}
				boom[index]->setBoomExp(L[0],L[1],L[2],L[3]);              // 设置炸弹在各个方向上的范围
				boom[index]->placeBoomCen();
				boom[index]->placeBoomDir();	
			}
		}
		index = (index + 1) % 100;
	}

	
	return false;
}

bool Game::gameRenderFunc()
{
	// Render graphics
	//hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);
	gameInfoSprite->Render(0,0);
	Game_Map->Render();	
	
	if(!player1->isDead())
		player1->Render();
	if(!player2->isDead())
		player2->Render();
	for(int i = 0; i < monsternum; i++)
	{
		if(!monster[i]->isDead())
			monster[i]->Render();
	}
	for(int i = 0; i < 100; i++)
	{
		if(toolsPlaced[i])
			tools[i]->Render();
	} 
	int index = BoomListHead;
	while (index != BoomListTail)
	{
		if (isExplode[index])
		{
			boom[index]->RenderpopoCen();
			boom[index]->RenderpopoDir();
		}
		if (isPlace[index])
		{
			boom[index]->Renderpopo();
		}
		index = (index + 1) % 100;
	}

	gameGUI->Render();

	//////显示游戏时间
	int minute = (int)gameTime / 60;
	int second = gameTime - minute * 60; //将秒转换为分
	fnt->printf(760, 60, HGETEXT_RIGHT, "%d", minute);
	fnt->printf(870, 60, HGETEXT_RIGHT, "%d", second);

	//////显示1P 英雄复活所需要的时间
	fnt->printf(810,163,HGETEXT_RIGHT,"%2.1f",player1->getReviveTime());

	//////显示1P 英雄还可放置的炸弹数
	fnt->printf(960, 163, HGETEXT_RIGHT, "%d", player1->getLeftBomb());

	/////显示1P英雄的技能
	fnt->printf(850, 220, HGETEXT_RIGHT, "%s", player1->getOccupation());

	//////显示1P英雄技能冷却 时间
	fnt->printf(960, 220, HGETEXT_RIGHT, "%d", player1->getLethality());


	//////显示2P 英雄复活所需要的时间
	fnt->printf(810, 330,HGETEXT_RIGHT,"%2.1f",player2->getReviveTime());

	//////显示2P 英雄还可放置的炸弹数
	fnt->printf(960, 330, HGETEXT_RIGHT, "%d", player2->getLeftBomb());

	/////显示2P英雄的技能
	fnt->printf(850, 388, HGETEXT_RIGHT, "%s", player2->getOccupation());

	//////显示2P英雄技能冷却 时间
	fnt->printf(960, 388, HGETEXT_RIGHT, "%d", player2->getLethality());
	
	fnt->SetScale(2.0);
	if(isGameOver){
		if(player1home == 0)
			fnt->printf(500, 380,  HGETEXT_RIGHT, "player1 win!!" );
		else
			fnt->printf(500, 380,  HGETEXT_RIGHT, "player2 win!!" );
	}
	fnt->SetScale(1.0);
	



	return false;
}

bool Game::noOtherBomb(int x, int y)
{
	int index = BoomListHead;
	while(index != BoomListTail){
		if(isPlace[index] && boom[index]->getpopX() == x && boom[index]->getpopY() == y)
			return false;
		index++;
	}
	return true;
}

bool Game::bombHero(int boomIndex, double x, double y)
{
	int L[4];
	boom[boomIndex]->getBoomExp(L);
	int i = int(x) / BOX_WIDTH; 
	int j = int(y) / BOX_HEIGHT;
	int boomi = int(boom[boomIndex]->getpopX()) / BOX_WIDTH;
	int boomj = int(boom[boomIndex]->getpopY()) / BOX_HEIGHT; 
	// 上方
	if((i == boomi && (j >= boomj - L[0] && j <= boomj + L[1])) ||(j == boomj && (i >= boomi - L[2] && i <= boomi + L[3])))      // 判断人是否在炸弹的爆炸范围内
		return true;
	else 
		return false;
}

bool Game::canHeroPassBomb(double px, double py, DIRECTION dir)
{
	int index = BoomListHead;
	int boomi, boomj;
	int boomx, boomy;
	int i, j;
	double delta;
	double error = 4;
	while(index != BoomListTail)
	{
		if(!isPlace[index])
		{
			index++;
			continue;
		}
		boomx = boom[index]->getpopX()+BOX_WIDTH/2;
		boomy = boom[index]->getpopY()+BOX_HEIGHT/2; 
		boomi = boomx/BOX_WIDTH;
		boomj = boomy/BOX_HEIGHT;
		index++;
		if(abs(px-boomx) < BOX_WIDTH-error && abs(py-boomy)< BOX_HEIGHT-error)                  //判断是否在炸弹内，如果在，则可以行走；一旦超过炸弹范围，则无法行走。
			continue;
		switch(dir){
		case LEFT:
			i = int(px - 20) / BOX_WIDTH;
			j = int(py) / BOX_WIDTH;
			delta = py - j * BOX_WIDTH;	
			if((i == boomi && j == boomj)|| (delta < 20-error && (i == boomi && j-1 == boomj)) || (delta > 20+error && (i == boomi && j+1 == boomj)))
				return false;
			else
				continue;
		case RIGHT:
			i = int(px + 20) / BOX_WIDTH;
			j = int(py) / BOX_WIDTH;
			delta = py - j * BOX_WIDTH;	
			if( (i == boomi && j == boomj)|| (delta < 20-error && (i == boomi && j-1 == boomj)) || (delta > 20+error && (i == boomi && j+1 == boomj)))
				return false;
			else
				continue;
		case UP:
			i = int(px) / BOX_WIDTH;
			j = int(py-20) / BOX_WIDTH;
			delta = px - i * BOX_WIDTH;	
			if( (i == boomi && j == boomj)|| (delta < 20-error && (i-1 == boomi && j == boomj)) || (delta > 20+error && (i+1 == boomi && j == boomj)))
				return false;
			else
				continue;
		case DOWN:
			i = int(px) / BOX_WIDTH;
			j = int(py+20) / BOX_WIDTH;
			delta = px - i * BOX_WIDTH;	
			if( (i == boomi && j == boomj)|| (delta < 20-error && (i-1 == boomi && j == boomj)) || (delta > 20+error && (i+1 == boomi && j == boomj)))
				return false;
			else
				continue;
		case NO:
			continue;
		}	
	}
	return true;
}

bool Game::heroHitMonster(Hero *p, Monster *m)
{
	double hx,hy,mx,my;
	hx = p->getX();
	hy = p->getY();
	mx = m->getX();
	my = m->getY();
	if(abs(hx-mx)<20 && abs(hy-my) < 20)                       // 
		return true;
	else 
		return false;
}
bool Game::heroHitTools(Hero *p, Tools *t)
{
	double hx,hy,tx,ty;
	hx = p->getX();
	hy = p->getY();
	tx = t->getX()+20;
	ty = t->getY()+20;
	if(abs(hx-tx)<20 && abs(hy-ty) < 20)                      
		return true;
	else 
		return false;
}

void Game::gameMenu(hgeGUI *gui)
{

	//////音乐选择框
	gui->AddCtrl(new hgeGUIMenuItem(11, fnt, snd, 790, 480, 0.3f, "Ten Years"));
	gui->AddCtrl(new hgeGUIMenuItem(12, fnt, snd, 790, 525, 0.3f, "Hotel California"));
	gui->AddCtrl(new hgeGUIMenuItem(13, fnt, snd, 790, 560, 0.3f, "Spirited Away"));
	gui->AddCtrl(new hgeGUIMenuItem(14, fnt, snd, 955, 525, 0.3f, "Turn off"));

	/////显示游戏暂停、重新开始、返回的菜单
	gui->AddCtrl(new hgeGUIMenuItem(15, fnt, snd, 735, 620, 0.3f, "Pause"));
	gui->AddCtrl(new hgeGUIMenuItem(16, fnt, snd, 835, 620, 0.3f, "Restart"));
	gui->AddCtrl(new hgeGUIMenuItem(17, fnt, snd, 935, 620, 0.3f, "Return"));
}

void Game::bombTool(int i, int j)
{
	int x = i * BOX_WIDTH;
	int y = j * BOX_HEIGHT;
	for(int i = 0; i < 100; i++){
		if(toolsPlaced[i]){
			if(tools[i]->getX()==x && tools[i]->getY()==y)
				toolsPlaced[i] = false;
		}
	}
}

hgeGUIText* getText(hgeGUIText *text, char * buff, DWORD color){
	text->SetText(buff);
	text->SetColor(color);
	return text;
}



