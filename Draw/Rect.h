#pragma once
class Rect {
private:
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXCOLOR color;
private:
	struct Vertex {
		D3DXVECTOR3 Position;
		D3DXCOLOR Color;

	};
private:
	Shader* shader; //class Shader* shader;
	ID3D11Buffer* vertexBuffer;
private:
	void CreateBuffer(wstring shaderFile);

public:
	Rect(wstring shaderFile);
	Rect(wstring shaderFile,D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color=D3DXCOLOR(1,1,1,1));//overloading
	~Rect();
	void Update();
	void Render();
	void ViewProjection(D3DXMATRIX& V, D3DXMATRIX& P);
public : 
	//position
	void Position(float x, float y);//overloading
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() { return position; }

	//scale
	void Scale(float x, float y);//overloading
	void Scale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() { return scale; }


};