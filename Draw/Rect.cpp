#include"stdafx.h"
#include"Rect.h"



Rect::Rect(wstring shaderFile)
	:position(0,0),scale(1,1),color(1,1,1,1)//world position
{
	CreateBuffer(shaderFile);
}

Rect::Rect(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color)
	: position(position),scale(scale),color(color)
{
	CreateBuffer(shaderFile);
}

Rect::~Rect()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(vertexBuffer);
}

void Rect::Update()
{
	D3DXMATRIX W;
	D3DXMATRIX S,T;
	D3DXMatrixScaling(&S, scale.x, scale.y, 1.0f);
	D3DXMatrixTranslation(&T, position.x, position.y, 0.0f);
	W = S * T;
	shader->AsMatrix("World")->SetMatrix(W);


}

void Rect::Render()
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	shader->Draw(0, 0, 6);

}

void Rect::ViewProjection(D3DXMATRIX& V, D3DXMATRIX& P)
{
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);
}

void Rect::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y); //overloading posiiton 
	//D3DXVECTOR2 input ={x,y};
	Position(input);
}

void Rect::Position(D3DXVECTOR2& vec)
{
	position = vec; //world position
}

void Rect::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y); //overloading Scale
	Scale(input);
}

void Rect::Scale(D3DXVECTOR2 & vec)
{
}
void Rect::CreateBuffer(wstring shaderFile)
{
	shader = new Shader(shaderFile);

	Vertex vertices[6];
	vertices[0].Position = D3DXVECTOR3(-0.5f, -0.5f, 0.0f);//verex position
	vertices[1].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[3].Position = D3DXVECTOR3(0.5f, -0.5f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(-0.5f, 0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(0.5f, 0.5f, 0.0f);

	//create vertexBuffer

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;

	desc.ByteWidth = sizeof(Vertex) * 6;//draw star
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//¿ëµµ

   //data vertices 

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices; //buffer input to vertices

	HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
	assert(SUCCEEDED(hr));
}