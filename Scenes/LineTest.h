#pragma once
#include "Scene.h"

class LineTest : public Scene
{
private:
	vector<class Line*> lines;
	vector<pair<D3DXVECTOR2, D3DXVECTOR2>> linePoints;

	Sprite* background;

	D3DXVECTOR2 mouse;
	D3DXVECTOR2 cameraPos;
	D3DXVECTOR2 position; //최종 마우스 포지션(WinAPI -> DX)

	D3DXVECTOR2 lastPosition;

private:
	void EditLine();
	void RenderImGui();

public:
	LineTest(SceneValues* values);
	~LineTest();

	void Update() override;
	void Render() override;

};