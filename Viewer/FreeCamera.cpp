#include"stdafx.h"
#include"FreeCamera.h"



FreeCamera::FreeCamera(float speed)
	:speed(speed)
{

}

FreeCamera::~FreeCamera()
{


}

void FreeCamera::Move(D3DXVECTOR2 translation)
{
	position += translation * Time::Delta();

}

void FreeCamera::Position(float x, float y)
{
	Position(D3DXVECTOR2(x, y));
}

void FreeCamera::Position(D3DXVECTOR2 vec)
{
	position = vec;

}


void FreeCamera::Update()
{
	if (Key->Press(VK_LEFT))
		Move(D3DXVECTOR2(-1, 0)*speed);

	else if(Key->Press(VK_RIGHT))
		Move(D3DXVECTOR2(1, 0)*speed);

	else if (Key->Press(VK_UP))
		Move(D3DXVECTOR2(0, 1)*speed);

	else if (Key->Press(VK_DOWN))
		Move(D3DXVECTOR2(0, -1)*speed);

	__super::Update();//부모 업데이트로 

}
