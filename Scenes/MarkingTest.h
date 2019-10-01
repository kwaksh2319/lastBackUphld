#pragma once
#include"Scene.h"
class MarkingTest :public Scene
{


private:
	

	Sprite* background;
	SoundManager* soundManger;

	class Player* player;
	vector<class Marker*> markers;
private :
   void	RenderBackground();
   void OpenComplete(wstring fileName);
   void SaveComplete(wstring fileName);

public:
	MarkingTest(SceneValues* values);
	~MarkingTest();


	void Update() override;
	void Render() override;

	class Player* GetPlayer();



};
