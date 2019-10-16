#pragma once
#include "Scene.h"

class Sonic : public Scene
{
private:
	vector<class Line*> lines;
	vector<pair<D3DXVECTOR2, D3DXVECTOR2>> linePoints;

	vector<class Ring*> rings;
	vector<D3DXVECTOR2> ringPoints;

	vector<class Fish*> fishes;
	vector<D3DXVECTOR2> fishPoints;

	Sprite* background;
	class SonicPlayer* player;

	bool lineVisible;
	float slope;


public:
	Sonic(SceneValues* values);
	~Sonic();

	void Update() override;
	void Render() override;

};