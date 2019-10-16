#pragma once
#include"./Viewer/IFollow.h"
class AstarPlayer: public IFollowing { //플레이어 어케스팅 가능

private:
	float moveSpeed;
	Animation* animation;
	D3DXVECTOR2 focusOffset;
	
	D3DXVECTOR2 position;

public:
	AstarPlayer(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~AstarPlayer();
	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();

	void Position(D3DXVECTOR2 vec) { position = vec; }
	D3DXVECTOR2 Position() { return position; }

	void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;
	Sprite* GetSprite();
};