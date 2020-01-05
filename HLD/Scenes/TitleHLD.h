#pragma once
#include"./Scenes/Scene.h"
enum class TitlState {
	Appear, Idle
};
class TitleHLD :public Scene {

public:
	TitleHLD(SceneValues * values);
	~TitleHLD();


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
	Animation*title;
	Rect* rectSelect;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	TitlState state;
	bool bCheckState;
	bool bNext;
	bool bCheckSelect;


};