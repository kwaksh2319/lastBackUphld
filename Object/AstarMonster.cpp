#include"stdafx.h"
#include"AstarMonster.h"


AstarMonster::AstarMonster(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:position(position),scale(scale),bCollision(false),bMove(false)

{
	animation = new Animation;
	wstring spriteFile = Textures + L"./Astar/character.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	Clip*clip;
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 123, 1430, 142, 1447), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 123, 1460, 142, 1477), 0.3f);
		animation->AddClip(clip);
	}

	//Right 1
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 172, 1430, 191, 1447), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 172, 1460, 191, 1477), 0.3f);
		animation->AddClip(clip);
	}

	//Up
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 147, 1430, 166, 1447), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 147, 1460, 166, 1477), 0.3f);
		animation->AddClip(clip);
	}

	//Down
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 98, 1430, 117, 1447), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 98, 1460, 117, 1477), 0.3f);
		animation->AddClip(clip);
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);
	animation->DrawBound(true);
	
}

AstarMonster::~AstarMonster()
{
	SAFE_DELETE(animation);
}

void AstarMonster::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{

	//ÀÌµ¿
	
     bMove = false;
	

	if (Key->Down('J')) {
		bMove = true;
		position.x -= animation->TextureSize().x*scale.x;
		animation->Position(position);


		animation->Play(0);

	}
	else if (Key->Down('L')) {
		bMove = true;
		position.x += animation->TextureSize().x*scale.x;
		animation->Position(position);


		animation->Play(1);

	}
	else if (Key->Down('I')) {
		bMove = true;
		position.y += animation->TextureSize().y*scale.y;
		animation->Position(position);


		animation->Play(2);

	}
	else if (Key->Down('K')) {
		bMove = true;
		position.y -= animation->TextureSize().y*scale.y;
		animation->Position(position);


		animation->Play(3);

	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Update(V, P);
}

void AstarMonster::Render()
{
	
	animation->Render();
}


Sprite * AstarMonster::GetSprite()
{
	return animation->GetSprite();
}
