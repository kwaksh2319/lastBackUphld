#include "stdafx.h"
#include "Rect.h"

Rect::Rect(wstring shaderFile)
	:position(0, 0), scale(1, 1), color(0, 0, 0, 1)
{
	CreateBuffer(shaderFile);
	UpdateWorld();
	Color(color);
}


Rect::Rect(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color)
	: position(position), scale(scale), color(color)
{
	CreateBuffer(shaderFile);
	UpdateWorld();
	Color(color);
}

Rect::~Rect()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(vertexBuffer);
}

void Rect::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);

}

void Rect::Render()
{
	UINT stride = sizeof(Vertex); //보폭
	UINT offset = 0; //시작점

	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);

	shader->Draw(0, 0, 6);
}



void Rect::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	//D3DXVECTOR2 input = {x, y};
	Position(input);
}

void Rect::Position(D3DXVECTOR2& vec)
{
	position = vec;
	UpdateWorld();
}

void Rect::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void Rect::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;
	UpdateWorld();
}

void Rect::Color(float r, float g, float b)
{
	D3DXCOLOR input = D3DXCOLOR(r, g, b, 1);
	Color(input);
}

void Rect::Color(D3DXCOLOR & vec)
{
	color = vec;
	shader->AsVector("Color")->SetFloatVector(color);
}


void Rect::CreateBuffer(wstring shaderFile)
{
	shader = new Shader(shaderFile);

	Vertex vertices[6];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);

	//Create VertexBerffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 6;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		//쉐이더로 넘기면서 값 복사해줌. 원본은 지역변수로 소멸되어도 상관없음
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

}

void Rect::UpdateWorld()
{
	D3DXMATRIX W;
	D3DXMATRIX S, T;

	D3DXMatrixScaling(&S, scale.x, scale.y, 1.0f);
	D3DXMatrixTranslation(&T, position.x, position.y, 0.0f);

	W = S * T;

	shader->AsMatrix("World")->SetMatrix(W);
}
