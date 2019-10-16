#include"stdafx.h"
#include"Fish.h"

#define MAX_LIMIT_Y 150.0f
#define SPEED 0.1f

Fish::Fish(D3DXVECTOR2 position)
	:bCollision(false), bAlive(false), bVisible(true), speed(SPEED),start(position), position(position)
{
	wstring textureFile = Textures + L"./Sonic/enemies.png";
	wstring shaderFile = Shaders + L"Effect.fx";

	fish = new Animation;
	Clip*clip;
    //UP
	{

		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 281, 315, 316, 350), 0.2f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 322, 315, 357, 350), 0.2f);
		fish->AddClip(clip);
	}
	// Down
	{

		clip = new Clip(PlayMode::Reverse);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 281, 315, 316, 350), 0.2f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 322, 315, 357, 350), 0.2f);
		fish->AddClip(clip);
	}
	fish->Play(0);

}

Fish::~Fish()
{
	SAFE_DELETE(fish);
}

void Fish::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	position.y += speed;
	if (position.y > start.y + MAX_LIMIT_Y) {
		speed = -SPEED* 0.75f;
		fish->Play(0);
	}
	else if (position.y<start.y){
		speed = SPEED;
		fish-> Play(1);

	}
	fish->Position(position);
	fish->Update(V, P);

}

void Fish::Render()
{
	fish->Render();
}

Sprite * Fish::GetSprite()
{
	return fish->GetSprite();
}
