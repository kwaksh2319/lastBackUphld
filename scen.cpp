#include"stdafx.h"
#include"Device.h"

ID3D11Buffer* vertexBuffer;

ID3D11InputLayout* inputLayout;

D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
	{
	"POSITION",
	0,
	DXGI_FORMAT_R32G32B32_FLOAT,
	0,
	0,
	D3D11_INPUT_PER_VERTEX_DATA,
	0
	},
     {//Size 
    "COLOR",
	  0,
	   DXGI_FORMAT_R32G32B32_FLOAT,
	   0,
	   12,  
	   D3D11_INPUT_PER_VERTEX_DATA,
	   0

      }
};

struct Vertex {
	D3DXVECTOR3 Position;
	D3DXCOLOR Color;

};
//star draw verices
Vertex vertices[6];
void InitScene() {
	//Vertex position setting
	
	
	//Vertex vertices[6];

	vertices[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(0.0f, +0.5f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.5f, 0.0f, 0.0f);

	vertices[3].Position = D3DXVECTOR3(+0.5f, 0.0f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(0.0f, +0.5f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.5f, +0.5f, 0.0f);
	
	//cube draw verices
	//Vertex vertices[17];
	
	//color setting star
	vertices[0].Color = D3DXCOLOR(1, 0, 0, 1);
	vertices[1].Color = D3DXCOLOR(0, 1, 0, 1);
	vertices[2].Color = D3DXCOLOR(1, 0, 0, 1);

	vertices[3].Color = D3DXCOLOR(0, 0, 1, 1);
	vertices[4].Color = D3DXCOLOR(0, 1, 0, 1);
	vertices[5].Color = D3DXCOLOR(1, 0, 0, 1);
	
	
	
	//create vertexBuffer
	{   //buffer size
		D3D11_BUFFER_DESC desc;
		ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		desc.Usage = D3D11_USAGE_DEFAULT;
		
		desc.ByteWidth = sizeof(Vertex) * 6;//draw star
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//용도
		
       //data vertices 
		
		D3D11_SUBRESOURCE_DATA data;
		ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		data.pSysMem = vertices;
		
		HRESULT hr =Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
		
	
	}
	//create layout
	{
		HRESULT hr = Device->CreateInputLayout(
			layoutDesc,
			ARRAYSIZE(layoutDesc),
			VsBlob->GetBufferPointer(),
			VsBlob->GetBufferSize(),
			&inputLayout
		);

		assert(SUCCEEDED(hr));
		

	}

}

void DestoryScene() {
	inputLayout->Release();
	vertexBuffer->Release();

	
}

void Update() {
	if (key->Press('A') == true)
		vertices[0].Position.x -= 0.001f;
	else if (key->Press('D') == true)
		vertices[0].Position.x += 0.001f;
	else if (key->Press('W') == true)
		vertices[0].Position.y += 0.001f;
	else if (key->Press('S') == true)
		vertices[0].Position.y -= 0.001f;

	
	DeviceContext->UpdateSubresource(
	   vertexBuffer,0,NULL,vertices,sizeof(Vertex)*6,0
	);
}

void Render() {

	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	//function 
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{//draw 

		UINT stride = sizeof(Vertex);//
		UINT offset = 0;
		DeviceContext->IASetVertexBuffers(0,1,&vertexBuffer,&stride,&offset);
		//DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);//정점 연결을 어떻게 그릴래
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DeviceContext->IASetInputLayout(inputLayout);
		//DeviceContext->Draw(17, 0);//갯수 draw cube
		
		DeviceContext->Draw(6, 0);//갯수 draw star
		
	}
	SwapChain->Present(0, 0);

}