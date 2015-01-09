#ifndef _TOOLS_H_
#define _TOOLS_H_
#include <hge.h>
#include <hgeanim.h>

#define MAX_SPEED 500
#define MAX_POWER 5 
#define MAX_BOMB 10

enum ToolsKind {NONE,POP_ADD,SPEED_ADD,POWER_ADD,POWER_MAX,SPEED_MAX};

class Tools
{
public:
	Tools(void);
	Tools(HTEXTURE texTools,int nframes,float FPS,float x,float y,float w,float h);
	~Tools(void);
	void setTool(ToolsKind kind,int x,int y);
	void setTex(HTEXTURE texTools);
	void Render();
	void placeTool();//安放道具
	ToolsKind getToolsKind();//返回道具类型
	void updateTool(float fDeltaTime);
	void setPosition(int x,int y);		//设定道具坐标
	int getX();int getY();              //获取道具坐标

private:
	hgeAnimation* tool;
	int toolX;int toolY;//道具坐标xy
	ToolsKind toolskind;//道具种类
};

#endif