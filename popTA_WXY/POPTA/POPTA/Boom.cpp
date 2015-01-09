#include "Boom.h"
//#include "Game.h"

Boom::Boom(HTEXTURE texPop,  int nframes,  float FPS,  float x,  float y,  float w,  float h){	//创建泡泡动画
	popo = new hgeAnimation(texPop, nframes, FPS, x, y, w, h);
}

Boom::Boom()
{

}

void Boom::setBoom(int x, int y, int L, int w)
{
	setpopX(x);
	setpopY(y);
	setboomLength(L);
	setWhose(w);
	setBoomExp(L,L,L,L);
}

//place the boom
void Boom::Renderpopo(){		//渲染泡泡
	popo->Render(popX,popY);
}

void Boom::RenderpopoCen(){		//渲染泡泡
	popoCen->Render(popX,popY);
}

void Boom::RenderpopoDir(){		//渲染泡泡
	popoDirUp[min(boomUp,boomLength)]->Render(popX,popY-200);
	popoDirLeft[min(boomLeft,boomLength)]->Render(popX-200,popY);
	popoDirDown[min(boomDown,boomLength)]->Render(popX,popY+40);
	popoDirRight[min(boomRight,boomLength)]->Render(popX+40,popY);
}

void Boom::placeBoom(){			//放置泡泡动作
	popo->Play();
		//popoDir->Play();
}

void Boom::placeBoomCen(){
	popoCen->Play();
}

void Boom::placeBoomDir(){
	popoDirUp[min(boomUp,boomLength)]->Play();
	popoDirLeft[min(boomLeft,boomLength)]->Play();
	popoDirDown[min(boomDown,boomLength)]->Play();
	popoDirRight[min(boomRight,boomLength)]->Play();
}

void Boom::updataPopo(float fDeltaTime){
	popo->Update(fDeltaTime);
}

void Boom::updataPopoCen(float fDeltaTime){
	popoCen->Update(fDeltaTime);
}

void Boom::updataPopoDir(float fDeltaTime){
	popoDirUp[min(boomUp,boomLength)]->Update(fDeltaTime);
	popoDirLeft[min(boomLeft,boomLength)]->Update(fDeltaTime);
	popoDirDown[min(boomDown,boomLength)]->Update(fDeltaTime);
	popoDirRight[min(boomRight,boomLength)]->Update(fDeltaTime);
}

void Boom::stopPopo(){
	popo->Stop();
}

void Boom::stopPopoCen(){
	popoCen->Stop();
}

void Boom::stopPopoDir(){
	popoDirUp[min(boomUp,boomLength)]->Stop();
	popoDirLeft[min(boomLeft,boomLength)]->Stop();
	popoDirDown[min(boomDown,boomLength)]->Stop();
	popoDirRight[min(boomRight,boomLength)]->Stop();
}

void Boom::setpopX(int x){
	popX = x;
}

void Boom::setpopY(int y){
	popY = y;
}

void Boom::setboomLength(int L){
	boomLength = L;
}

void Boom::setWhose(int w){
	whose = w;
}

int Boom::getboomLength(){
	return boomLength;
}

int Boom::getpopX(){
	return popX;
}

int Boom::getpopY(){
	return popY;
}

float Boom::getDelay(){			//popo的爆炸延时
	return delay;
}

int Boom::getWhose(){
	return whose;
}

void Boom::setDelay(float newdelay){
	delay = newdelay;
}

void Boom::setBoomExpT(int T){
	tExp=T;	
}

int Boom::getBoomExpT(){
	return tExp;
}

int	Boom::getBoomT(){
	return tPlaceDelay;	
}

void Boom::setBoomT(int T){
	tPlaceDelay=T;
}



void Boom::setBoomExp(int up,int down,int left,int right){	//爆炸方向上的限值
	boomUp=up;		boomDown=down;
	boomLeft=left;	boomRight=right;
}

void Boom::boomExpDir(HTEXTURE texPopDir){	//创建爆炸动画
	popoDirUp[0] = new hgeAnimation(texPopDir,3, 8, 0, 0, 40, 40);
	popoDirLeft[0] = new hgeAnimation(texPopDir,3, 8, 0, 0, 40, 40);
	popoDirDown[0] = new hgeAnimation(texPopDir,3, 8, 0, 0, 40, 40);
	popoDirRight[0] = new hgeAnimation(texPopDir,3, 8, 0, 0, 40, 40);
	for(int i=1;i<6;i++){
		popoDirUp[i] = new hgeAnimation(texPopDir,3, 8, (i-1)*120, 0, 40, 200);
		popoDirLeft[i] = new hgeAnimation(texPopDir,3, 8, 0, 400+40*(i-1), 200, 40);
		popoDirDown[i] = new hgeAnimation(texPopDir,3, 8,(i-1)*120, 200, 40, 200);
		popoDirRight[i] = new hgeAnimation(texPopDir,3, 8, 0, 600+40*(i-1), 200, 40);
	}
}

void Boom::boomExpCen(HTEXTURE texPopCen,  int nframes,  float FPS,  float x,  float y,  float w,  float h){	//创建爆炸动画
	popoCen = new hgeAnimation(texPopCen, nframes, FPS, x, y, w, h);
}