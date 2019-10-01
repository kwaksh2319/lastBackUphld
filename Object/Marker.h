#pragma once
class Marker
{
private:
	Clip* clip;
	
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	
public:
	Marker(wstring shaderFile, D3DXVECTOR2 position);
	~Marker();
	void Update(D3DXMATRIX & V, D3DXMATRIX & P);
	void Render();

	D3DXVECTOR2 postion() { return position; }
	Clip*GetClip() { return clip; }

};