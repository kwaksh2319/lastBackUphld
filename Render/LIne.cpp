#include "stdafx.h"
#include "Line.h"


Line::Line(D3DXVECTOR2 leftPoint, D3DXVECTOR2 rightPoint)
	: bDrawCollision(false), bVisivle(true),
	 _leftPoint(leftPoint), _rightPoint(rightPoint)
	, scale(1, 1), position(0,0)
{
	wstring shaderFile = Shaders + L"Bounding.fx";

	CreateBuffer(shaderFile, leftPoint, rightPoint);

	if (leftPoint.x > rightPoint.x)
	{
		this->_leftPoint = rightPoint;
		this->_rightPoint = leftPoint;
	}
	else
	{
		this->_leftPoint = leftPoint;
		this->_rightPoint = rightPoint;
	}

}

Line::~Line()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(vertexBuffer);
}

void Line::CreateBuffer(wstring shaderFile, D3DXVECTOR2 leftPoint, D3DXVECTOR2 rightPoint)
{
	shader = new Shader(shaderFile);

	vertices[0].Position = D3DXVECTOR3(leftPoint.x, leftPoint.y, 0);
	vertices[1].Position = D3DXVECTOR3(rightPoint.x, rightPoint.y, 0);

	//Create Vertex Buffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * 2;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
}


void Line::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);

	D3DXMATRIX W, S, T;
	D3DXMatrixScaling(&S, scale.x, scale.y, 1.0f);
	D3DXMatrixTranslation(&T, position.x, position.y, 0.0f);
	W = S * T;

	shader->AsMatrix("World")->SetMatrix(W);

	vertices[0].Position = D3DXVECTOR3(_leftPoint.x, _leftPoint.y, 0.0f);
	vertices[1].Position = D3DXVECTOR3(_rightPoint.x, _rightPoint.y, 0.0f);

	DeviceContext->UpdateSubresource
	(
		vertexBuffer, 0, NULL, vertices, sizeof(Vertex) * 2, 0
	);

}

void Line::Render()
{
	if (bVisivle == true)
	{
		UINT stride = sizeof(Vertex);
		UINT offset = 0;

		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

		shader->Draw(0, bDrawCollision ? 1 : 0, 2);
	}
}
