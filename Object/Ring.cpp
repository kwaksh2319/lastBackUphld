#include"stdafx.h"
#include"Ring.h"

Ring::Ring(D3DXVECTOR2 position)
	:bCollision(false),bAlive(false),bVisible(true),position(position)
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
	ring->Scale(0.5f, 0.5f);
	ring->Play(0);
	
}

Ring::~Ring()
{
	SAFE_DELETE(ring);
}

void Ring::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	//player 일정 범위에 있을때 update
	if (bVisible == false)
		   return;
	if (ring->GetCurrentClip() == 1 && ring->GetClip()->EndFrame())
		bAlive = false;
	
	if (bCollision == true)
		ring->Play(1);
	
	ring->DrawBound(true);
	ring->GetSprite()->DrawCollision(bCollision);

	
	ring->Position(position);
	ring->Update(V, P);
}

void Ring::Render()
{
	if (bVisible == false)
		return;

	ring->Render();
}

Sprite * Ring::GetSprite()
{
	return ring->GetSprite();
}
