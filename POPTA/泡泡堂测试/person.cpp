#include "person.h"


person::person(void)
{
}


person::~person(void)
{
	for(int i = 0; i < 4; i++)
		if(!dir_image[i])
			delete dir_image[i];
}


person::person(HTEXTURE tex, int nframes, float FPS, float w, float h){
	person_direction = DOWN;
	for(int i = 0; i < 4; i++)
		dir_image[i] = new hgeAnimation(tex, nframes, FPS, 0, i * h, w, h);
}

void person::Walk(int direction){
	if(person_direction == direction){

	}else{

	};
}

void person::setDirection(DIRECTION direction){
	if (person_direction != direction)
	{
		dir_image[person_direction]->Stop();
		person_direction = direction;
		dir_image[person_direction]->Play();
	}
}

void person::Update(float fDeltaTime, DIRECTION direction){
	if(direction == person_direction || direction == NO)
		dir_image[person_direction]->Update(fDeltaTime);
	else
		setDirection(direction);
}

void person::Render(float x, float y){
	if(x == -1 || y == -1)
		dir_image[person_direction]->Render(pX, pY);
	else{
		pX = x;
		pY = y;
		dir_image[person_direction]->Render(pX, pY);
	}
}

//place the boom

void person::placeBoom(hgeAnimation	*placeBoom, float fDeltaTime){ 
	placeBoom->Play();
	placeBoom->Update(fDeltaTime);
}

void person::Stop(){
	dir_image[person_direction]->Stop();
}

void person::Play(){
	dir_image[person_direction]->Play();
}

void person::Play(DIRECTION direction){
	person_direction = direction;
	dir_image[person_direction]->Play();
}

void person::Move(float speed, float fDeltaTime){
	switch(person_direction){
	case LEFT:
		pX -= speed * fDeltaTime;
		break;
	case DOWN:
		pY += speed * fDeltaTime;
		break;
	case RIGHT:
		pX += speed * fDeltaTime;
		break;
	case UP:
		pY -= speed * fDeltaTime;
		break;
	default:
		break;
	}
}

void person::setX(int x){
	pX = x;
}

void person::setY(int y){
	pY = y;
}

void person::set_person_state(PERSON_STATE _person_state){
	person_state = _person_state;
}

int person::getX(){
	return pX;
}

int person::getY(){
	return pY;
};

PERSON_STATE person::get_person_state(){
	return person_state;
}

DIRECTION person::getDirection(){
	return person_direction;
}
