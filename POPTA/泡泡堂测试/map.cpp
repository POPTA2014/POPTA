#include "map.h"

Box::Box(void){

};

Box::Box(int state, hgeQuad image){
	Box_image = image;
	Box_state = state;
}

Box::~Box(void){

};

void Box::state_change(int state){
	Box_state = state;
};

void Box::image_change(HGE *hge, hgeQuad image){
	Box_image = image;
}

void Box::Image_for_state(HGE *hge){
	switch(Box_state){
	case 0:
		Box_image.tex = hge->Texture_Load("wall1.png");
		break;
	case 1:
		Box_image.tex = hge->Texture_Load("wall2.png");
		break;
	case 2:
		Box_image.tex = hge->Texture_Load("wall3.png");
		break;
	default:
		break;
	}
}

void Box::Render(HGE *hge){
	hge->Gfx_RenderQuad(&(this->Box_image));
}

map::map(void)
{
}

map::map(HGE *hge, int state[BOX_NUM][BOX_NUM]){
	for(int i = 0; i < BOX_NUM; i++)
		for(int j = 0; j < BOX_NUM; j++)
		{
			box[i][j].Box_state = state[i][j];
			box[i][j].Image_for_state(hge);	
			box[i][j].Box_image.v[0].x = i * BOX_LENGTH; box[i][j].Box_image.v[0].y = j * BOX_WIDTH;
			box[i][j].Box_image.v[1].x = (i+1) * BOX_LENGTH; box[i][j].Box_image.v[1].y = j * BOX_WIDTH;
			box[i][j].Box_image.v[2].x = i * BOX_LENGTH; box[i][j].Box_image.v[2].y = (j+1) * BOX_WIDTH;
			box[i][j].Box_image.v[3].x = (i+1) * BOX_LENGTH; box[i][j].Box_image.v[3].y = (j+1) * BOX_WIDTH;
			box[i][j].Box_image.blend = BLEND_ALPHAADD | BLEND_COLORMUL | BLEND_ZWRITE;;
		}
}


map::~map(void)
{
}

void map::Render(HGE *hge){
	for(int i = 0; i < BOX_NUM; i++)
		for(int j = 0; j < BOX_NUM; j++)
			box[i][j].Render(hge);
}

