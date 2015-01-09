#include"GUI_edit.h"
//#include<hgeguictrls.h>

char* Name_first[GUI_ID_FIRST_T - GUI_ID_FIRST_H] = 
{
	"",
	"Play",
	"Hero",
	"Map",
	"Exit",
};

char* Name_play[GUI_ID_PLAY_T - GUI_ID_PLAY_H] =
{
	"",
	"Return",
};

char* Name_hero[GUI_ID_HERO_T - GUI_ID_HERO_H] = 
{
	"",
	"Saber",
	"Archer",
	"Caster",
	"Rider",
	"Assasin",
	"Basaker",
	"Saber",
	"Archer",
	"Caster",
	"Rider",
	"Assasin",
	"Basaker",
};

char* Name_map[GUI_ID_MAP_T - GUI_ID_MAP_H] = 
{
	"",
	"Snow",
	"Grassland",
	"Sand",
};



GUI_edit::GUI_edit()
{
}

GUI_edit::~GUI_edit()
{
}

bool GUI_edit::edit_init(hgeGUI* gui, hgeFont *fnt, HEFFECT snd, HTEXTURE  tex)
{
	int i = 1;
	//FIRST

	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_play,fnt,snd,400,370,0.0f,Name_first[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero, fnt, snd, 400, 410, 0.1f, Name_first[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_map, fnt, snd, 400, 450, 0.2f, Name_first[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_exit,fnt,snd,400,490,0.3f,Name_first[i++]));

	//Play
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_playreturn, fnt, snd, 600, 500, 0.0f, Name_play[i++]));
	//Hero
	i = 1;
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero1, fnt, snd, 80, 300, 0.3f, Name_hero[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero2, fnt, snd, 250, 300, 0.3f, Name_hero[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero3, fnt, snd, 420, 300, 0.3f, Name_hero[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero4, fnt, snd, 590, 300, 0.3f, Name_hero[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero5, fnt, snd, 760, 300, 0.3f, Name_hero[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero6, fnt, snd, 930, 300, 0.3f, Name_hero[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero7, fnt, snd, 80, 605, 0.3f, Name_hero[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero8, fnt, snd, 250, 605, 0.3f, Name_hero[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero9, fnt, snd, 420, 605, 0.3f, Name_hero[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero10, fnt, snd, 580, 605, 0.3f, Name_hero[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero11, fnt, snd, 760, 605, 0.3f, Name_hero[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_hero12, fnt, snd, 930, 605, 0.3f, Name_hero[i++]));
	gui->AddCtrl(new hgeGUIButton(GUI_ID_heroConfirm, 450, 630, 123, 44, tex, 0, 44));


	//Map
	i = 1;
	
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_map1, fnt, snd, 150, 430, 0.3f, Name_map[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_map2, fnt, snd, 500, 430, 0.3f, Name_map[i++]));
	gui->AddCtrl(new hgeGUIMenuItem(GUI_ID_map3, fnt, snd, 785, 430, 0.3f, Name_map[i++]));
	gui->AddCtrl(new hgeGUIButton(GUI_ID_mapConfirm, 450, 500, 123, 44, tex, 0, 44));

	return true;
}


void GUI_edit::edit_show(hgeGUI* gui,int page)
{
	bool bfirst = (page == GUI_ID_FIRST_H);
	for(int i = GUI_ID_FIRST_H+1; i < GUI_ID_FIRST_T; i++)
	{
		gui->ShowCtrl(i,bfirst);
		gui->EnableCtrl(i,bfirst);
	}

	bool bplay = (page == GUI_ID_PLAY_H);
	for (int i = GUI_ID_PLAY_H + 1; i < GUI_ID_PLAY_T; i++)
	{
		gui->ShowCtrl(i, bplay);
		gui->EnableCtrl(i, bplay);
	}

	bool bhero = (page == GUI_ID_HERO_H);
	for(int i = GUI_ID_HERO_H+1; i < GUI_ID_HERO_T; i++)
	{
		gui->ShowCtrl(i, bhero);
		gui->EnableCtrl(i, bhero);
	}

	bool bmap = (page == GUI_ID_MAP_H);
	for(int i = GUI_ID_MAP_H+1; i < GUI_ID_MAP_T; i++)
	{
		gui->ShowCtrl(i, bmap);
		gui->EnableCtrl(i, bmap);
	}
}