#pragma once
class HLDCrystal {

private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 playerPos;
	D3DXVECTOR2 scale;
	bool bCheck;
	bool bCheckRange;
	bool bCheckMoney;
	float hitCount;
	float moveSpeed;
	Sprite*crystal;
	Sprite*crystalMoney;

public:

	HLDCrystal(D3DXVECTOR2 pos);
	~HLDCrystal();

	void Position(float x, float y);
	void Position(D3DXVECTOR2 val);
	D3DXVECTOR2 Position() { return position; }



	void Scale(float x, float y);
	void Scale(D3DXVECTOR2 val);
	D3DXVECTOR2 Scale() { return scale; }
	
	void GetMoneyCollision(bool val);
	void GetCollision(bool val);
	void SearchRange(bool val);
	void GetPlayerPoint(D3DXVECTOR2 pos);

	void Update(D3DXMATRIX &V, D3DXMATRIX &P);
	void Render();
	Sprite*GetSprite();
	Sprite*GetSpriteMoney();








};