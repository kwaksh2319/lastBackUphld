#pragma once
#include"Scene.h"
class Astar :public Scene
{


private:
	/*이미지 버튼*/
	
	Sprite*background;
	class AstarPlayer* player;
	class AstarMonster* monster;

	Sprite*playerRect;
	Sprite*monsterRect;

	 class Node* node;
	D3DXVECTOR2 massSize;

	D3DXVECTOR2 mouse;
	D3DXVECTOR2 cameraPos;
	D3DXVECTOR2 position;
	
	bool bMove;



public:
	Astar(SceneValues* values);
	~Astar();


	void Update() override;
	void Render() override;

	



};
