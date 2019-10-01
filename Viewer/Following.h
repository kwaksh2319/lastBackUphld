#pragma once
#include"IFollow.h"
#include"Camera.h"
class Following :public Camera {

private:
	IFollowing* focus;

public:

	Following(IFollowing* focus=NULL);//NULL을 넣지않으면 터질위험이 크다.

	~Following();

	void Change(IFollowing* focus);//event appear move focus camera
	void Update() override;

};