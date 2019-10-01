#pragma once
class Bullet
{
private:
	Clip* clip;
	D3DXVECTOR2 velocity;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;

public:
	Bullet(wstring shaderFile, D3DXVECTOR2 start, float angle, float speed);
	~Bullet();
	void Update(D3DXMATRIX & V, D3DXMATRIX & P);
	void Render();

	D3DXVECTOR2 postion() { return position; }
	Clip*GetClip() { return clip; }

};