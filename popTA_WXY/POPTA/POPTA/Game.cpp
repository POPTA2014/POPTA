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
	player1->setBoomLimit(10);
	player1->Play(DOWN);
	player2 = new Hero(player2Pic, 4, 8, 100, 100);
	player2->setPositionX(420);
	player2->setPositionY(420);
	player2->Play(DOWN);

	boomNum_p1 = 0;
	boomNum_p2 = 0;
}

void Game::createMonsters()
{
}

void Game::addBoom(int x, int y, int L, int w)
{
	int index = BoomListTail;
    BoomListTail = (BoomListTail + 1) % 100;

	isPlace[index] = 1;
	boom[index]->setBoom(x,y,L,w);//爆炸长度
	boom[index]->setDelay(1200);
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
		if( pThis->Game_Map->heroPass( pThis->player1->getPositionX(), pThis->player1->getPositionY(), pThis->player1->getDirection()))
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
		if( pThis->Game_Map->heroPass( pThis->player2->getPositionX(), pThis->player2->getPositionY(), pThis->player2->getDirection()))
			pThis->player2->Move(fDeltaTime);
		pThis->player2->Update(fDeltaTime, dirPlayer2);
	}

	if(pThis->hge->Input_GetKeyState(HGEK_SPACE)){           //place the boom
		if(!pThis->p1Bkey)
		{
				int x = BOX_HEIGHT*(int((pThis->player1->getPositionX())/BOX_HEIGHT));
				int y = BOX_WIDTH*(int((pThis->player1->getPositionY())/BOX_WIDTH));
				int L = pThis->player1->getLethality();
				pThis->addBoom(x,y,L,1);
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
		if (!pThis->p2Bkey)
		{
			int x = BOX_HEIGHT*(int((pThis->player2->getPositionX())/BOX_HEIGHT));
			int y = BOX_WIDTH*(int((pThis->player2->getPositionY())/BOX_WIDTH));
			int L = pThis->player2->getLethality();
			pThis->addBoom(x,y,L,2);
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
				pThis->boom[index]->placeBoomCen();
				pThis->boom[index]->placeBoomDir();	
				pThis->isExplode[index] = 1;
				pThis->isPlace[index] = 0;
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