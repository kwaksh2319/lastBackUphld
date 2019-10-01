#include"stdafx.h"
#include"Marker.h"


Marker::Marker(wstring shaderFile, D3DXVECTOR2 position)
	:scale(1,1),position(position)
{
	wstring textureFile = Textures + L"bullet.png";
	clip = new Clip(PlayMode::Loop);
	clip->AddFrame(new Sprite(textureFile,shaderFile,37,1,55,18),0.3f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 117, 7, 55, 10), 0.3f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 37, 116, 53, 133), 0.3f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 204, 100, 220, 126), 0.3f);


	clip->Position(position);
	clip->Play();


}

Marker::~Marker()
{
	SAFE_DELETE(clip);

}

void Marker::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	

	clip->Position(position);
	clip->Update(V,P);
}

void Marker::Render()
{
	

	clip->Render();

	

}
