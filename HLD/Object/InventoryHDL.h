#pragma once
#include"HLD/Object/HLDPlayer.h"
class InventoryHDL : HLDPlayer {

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	bool bCheck;
	Rect*inventory[4][3];
	
	vector<class Sprite*> itemMoney;
public:
	InventoryHDL(D3DXVECTOR2 pos, D3DXVECTOR2 size);
	~InventoryHDL();
	
	
	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }

	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();

	void SetSprite(Sprite * data);



};