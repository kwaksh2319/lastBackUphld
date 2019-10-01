#pragma once
#include"Camera.h"
class FreeCamera :public Camera {
private:
	float speed;//camera speed
private:
	void Move(D3DXVECTOR2 translation);

public:

	FreeCamera(float speed=200);
	~FreeCamera();
	void Position(float x, float y);
	void Position(D3DXVECTOR2 vec);

	void Update() override;


};