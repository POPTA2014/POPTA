#include "Tools.h"


Tools::Tools(void)
{
}

Tools::Tools(HTEXTURE texTools,int nframes,float FPS,float x,float y,float w,float h)
{
	toolX = x;toolY = y;
	tool = new hgeAnimation(texTools,nframes,FPS,x,y,w,h);
}
Tools::~Tools(void)
{
}
void Tools::setTool(ToolsKind kind,int x,int y){
	toolskind = kind;
	toolX = x;
	toolY = y;
}
void Tools::setTex(HTEXTURE texTools){
	tool->SetTexture(texTools);
}
void Tools::Render(){
	tool->Render(toolX,toolY);
}
void Tools::placeTool(){//放置道具
	tool->Play();
}
ToolsKind Tools::getToolsKind(){//返回道具类型
	return toolskind;
}

void Tools::updateTool(float fDeltaTime){
	tool->Update(fDeltaTime);
}

void Tools::setPosition(int x,int y){
	toolX=x;
	toolY=y;
}
int Tools::getX(){
	return toolX;
}
int Tools::getY(){
	return toolY;
}
