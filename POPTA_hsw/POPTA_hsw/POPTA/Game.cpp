#include "Game.h"


Game* Game::pThis;

void Game::gameStart()
{
	hge = hgeCreate(HGE_VERSION);
	hge->System_SetState(HGE_FRAMEFUNC, pThis->gameFrameFunc);
	hge->System_SetState(HGE_RENDERFUNC,pThis->gameRenderFunc);
	hge->System_SetState(HGE_TITLE, "POPTA");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, MAP_SIZE[0]);
	hge->System_SetState(HGE_SCREENHEIGHT, MAP_SIZE[1]);
	hge->System_SetState(HGE_SHOWSPLASH, false);
	hge->System_SetState(HGE_USESOUND, false);

	srand((unsigned)time(NULL));

	if(hge->System_Initiate()){

		loadMap();
		createHeroes();
		initBoomList();
		p1Bkey = false;
		p2Bkey = false;
		/*
		boomP1 = new Boom(texPopo, 4, 8, 0, 0, 42, 40);	//hgeAnimation(  HTEXTURE tex,  int nframes,  float FPS,  float x,  float y,  float w,  float h);
		boomP1->boomExpDir(texPopoDir);	//
		boomP1->boomExpCen(texPopoCen, 3, 8, 0, 0, 40, 40);
		boomP1->setboomLength(5);//爆炸长度
		boomP1->setBoomExp(3,3,3,3);//
		boomP1->setDelay(1200);
		*/

		hge->System_Start();

		// Delete created objects and free loaded resources
		delete gui;
		delete fnt;
		delete spr;
		hge->Effect_Free(snd);
		hge->Texture_Free(player1Pic);
		hge->Texture_Free(player2Pic);
		hge->Texture_Free(quad.tex);
	}

	// Clean up and shutdown
	//hge->System_Shutdown();
	//hge->Release();
}

void Game::loadMap()
{
	mapPic = hge->Texture_Load("picture/maptype1.png");
	Game_Map = new Map(mapPic);
	Game_Map->loadMap(0);
}

void Game::createHeroes()
{
	fnt = new hgeFont("picture/font1.fnt");
	player1Pic = hge->Texture_Load("picture/player1.png");
	player2Pic = hge->Texture_Load("picture/player2.png");
	player1 = new Hero(player1Pic, 4, 8, 100, 100);
	player1->setPositionX(20);
	player1->setPositionY(20);
	player1->setBoomLimit(3);
	player1->Play(DOWN);
	player2 = new Hero(player2Pic, 4, 8, 100, 100);
	player2->setPositionX(420);
	player2->setPositionY(420);
	player2->setBoomLimit(3);
	player2->Play(DOWN);

	boomNum_p1 = 0;
	boomNum_p2 = 0;
}

void Game::createMonsters()
{
}

