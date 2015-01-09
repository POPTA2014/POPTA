/*
** Haaf's Game Engine 1.8
** Copyright (C) 2003-2007, Relish Games
** hge.relishgames.com
**
** hge_tut06 - Creating menus
*/


// Copy the files "menu.wav", "font1.fnt", "font1.png",
// "bg.png" and "cursor.png" from the folder "precompiled"
// to the folder with executable file. Also copy hge.dll
// and bass.dll to the same folder.

//
//#include "..\..\include\hge.h"
//#include "..\..\include\hgefont.h"
//#include "..\..\include\hgegui.h"

#include "menuitem.h"
#include "GUI_edit.h"
#include <math.h>


// Pointer to the HGE interface.
// Helper classes require this to work.
HGE *hge=0;

// Some resource handles
HEFFECT				snd;
HTEXTURE			tex;

//--back pic
HTEXTURE			back;
HTEXTURE			back_1, back_2, back_3, back_4, button;

hgeSprite			*backSpr;
hgeSprite			*back1Spr, *back2Spr, *back3Spr, *back4Spr;
hgeSprite			*showSpr;

// Pointers to the HGE objects we will use
hgeGUI				*gui;

hgeFont				*fnt;
hgeSprite			*spr;
hgeGUIText			*error_text;
hgeGUIText          *herotype1;
hgeGUIText          *herotype2;
hgeGUIText           *player1;
hgeGUIText           *player2;
hgeGUIText           *map;
hgeGUIText           *maptype;
struct Info{
	int hero1_info;
	int hero2_info;
	int map_info;
};

struct Info menu_info;

bool FrameFunc()
{
	float dt=hge->Timer_GetDelta();
	static float t=0.0f;
	float tx,ty;
	int id;
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
							   if (menu_info.hero1_info == 0 || menu_info.hero1_info == 0|| menu_info.map_info == 0){
								   showSpr = back4Spr;

								   gui->DelCtrl(1);

								   error_text = new hgeGUIText(1, 600, 220, 300, 300, fnt);
								   error_text->SetText("Please choose hero type and map type");
								   error_text->SetColor(0xFFFF7F00);
								   gui->AddCtrl(error_text);

								   GUI_edit::edit_show(gui, GUI_ID_PLAY_H);

								    gui->SetFocus(1);
			                        gui->Enter();
							   }
							   else 
								   showSpr = back3Spr;

							            break;
		   }

		   case GUI_ID_hero:
		   {
			                            showSpr = back1Spr;

										menu_info.hero1_info = 0;
										menu_info.hero2_info = 0;

										player1 = new hgeGUIText(60, 120, 47, 50, 40, fnt);
										player1->bStatic;
										player1->SetText("Player1 :");
										player1->SetColor(0xFFFF7F00);

										herotype1 = new hgeGUIText(61, 230, 47, 80, 40, fnt);
										herotype1->bStatic;
										herotype1->SetText("NULL");
										herotype1->SetColor(0xFFFF7F00);

										gui->AddCtrl(player1);
										gui->AddCtrl(herotype1);
	
										player2 = new hgeGUIText(62, 120, 304, 60, 40, fnt);
										player2->bStatic;
										player2->SetText("Player2 :");
										player2->SetColor(0xFFFF7F00);

										herotype2 = new hgeGUIText(63, 230, 304, 80, 40, fnt);
										herotype2->bStatic;
										herotype2->SetText("NULL");
										herotype2->SetColor(0xFFFF7F00);

										gui->AddCtrl(player2);
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

										map = new hgeGUIText(64, 120, 100, 60, 40, fnt);
										map->bStatic;
										map->SetText("Map :");
										map->SetColor(0xFFFF7F00);

										maptype = new hgeGUIText(65, 260, 100, 80, 40, fnt);
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

								  herotype1->SetText("Saber");

								  GUI_edit::edit_show(gui, GUI_ID_HERO_H);
								  gui->SetFocus(1);
								  gui->Enter();

								  break;
			}
				
			case GUI_ID_hero2:
			{
								  menu_info.hero1_info = 2;

								  herotype1->SetText("Archer");

								  GUI_edit::edit_show(gui, GUI_ID_HERO_H);
								  gui->SetFocus(1);
								  gui->Enter();
								  break;
			}
				
			case GUI_ID_hero3:
			{
								 menu_info.hero1_info = 3;
		
								 herotype1->SetText("Caster");

								 GUI_edit::edit_show(gui, GUI_ID_HERO_H);
								 gui->SetFocus(1);
								 gui->Enter();
								 break;
			}
				
			case GUI_ID_hero4:
			{
								 menu_info.hero1_info = 4;

								 herotype1->SetText("Rider");

								 GUI_edit::edit_show(gui, GUI_ID_HERO_H);
								 gui->SetFocus(1);
								 gui->Enter();
								 break;
			}
				
			case GUI_ID_hero5:
			{
								 menu_info.hero1_info = 5;

								 herotype1->SetText("Assasin");

								 GUI_edit::edit_show(gui, GUI_ID_HERO_H);
								 gui->SetFocus(1);
								 gui->Enter();
								 break;
			}
				
			case GUI_ID_hero6:
			{
								 menu_info.hero1_info = 6;

								 herotype1->SetText("Basaker");

								 GUI_edit::edit_show(gui, GUI_ID_HERO_H);
								 gui->SetFocus(1);
								 gui->Enter();
								 break;
			}
			case GUI_ID_hero7:
			{
								 menu_info.hero2_info = 1;

								 herotype2->SetText("Saber");

								 GUI_edit::edit_show(gui, GUI_ID_HERO_H);
								 gui->SetFocus(1);
								 gui->Enter();

								 break;
			}
			case GUI_ID_hero8:
			{
								 menu_info.hero2_info = 2;

								 herotype2->SetText("Archer");

								 GUI_edit::edit_show(gui, GUI_ID_HERO_H);
								 gui->SetFocus(1);
								 gui->Enter();

								 break;
			}
			case GUI_ID_hero9:
			{
								 menu_info.hero2_info = 3;

								 herotype2->SetText("Caster");

								 GUI_edit::edit_show(gui, GUI_ID_HERO_H);
								 gui->SetFocus(1);
								 gui->Enter();

								 break;
			}

			case GUI_ID_hero10:
			{
								 menu_info.hero2_info = 4;

								 herotype2->SetText("Rider");

								 GUI_edit::edit_show(gui, GUI_ID_HERO_H);
								 gui->SetFocus(1);
								 gui->Enter();
								 break;
			}

			case GUI_ID_hero11:
			{
								 menu_info.hero2_info = 5;

								 herotype2->SetText("Assasin");

								 GUI_edit::edit_show(gui, GUI_ID_HERO_H);
								 gui->SetFocus(1);
								 gui->Enter();
								 break;
			}

			case GUI_ID_hero12:
			{
								 menu_info.hero2_info = 6;

								 herotype2->SetText("Basaker");

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

								maptype->SetText("sea world");

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

								maptype->SetText("snow");

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
								return true;
			}
	}
	}
	else if(id) { lastid=id; gui->Leave(); }

	// Here we update our background animation

	return false;
}


