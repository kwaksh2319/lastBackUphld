#pragma once

class AstarMonster { //플레이어 어케스팅 가능

private:
	
	Animation* animation;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;


	bool bCollision;
	bool bMove;



public:
	AstarMonster(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~AstarMonster();
	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();
	void Position(D3DXVECTOR2 vec) {position = vec;}
	D3DXVECTOR2 Position() { return position; }

	void Scale(D3DXVECTOR2 vec) { scale = vec; }
	D3DXVECTOR2 Scale() { return scale; }

	void Collision(bool val) { bCollision = val; }
	bool Collision() { return bCollision; }
	
	void Move(bool val) { bMove = val; }
	bool Move() { return bMove; }
;
	Sprite* GetSprite();
};