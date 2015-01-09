#ifndef _BOOM_H_
#define _BOOM_H_
#include <hge.h>
#include <hgefont.h>
#include <hgegui.h>
#include <hgeanim.h>

class Boom{
public:
	Boom();;
	Boom(HTEXTURE texPop,  int nframes,  float FPS,  float x,  float y,  float w,  float h);
	void setBoom(int x, int y, int L, int w);	
	void stopPopo();
	void stopPopoCen();
	void stopPopoDir();
	void Renderpopo();
	void RenderpopoCen();
	void RenderpopoDir();
	void setpopX(int x);		//设定泡泡的横坐标
	void setpopY(int y);		//设定泡泡的纵坐标
	void setboomLength(int L);	//设定爆炸长度的格子数
	void setWhose(int w);
	float getDelay();			//popo的爆炸延时
	int getpopX();
	int getpopY();
	int getboomLength();		//爆炸长度为几个格子
	int getWhose();
	void setDelay(float delay);
	//place the boom
	void placeBoom();		//安放泡泡
	void placeBoomCen();	//所安放的泡泡爆炸
	void placeBoomDir();	//所安放的泡泡在4个方向爆炸波及
	void setBoomExpT(int T);//设置爆炸过程动画延时
	int  getBoomExpT();		//爆炸过程动画延时
	int	 getBoomT();		//放置泡泡延时
	void setBoomT(int T);	//设置放置泡泡延时
	void updataPopo(float fDeltaTime);
	void updataPopoCen(float fDeltaTime);
	void updataPopoDir(float fDeltaTime);
	void setBoomExp(int up,int down,int left,int right);	//设定爆炸方向上波及的格子数
	void getBoomExp(int *L);;
	void boomExpDir(HTEXTURE texPopDir);	//创建爆炸动画
	void boomExpCen(HTEXTURE texPopCen,  int nframes,  float FPS,  float x,  float y,  float w,  float h);	//创建爆炸动画


	private:
	//pop
	hgeAnimation* popo;			//popo每一帧图片
	hgeAnimation* popoCen;		//popoCen每一帧图片
	hgeAnimation* popoDirUp[6];	//popoDir每一帧图片
	hgeAnimation* popoDirLeft[6];
	hgeAnimation* popoDirDown[6];
	hgeAnimation* popoDirRight[6];		
	int popX;                //pop的横向坐标位置
	int popY;				//pop的纵向坐标位置
	int boomLength;				//爆炸长度
	int tPlaceDelay,tExp;		//放置泡泡、爆炸延时
	int boomUp,boomDown,boomLeft,boomRight;	//爆炸波动中心的上下左右可炸格子数
	float popoPlaceTime, delay;	//popo的安放、爆炸时间
	int whose;                  //谁放置的炸弹
};



#endif