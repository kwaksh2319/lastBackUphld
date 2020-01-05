#pragma once

#define WidthNode 16
#define HeightNode 25
class HLDgrid
{
private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXCOLOR color;

private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
		D3DXCOLOR Color;
	};

private:
	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	UINT width = 862;
	UINT height = 960; //���� -> �ڰ� �߷��� �Ⱥ��� -> ���� ����

	//Todo 02. �ε��� ������, ���� ����
	
	UINT vertexCount;
	Vertex* vertices;
	UINT indexCount;
	UINT *indices;
	ID3D11Buffer* indexBuffer;

private:
	void CreateBuffer(wstring shaderFile);


public:
	HLDgrid(wstring shaderFile);
	HLDgrid(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color = D3DXCOLOR(0xff555566));// 
	~HLDgrid();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P); //overide
	void Render();



public:
	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() { return scale; }

	void Color(float r, float g, float b);
	void Color(D3DXCOLOR& vec);
	D3DXCOLOR Color() { return color; }

	static bool PtInRect(const HLDgrid* rect, D3DXVECTOR2 ptMouse);
	D3DXVECTOR2 TransGetPosition(D3DXVECTOR2 pos);
	
	
};