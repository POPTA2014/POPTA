#pragma once
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
const int MAP_SIZE[2] = {680, 680};
const int BOX_NUM = 17;
const int BOX_LENGTH = 40;
const int BOX_WIDTH = 40;



class Box
{
public:
	Box(void);
	Box(int state, hgeQuad image);
	~Box(void);
	void state_change(int s);
	void image_change(HGE *hge, hgeQuad image);
	void Image_for_state(HGE *hge);
	void Render(HGE *hge);
	friend class map;
private:
	int Box_state;
	hgeQuad Box_image;        //该方格上对应的图片
};

class map
{
public:
	map(void);
	map(HGE *hge, int state[BOX_NUM][BOX_NUM]);
	~map(void);
	void Render(HGE *hge);
private:
	Box box[BOX_NUM][BOX_NUM];
};