bool RenderFunc()
{
	// Render graphics
	hge->Gfx_BeginScene();
	showSpr->Render(0, 0);
	gui->Render();
	fnt->SetColor(0xFFFFFFFF);
	fnt->SetScale(1.1);
	//fnt->printf(5, 5, HGETEXT_LEFT, "dt:%.3f\nFPS:%d", hge->Timer_GetDelta(), hge->Timer_GetFPS());
	hge->Gfx_EndScene();

	return false;
}


int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	hge = hgeCreate(HGE_VERSION);

	hge->System_SetState(HGE_LOGFILE, "hge_tut06.log");
	hge->System_SetState(HGE_FRAMEFUNC, FrameFunc);
	hge->System_SetState(HGE_RENDERFUNC, RenderFunc);
	hge->System_SetState(HGE_TITLE, "POPTA");
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_SCREENWIDTH, 800);
	hge->System_SetState(HGE_SCREENHEIGHT, 600);
	hge->System_SetState(HGE_SCREENBPP, 32);
	//hge->System_SetState(HGE_SHOWSPLASH, false);//是否显示HGE初始化图标

	if(hge->System_Initiate())
	{

		// Load sound and textures
		tex = hge->Texture_Load("cursor.png");
		snd = hge->Effect_Load("menu.wav");

		back = hge->Texture_Load("background.png");
		back_1 = hge->Texture_Load("hero.png");
		back_2 = hge->Texture_Load("map.png");
		back_3 = hge->Texture_Load("start_0.png");
		back_4 = hge->Texture_Load("error.png");
		button = hge->Texture_Load("button.jpg");
		if (!tex || !snd || !back || !back_1 || !back_2 || !back_3 || !back_4||!button)
		{
			// If one of the data files is not found, display
			// an error message and shutdown.
			MessageBox(NULL, "Can't load HERO.PNG, BCACKGROUND.PNG,MAP.PNG,START.PNF,ERROR.PNG,CURSOR.PNG or MENU.WAV", "Error", MB_OK | MB_ICONERROR | MB_APPLMODAL);
			hge->System_Shutdown();
			hge->Release();
			return 0;
		}

		// Load the font, create the cursor sprite
		fnt=new hgeFont("font1.fnt");
		spr=new hgeSprite(tex,0,0,32,32);

		//-back spr
		backSpr = new hgeSprite(back, 0, 0, 800, 600);

		back1Spr = new hgeSprite(back_1, 0, 0, 800, 600);
		back2Spr = new hgeSprite(back_2, 0, 0, 800, 600);
		back3Spr = new hgeSprite(back_3, 0, 0, 800, 600);
		back4Spr = new hgeSprite(back_4, 0, 0, 800, 600);

		showSpr = backSpr;
		
		menu_info.hero1_info = 0;
		menu_info.hero2_info = 0;
		menu_info.map_info = 0;

		// Create and initialize the GUI
		gui=new hgeGUI();

		GUI_edit::edit_init(gui, fnt, snd,button);
		GUI_edit::edit_show(gui, GUI_ID_FIRST_H);

		gui->SetNavMode(HGEGUI_UPDOWN | HGEGUI_CYCLED);
		gui->SetCursor(spr);
		gui->SetFocus(1);
		gui->Enter();

		// Let's rock now!
		hge->System_Start();

		// Delete created objects and free loaded resources
		delete gui;
		delete fnt;
		delete spr;
		hge->Effect_Free(snd);
		hge->Texture_Free(tex);
		hge->Texture_Free(back);
		hge->Texture_Free(back_1);
		hge->Texture_Free(back_2);
		hge->Texture_Free(back_3);
	}

	// Clean up and shutdown
	hge->System_Shutdown();
	hge->Release();
	return 0;
}
