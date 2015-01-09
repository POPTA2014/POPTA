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
	void setpopX(int x);		//�趨���ݵĺ�����
	void setpopY(int y);		//�趨���ݵ�������
	void setboomLength(int L);	//�趨��ը���ȵĸ�����
	void setWhose(int w);
	float getDelay();			//popo�ı�ը��ʱ
	int getpopX();
	int getpopY();
	int getboomLength();		//��ը����Ϊ��������
	int getWhose();
	void setDelay(float delay);
	//place the boom
	void placeBoom();		//��������
	void placeBoomCen();	//�����ŵ����ݱ�ը
	void placeBoomDir();	//�����ŵ�������4������ը����
	void setBoomExpT(int T);//���ñ�ը���̶�����ʱ
	int  getBoomExpT();		//��ը���̶�����ʱ
	int	 getBoomT();		//����������ʱ
	void setBoomT(int T);	//���÷���������ʱ
	void updataPopo(float fDeltaTime);
	void updataPopoCen(float fDeltaTime);
	void updataPopoDir(float fDeltaTime);
	void setBoomExp(int up,int down,int left,int right);	//�趨��ը�����ϲ����ĸ�����
	void getBoomExp(int *L);;
	void boomExpDir(HTEXTURE texPopDir);	//������ը����
	void boomExpCen(HTEXTURE texPopCen,  int nframes,  float FPS,  float x,  float y,  float w,  float h);	//������ը����


	private:
	//pop
	hgeAnimation* popo;			//popoÿһ֡ͼƬ
	hgeAnimation* popoCen;		//popoCenÿһ֡ͼƬ
	hgeAnimation* popoDirUp[6];	//popoDirÿһ֡ͼƬ
	hgeAnimation* popoDirLeft[6];
	hgeAnimation* popoDirDown[6];
	hgeAnimation* popoDirRight[6];		
	int popX;                //pop�ĺ�������λ��
	int popY;				//pop����������λ��
	int boomLength;				//��ը����
	int tPlaceDelay,tExp;		//�������ݡ���ը��ʱ
	int boomUp,boomDown,boomLeft,boomRight;	//��ը�������ĵ��������ҿ�ը������
	float popoPlaceTime, delay;	//popo�İ��š���ըʱ��
	int whose;                  //˭���õ�ը��
};



#endif