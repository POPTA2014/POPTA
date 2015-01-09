#ifndef GUI_EDIT
#define GUI_EDIT


#include <hge.h>
#include <hgegui.h>
#include <hgefont.h>
#include <hgecolor.h>
#include"menuitem.h"


//--

enum GUI_ID_FIRST
{
	GUI_ID_FIRST_H = 10,

	GUI_ID_play,
	GUI_ID_hero,
	GUI_ID_map,
	GUI_ID_exit,

	GUI_ID_FIRST_T
};

//--

enum GUI_ID_PLAY
{
	GUI_ID_PLAY_H = 16,

	GUI_ID_playreturn,

	GUI_ID_PLAY_T
};

//--

enum GUI_ID_HERO
{
	GUI_ID_HERO_H = 20,

	GUI_ID_hero1,
	GUI_ID_hero2,
	GUI_ID_hero3,
	GUI_ID_hero4,
	GUI_ID_hero5,
	GUI_ID_hero6,

	GUI_ID_hero7,
	GUI_ID_hero8,
	GUI_ID_hero9,
	GUI_ID_hero10,
	GUI_ID_hero11,
	GUI_ID_hero12,
	GUI_ID_heroConfirm,

	GUI_ID_HERO_T
};


//--

enum GUI_ID_MAP
{
	GUI_ID_MAP_H = 50,

	GUI_ID_map1,
	GUI_ID_map2,
	GUI_ID_map3,
	GUI_ID_mapConfirm,

	GUI_ID_MAP_T
};




class GUI_edit
{
public:
	GUI_edit();
	~GUI_edit();

	static bool edit_init(hgeGUI* gui, hgeFont *fnt, HEFFECT snd, HTEXTURE  tex);

	static void edit_show(hgeGUI* gui,int page);

private:

};


#endif