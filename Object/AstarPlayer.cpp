#include"stdafx.h"
#include"AstarPlayer.h"

AstarPlayer::AstarPlayer(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:position(position),moveSpeed(200.0f) ,focusOffset(180,140)//카메라 좌표

{
	animation = new Animation;
	wstring spriteFile = Textures + L"AStar/character.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	Clip* clip;
	//Left 0
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 25, 54, 39, 73), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 25, 79, 39, 97), 0.3f);
		animation->AddClip(clip);
	}

	//Right 1
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 74, 54, 90, 73), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 74, 79, 90, 97), 0.3f);
		animation->AddClip(clip);
	}

	//Up
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 48, 54, 65, 73), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 48, 79, 66, 97), 0.3f);
		animation->AddClip(clip);
	}

	//Down
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 54, 17, 73), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 79, 17, 97), 0.3f);
		animation->AddClip(clip);
	}

	animation->Position(position);
	animation->Scale(scale);
	animation->Play(0);
 
	animation->DrawBound(true);//box

}

AstarPlayer::~AstarPlayer()
{
	SAFE_DELETE(animation);
}

void AstarPlayer::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{

	//이동
	D3DXVECTOR2 position = animation->Position();
	D3DXVECTOR3 rotation = animation->RotationDegree();

	if (Key->Press('A')) {
		
		position.x -= moveSpeed * Time::Delta();
		animation->Position(position);
		
		
		animation->Play(0);

	}
	else if (Key->Press('D')) {
		
		position.x += moveSpeed * Time::Delta();
		animation->Position(position);
		
	
		animation->Play(1);
	
	}else if (Key->Press('W')) {

		position.y += moveSpeed * Time::Delta();
		animation->Position(position);
		

		animation->Play(2);

	}
	else if (Key->Press('S')) {

		position.y -= moveSpeed * Time::Delta();
		animation->Position(position);


		animation->Play(3);

	}
	animation->Position(position);
	animation->Update(V, P);
}

void AstarPlayer::Render()
{
	
	animation->Render();
}

void AstarPlayer::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{

	*position = animation->Position() + focusOffset;

	D3DXVECTOR2 textureSize = animation->TextureSize();
	D3DXVECTOR2 scale = animation->Scale();

	//(*size).x = textureSize.x*scale.x;

	//(*size).y = textureSize.y*scale.y;

	(*size) = D3DXVECTOR2(1, 1);

}

Sprite * AstarPlayer::GetSprite()
{
	return animation->GetSprite();
}
