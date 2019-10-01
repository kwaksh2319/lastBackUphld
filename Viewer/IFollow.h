#pragma once
#include"stdafx.h"
class IFollowing { //추상클래스 

public:
	virtual void Focus(D3DXVECTOR2* position, D3DXVECTOR2*size) = 0;
};