#include"stdafx.h"
#include"Ring.h"

Ring::Ring(D3DXVECTOR2 position)
	:bCollision(false),bAlive(false),bVisible(true)
{
	wstring textureFile = Textures + L"Sonic/ring.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	ring = new Animation;
	Clip*clip;
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 263, 0, 313, 60), 0.2f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 143, 68, 176, 123), 0.2f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 406, 68, 426, 123), 0.2f);
		ring->AddClip(clip);
	}
		//Destroy
	{
		clip = new Clip(PlayMode::Reverse);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 263, 0, 313, 60), 0.2f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 143, 68, 176, 123), 0.2f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 406, 68, 426, 123), 0.2f);
		ring->AddClip(clip);
	}
}

Ring::~Ring()
{
}

void Ring::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
}

void Ring::Render()
{
}

Sprite * Ring::GetSprite()
{
	return nullptr;
}
