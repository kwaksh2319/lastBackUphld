#pragma once

class Line
{
private:
	Shader * shader;
	ID3D11Buffer* vertexBuffer;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	D3DXVECTOR2 _leftPoint;
	D3DXVECTOR2 _rightPoint;

	float slope;

private:
	bool bDrawCollision;
	bool bVisivle;

private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
	};
	Vertex vertices[2];

private:
	void CreateBuffer(wstring shaderFile, D3DXVECTOR2 leftPoint, D3DXVECTOR2 rightPoint);

public:
	Line(D3DXVECTOR2 leftPoint, D3DXVECTOR2 rightPoint);
	~Line();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

public:
	void LeftPoint(D3DXVECTOR2& val) { _leftPoint = val; }
	void RightPoint(D3DXVECTOR2 val) { _rightPoint = val; }
	D3DXVECTOR2 LeftPoint() { return _leftPoint; }
	D3DXVECTOR2 RightPoint() { return _rightPoint; }
	float Slope() { return slope; }

	void DrawCollision(bool val) { bDrawCollision = val; }
	void Visible(bool val) { bVisivle = val; }
};
