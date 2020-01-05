#include"stdafx.h"
#include"HLDgrid.h"


HLDgrid::HLDgrid(wstring shaderFile)
	:position(0, 0), scale(1, 1), color(1, 0, 1, 1)
{



	CreateBuffer(shaderFile);

	Color(color);
}


HLDgrid::HLDgrid(wstring shaderFile, D3DXVECTOR2 position, D3DXVECTOR2 scale, D3DXCOLOR color)
	: position(position), scale(scale), color(color)
{


	CreateBuffer(shaderFile);

	Color(color);
}

HLDgrid::~HLDgrid()
{
	SAFE_DELETE(shader);
	SAFE_RELEASE(vertexBuffer);
}

void HLDgrid::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	/*
	D3DXMATRIX W;
	D3DXMATRIX S, T;



	D3DXMatrixScaling(&S, scale.x, scale.y, 1.0f);
	D3DXMatrixTranslation(&T, position.x, position.y, 0.0f);
	W = S * T;
	*/
	
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);

	
	//shader->AsVector("Color")->SetFloatVector(color);
	

}

void HLDgrid::Render()
{
	UINT stride = sizeof(Vertex); //����
	UINT offset = 0; //������
	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	DeviceContext->IASetIndexBuffer(indexBuffer, DXGI_FORMAT_R32_UINT, 0); //Todo 08. �ε��� ���� ���
	{
		D3DXMATRIX W;
		D3DXMATRIX S, T;



		D3DXMatrixScaling(&S, scale.x, scale.y, 1.0f);
		D3DXMatrixTranslation(&T, position.x, position.y, 0.0f);

		W = S * T;
		shader->AsMatrix("World")->SetMatrix(W);
		shader->AsVector("Color")->SetFloatVector(color);
		shader->DrawIndexed(0, 0, indexCount);

	}
	ImGui::SliderFloat("Gridpositionx", (float*)&position.x , -1000.0, 1000.0);
	ImGui::SliderFloat("Gridpositiony", (float*)&position.y, -1000.0, 1000.0);
	ImGui::SliderFloat("Gridscalex", (float*)&scale.x, -1000.0, 1000.0);
	ImGui::SliderFloat("Gridscaley", (float*)&scale.y, -1000.0, 1000.0);
	//shader->Draw(0, 0, 6);

	
}



void HLDgrid::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	//D3DXVECTOR2 input = {x, y};
	Position(input);
}

void HLDgrid::Position(D3DXVECTOR2& vec)
{
	position = vec;

}

void HLDgrid::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDgrid::Scale(D3DXVECTOR2 & vec)
{
	scale = vec;

}

void HLDgrid::Color(float r, float g, float b)
{
	D3DXCOLOR input = D3DXCOLOR(r, g, b, 0.5f);
	Color(input);
}

void HLDgrid::Color(D3DXCOLOR & vec)
{
	color = vec;
	shader->AsVector("Color")->SetFloatVector(color);
}

bool HLDgrid::PtInRect(const HLDgrid * rect, D3DXVECTOR2 ptMouse)
{
	float xScale = rect->scale.x*0.5f;
	float yScale = rect->scale.y*0.5f;

	float left = rect->position.x - xScale;
	float right = rect->position.x + xScale;
	float bottom = rect->position.y - yScale;
	float top = rect->position.y + yScale;

	bool bCheck = true;

	bCheck &= ptMouse.x > left;
	bCheck &= ptMouse.x < right;
	bCheck &= ptMouse.y > bottom;
	bCheck &= ptMouse.y < top;

	return bCheck;
}



D3DXVECTOR2 HLDgrid::TransGetPosition(D3DXVECTOR2 pos)
{
	UINT indexX[4];
	float x = pos.x+ WidthNode/2;
	float z = pos.y+ HeightNode/2;
	indexX[0] = WidthNode * z + x;
	indexX[1] = WidthNode * (z + 1) + x;
	indexX[2] = WidthNode * z + x + 1;
	indexX[3] = WidthNode * (z + 1) + x + 1;
	UINT indexY[4];

	indexY[0] =HeightNode * z + x;
	indexY[1] = HeightNode * (z + 1) + x;
	indexY[2] = HeightNode * z + x + 1;
	indexY[3] = HeightNode * (z + 1) + x + 1;
	D3DXVECTOR2 v[4];
	for (int i = 0; i < 4; i++) {
		v[i].x = vertices[indexX[i]].Position.x;
		v[i].y = vertices[indexY[i]].Position.y;
	//	v[i].z = vertices[index[i]].Position.z;
	}
	return v[0];
}
void HLDgrid::CreateBuffer(wstring shaderFile)
{
	shader = new Shader(shaderFile);
	vertexCount = (width + 1) * (height + 1);
	vertices = new Vertex[vertexCount];
	
	for (UINT z = 0; z <= height; z++)
	{
		for (UINT x = 0; x <= width; x++)
		{
			UINT index = (width + 1) * z + x; //�� rect�� [0] ���ϱ�

			vertices[index].Position.x = (float)x;
			vertices[index].Position.y = (float)z;
			vertices[index].Position.z = 0.0f;

			//Todo 07. y�� 0����, z�� ������ �׸��� -> ����(�ϰ͵� �ȳ���) -> ī�޶� y�� ����������
			//vertices[index].Position.x = (float)x;
			//vertices[index].Position.y = 0.0f;
			//vertices[index].Position.z = (float)z;
		}
	}
	
	//Create VertexBerffer
	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		//	desc.Usage = D3D11_USAGE_DEFAULT;
		desc.ByteWidth = sizeof(Vertex) * vertexCount;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = vertices;
		//D3D11_SUBRESOURCE_DATA data;
		//ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));

		//���̴��� �ѱ�鼭 �� ��������. ������ ���������� �Ҹ�Ǿ �������
		subResource.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &subResource, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}
	
	indexCount = width * height * 6; //��ü �ε��� ���� -> �׸��� ��ĭ�� �ε����� 6�� (ĭ�� * 6��)
	indices = new UINT[indexCount];

	UINT index = 0;
	for (UINT z = 0; z < height; z++) //ĭ���ϱ� �۰ų� ����x, ����������o(0, 1, 2..�ε���)
	{
		for (UINT x = 0; x < width; x++)
		{
			indices[index + 0] = (width + 1) * z + x; //0 (�� ĭ�� ���ϴ� == �ε��� ��ȣ�� ����)
			indices[index + 1] = (width + 1) * (z + 1) + x; //4 (0�� ������ �ٷ� ��ĭ)
			indices[index + 2] = (width + 1) * z + (x + 1); //1
			indices[index + 3] = (width + 1) * z + (x + 1); //1
			indices[index + 4] = (width + 1) * (z + 1) + x; //4
			indices[index + 5] = (width + 1) * (z + 1) + (x + 1); //5 (�������� �� �� 1�� ���ϸ� ��)

			index += 6; //6���� �����ؼ� indices �迭�� ����
		}
	}
	


	{
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.ByteWidth = sizeof(UINT)* indexCount; //*400
		desc.BindFlags = D3D11_BIND_INDEX_BUFFER; //
		D3D11_SUBRESOURCE_DATA subResource = { 0 };
		subResource.pSysMem = indices; //
		HRESULT hr = Device->CreateBuffer(&desc, &subResource, &indexBuffer);
		assert(SUCCEEDED(hr));

	}

}