void Game::addBoom(int x, int y, int L, int w)	//L[5] = {int up,int down,int left,int right , int L};
{
	int index = BoomListTail;
    BoomListTail = (BoomListTail + 1) % 100;

	isPlace[index] = 1;
	boom[index]->setBoom(x,y,L,w);//爆炸长度与方向
	boom[index]->setDelay(4200);
	boom[index]->setBoomT(0);	//获取安放popo时间
	boom[index]->placeBoom();	//放置泡泡动作
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

bool Game::gameFrameFunc()
{
	DIRECTION dirPlayer1 = NO;
	DIRECTION dirPlayer2 = NO;
	if(pThis->hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;
	if(pThis->hge->Input_GetKeyState(HGEK_A))
		dirPlayer1 = LEFT;
	else if(pThis->hge->Input_GetKeyState(HGEK_W))
		dirPlayer1 = UP;
	else if(pThis->hge->Input_GetKeyState(HGEK_S))
		dirPlayer1 = DOWN;
	else if(pThis->hge->Input_GetKeyState(HGEK_D))
		dirPlayer1 = RIGHT;

	if(pThis->hge->Input_GetKeyState(HGEK_LEFT))
		dirPlayer2 = LEFT;
	else if(pThis->hge->Input_GetKeyState(HGEK_UP))
		dirPlayer2 = UP;
	else if(pThis->hge->Input_GetKeyState(HGEK_DOWN))
		dirPlayer2 = DOWN;
	else if(pThis->hge->Input_GetKeyState(HGEK_RIGHT))
		dirPlayer2 = RIGHT;

	

	float fDeltaTime = pThis->hge->Timer_GetDelta();

	if(dirPlayer1 == NO){
		pThis->player1->Stop();
	}else{
		if(! pThis->player1->isWalking())	
		{
			pThis->player1->Play();
		}
		pThis->player1->setDirection(dirPlayer1);
		if( pThis->Game_Map->heroPass( pThis->player1->getPositionX(), pThis->player1->getPositionY(), pThis->player1->getDirection())&&
			pThis->canHeroPassBomb(pThis->player1->getPositionX(), pThis->player1->getPositionY(), pThis->player1->getDirection()))
			pThis->player1->Move(fDeltaTime);
		pThis->player1->Update(fDeltaTime, dirPlayer1);
	}

	if(dirPlayer2 == NO){
		pThis->player2->Stop();
	}else{
		if(! pThis->player2->isWalking())	
		{
			pThis->player2->Play();
		}
		pThis->player2->setDirection(dirPlayer2);
		if( pThis->Game_Map->heroPass( pThis->player2->getPositionX(), pThis->player2->getPositionY(), pThis->player2->getDirection()) &&
			pThis->canHeroPassBomb(pThis->player2->getPositionX(), pThis->player2->getPositionY(), pThis->player2->getDirection()))
			pThis->player2->Move(fDeltaTime);
		pThis->player2->Update(fDeltaTime, dirPlayer2);
	}
	if(pThis->hge->Input_GetKeyState(HGEK_SPACE)){           //place the boom
		if((!pThis->p1Bkey)&&(pThis->player1->canPutBoom()))	//是否按下，是否能放
		{
			int L;	//爆炸的四方向可通过距离	L[5] = {int up,int down,int left,int right , int L};
			int i = int((pThis->player1->getPositionX())/BOX_HEIGHT);
			int j = int((pThis->player1->getPositionY())/BOX_WIDTH);
			int x = BOX_HEIGHT*i;
			int y = BOX_WIDTH*j;
			L = pThis->player1->getLethality();
			if(pThis->noOtherBomb(x,y))
			{
			pThis->addBoom(x,y,L,1);
			pThis->player1->putBoom();	//当下P1放置的popo记号自增1
			}
		}
		
		
		/*
		pThis->boomP1->setpopX(BOX_HEIGHT*(int((pThis->player1->getPositionX())/BOX_HEIGHT)));	//得出泡泡的横坐标位置
		pThis->boomP1->setpopY(BOX_WIDTH*(int((pThis->player1->getPositionY())/BOX_WIDTH)));		//得出泡泡的纵坐标位置
		pThis->isPlace=true;
		pThis->boomP1->setBoomT(0);	//获取安放popo时间
		pThis->boomP1->placeBoom();	//放置泡泡动作
		pThis->boomP1->setBoomExp(5,5,5,5);	//front left down right
		*/
	}
	if(pThis->hge->Input_KeyDown(HGEK_SPACE))
		pThis->p1Bkey = true;
	if(pThis->hge->Input_KeyUp(HGEK_SPACE))
		pThis->p1Bkey = false;
	if(pThis->hge->Input_GetKeyState(HGEK_ENTER)) {
		if ((!pThis->p2Bkey)&&(pThis->player2->canPutBoom()))
		{
			int L;	//爆炸的四方向可通过距离	L[5] = {int up,int down,int left,int right , int L};
			int i = int((pThis->player2->getPositionX())/BOX_HEIGHT);
			int j = int((pThis->player2->getPositionY())/BOX_WIDTH);
			int x = BOX_HEIGHT*i;
			int y = BOX_WIDTH*j;
			L = pThis->player2->getLethality();
			if(pThis->noOtherBomb(x,y))
			{
			pThis->addBoom(x,y,L,2);
			pThis->player2->putBoom();
			}
		}
	};
	if(pThis->hge->Input_KeyDown(HGEK_ENTER))
		pThis->p2Bkey = true;
	if(pThis->hge->Input_KeyUp(HGEK_ENTER))
		pThis->p2Bkey = false;

	/*while ((pThis->BoomListHead != pThis->BoomListTail)
		&&(pThis->isExplode[pThis->BoomListHead] == 0)&&(pThis->isPlace[pThis->BoomListHead] == 0))
		pThis->BoomListHead = (pThis->BoomListHead + 1) % 100;*/
	
	int index = pThis->BoomListHead;
	while (index != pThis->BoomListTail)
	{
		if (pThis->isExplode[index])
		{
			pThis->boom[index]->updataPopoCen(fDeltaTime);
			pThis->boom[index]->updataPopoDir(fDeltaTime);
			pThis->boom[index]->setBoomExpT(pThis->boom[index]->getBoomExpT()+1);
			if(pThis->boom[index]->getBoomExpT() == 300)
			{
				pThis->isExplode[index] = 0;
				pThis->boom[index]->stopPopoCen();	//POPO爆炸停止
				pThis->boom[index]->stopPopoDir();
				if (pThis->boom[index]->getWhose() == 1)
					pThis->player1->boomExp();
				else
					pThis->player2->boomExp();
				int L[4];
				pThis->boom[index]->getBoomExp(L);
				int i = pThis->boom[index]->getpopX()/BOX_WIDTH;
				int j = pThis->boom[index]->getpopY()/BOX_HEIGHT;
				if(pThis->Game_Map->canBomb(i,j-L[0]))						// 如果炸弹爆炸末端的箱子可以被炸掉，那就应该改变对应的状态
					pThis->Game_Map->setMap(i,j-L[0],2);
				if(pThis->Game_Map->canBomb(i,j+L[1]))
					pThis->Game_Map->setMap(i,j+L[1],2);
				if(pThis->Game_Map->canBomb(i-L[2],j))
					pThis->Game_Map->setMap(i-L[2],j,2);
				if(pThis->Game_Map->canBomb(i+L[3],j))
					pThis->Game_Map->setMap(i+L[3],j,2);
				if(pThis->bombHero(index, pThis->player1))
				{
					pThis->player1->heroDie();
					pThis->player1->setPositionX(20);
					pThis->player1->setPositionY(20);
				}
				if(pThis->bombHero(index, pThis->player2))
				{
					pThis->player2->heroDie();
					pThis->player2->setPositionX(420);
					pThis->player2->setPositionY(420);
				}
			}
		}
		if (pThis->isPlace[index])
		{
			pThis->boom[index]->stopPopoCen();	//测试
			pThis->boom[index]->updataPopo(fDeltaTime);
			pThis->boom[index]->setBoomT(pThis->boom[index]->getBoomT()+1);
			if(pThis->boom[index]->getBoomT() == pThis->boom[index]->getDelay())
			{
				pThis->boom[index]->stopPopo();	//POPO爆炸
				pThis->boom[index]->setBoomExpT(0);
				pThis->isExplode[index] = 1;
				pThis->isPlace[index] = 0;
				// 确定炸弹的范围
				int L[4]={};
				int i = pThis->boom[index]->getpopX()/BOX_WIDTH;
				int j = pThis->boom[index]->getpopY()/BOX_HEIGHT;
				while((L[0]<pThis->boom[index]->getboomLength())&&(pThis->Game_Map->canBombPass(i,j-L[0]-1))){
					L[0]++;
					if(pThis->Game_Map->canBomb(i,j-L[0]))
						break;
				}
				while((L[1]<pThis->boom[index]->getboomLength())&&(pThis->Game_Map->canBombPass(i,j+L[1]+1))){
					L[1]++;
					if(pThis->Game_Map->canBomb(i,j+L[1]))
						break;
				}
				while((L[2]<pThis->boom[index]->getboomLength())&&(pThis->Game_Map->canBombPass(i-L[2]-1,j))){
					L[2]++;
					if(pThis->Game_Map->canBomb(i-L[2],j))
						break;
				}
				while((L[3]<pThis->boom[index]->getboomLength())&&(pThis->Game_Map->canBombPass(i+L[3]+1,j))){
					L[3]++;
					if(pThis->Game_Map->canBomb(i+L[3],j))
						break;
				}
				pThis->boom[index]->setBoomExp(L[0],L[1],L[2],L[3]);              // 设置炸弹在各个方向上的范围
				pThis->boom[index]->placeBoomCen();
				pThis->boom[index]->placeBoomDir();	
			}
		}
		index = (index + 1) % 100;
	}

	/*
	if(pThis->isPlace){
		pThis->isExp=false;
		pThis->boomP1->stopPopoCen();	//测试
		pThis->boomP1->updataPopo(fDeltaTime);
		pThis->boomP1->setBoomT(pThis->boomP1->getBoomT()+1);
		if(pThis->boomP1->getBoomT()==pThis->boomP1->getDelay()){
			pThis->isPlace=false;
			pThis->boomP1->stopPopo();	//POPO爆炸
			pThis->isExp = true;
			pThis->boomP1->setBoomExpT(0);
			pThis->boomP1->placeBoomCen();
			pThis->boomP1->placeBoomDir();
		}
	}else{
	}
	if(pThis->isExp){
		pThis->boomP1->updataPopoCen(fDeltaTime);
		pThis->boomP1->updataPopoDir(fDeltaTime);
		pThis->boomP1->setBoomExpT(pThis->boomP1->getBoomExpT()+1);
		if(pThis->boomP1->getBoomExpT()==500){
			pThis->isExp=false;
			pThis->boomP1->stopPopoCen();	//POPO爆炸停止
			pThis->boomP1->stopPopoDir();
		}

	}
	*/
	return false;
}

bool Game::gameRenderFunc()
{
	// Render graphics
	pThis->hge->Gfx_BeginScene();
	pThis->hge->Gfx_Clear(0);
	pThis->Game_Map->Render();	
	pThis->player1->Render();
	pThis->player2->Render();

	int index = pThis->BoomListHead;
	while (index != pThis->BoomListTail)
	{
		if (pThis->isExplode[index])
		{
			pThis->boom[index]->RenderpopoCen();
			pThis->boom[index]->RenderpopoDir();
		}
		if (pThis->isPlace[index])
		{
			pThis->boom[index]->Renderpopo();
			pThis->fnt->printf(5, 5, HGETEXT_LEFT, "%d",pThis->BoomListTail);
		}
		index = (index + 1) % 100;
	}
	/*
	if(pThis->isPlace){
		pThis->boomP1->Renderpopo();	//放置泡泡		
	}
	if(pThis->isExp){
		pThis->boomP1->RenderpopoCen();
		pThis->boomP1->RenderpopoDir();
	}
	*/
	pThis->hge->Gfx_EndScene();


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

bool Game::bombHero(int boomIndex, Hero* p)
{
	int L[4];
	boom[boomIndex]->getBoomExp(L);
	int i = int(p->getPositionX()) / BOX_WIDTH; 
	int j = int(p->getPositionY()) / BOX_HEIGHT;
	int boomi = int(boom[boomIndex]->getpopX()) / BOX_WIDTH;
	int boomj = int(boom[boomIndex]->getpopY()) / BOX_HEIGHT; 
	// 上方
	if((i == boomi && (j >= boomj - L[0] || j <= boomj + L[1])) ||(j == boomj && (i >= boomi - L[2] || i <= boomi + L[3])))      // 判断人是否在炸弹的爆炸范围内
		return true;
	else 
		return false;
}

bool Game::canHeroPassBomb(int x, int y, DIRECTION dir)
{
	int index = BoomListHead;
	int i,i0;
	int j,j0;
	int boomi, boomj;
	switch(dir){
	case DOWN:
		i = x / BOX_WIDTH;
		j = (y+20) / BOX_HEIGHT;
		break;
	case UP:
		i = x / BOX_WIDTH;
		j = (y-20) / BOX_HEIGHT;
		break;
	case LEFT:
		i = (x-20) / BOX_WIDTH;
		j = y / BOX_HEIGHT;
		break;
	case RIGHT:
		i = (x+20) / BOX_WIDTH;
		j = y / BOX_HEIGHT;
		break;
	default:
		break;
	}	
	i0 = x / BOX_WIDTH;
	j0 = y / BOX_HEIGHT;
	while(index != BoomListTail)
	{
		boomi = boom[index]->getpopX() / BOX_WIDTH;
		boomj = boom[index]->getpopY() / BOX_HEIGHT; 
		index++;
		if(i0 == boomi && j0 == boomj)                                       // 如果英雄目前处于炸弹上，则任何一个方向都可以前进
			continue;
		if(i == boomi && j == boomj && isPlace[index])
			return false;
	}
	return true;
}
