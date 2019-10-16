#pragma once
#include"Scene.h"
class TitleScene :public Scene
{


private:
	

	Clip* sonic;
	Clip* tales;
	Sprite* sky;
	Sprite* island;
	Sprite* badge;

public:
	TitleScene(SceneValues* values);
	~TitleScene();


	void Update() override;
	void Render() override;

	



};
