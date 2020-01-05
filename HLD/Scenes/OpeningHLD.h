#pragma once
#include"./Scenes/Scene.h"

class OpeningHLD :public Scene {

public:
	OpeningHLD(SceneValues * values);
	~OpeningHLD();


	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position();

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale();

	void Update() override;
	void Render() override;
	void GetStageState(bool val) { bCheckState = val; }
	bool NextStage() { return bNext; }
private:
	Animation*opening;
	
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	
	bool bCheckState;
	bool bNext;
	


};