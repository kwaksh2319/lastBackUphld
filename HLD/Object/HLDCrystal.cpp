#include"stdafx.h"
#include"HLDCrystal.h"

HLDCrystal::HLDCrystal(D3DXVECTOR2 pos)
	:bCheck(false),bCheckRange(false),moveSpeed(400.0f), hitCount(0.0f),bCheckMoney(false)
{
	wstring textureFile = Textures + L"./HDL/HyperLightDrifter_sprite.png";
	wstring shaderFile = Shaders + L"Effect.fx";

	crystal = new Sprite(textureFile,shaderFile, 925, 0, 1005, 105);
	crystalMoney = new Sprite(textureFile, shaderFile,1010,1065,1020,1085);
	scale = D3DXVECTOR2(1.0f, 1.0f);
	position = pos;
	//crystal->DrawBound(true);

}

HLDCrystal::~HLDCrystal()
{
	SAFE_DELETE(crystalMoney);
	SAFE_DELETE(crystal);

}

void HLDCrystal::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void HLDCrystal::Position(D3DXVECTOR2 val)
{

	position = val;
}

void HLDCrystal::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void HLDCrystal::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

void HLDCrystal::GetMoneyCollision(bool val)
{
	bCheckMoney = val;
}

void HLDCrystal::GetCollision(bool val)
{
	bCheck = val;
}

void HLDCrystal::SearchRange(bool val)
{
	bCheckRange = val;
}

void HLDCrystal::GetPlayerPoint(D3DXVECTOR2 pos)
{
	playerPos = pos;
}

void HLDCrystal::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	//crystal->DrawCollision(bCheck);
	crystal->DrawReds(bCheck);
	if (!bCheck) {
		crystalMoney->Position(-50000.0f, -50000.0f);
		
		crystal->Position(position);
		
	}

	if(!bCheck&&hitCount>2.0f){
	
	//position = D3DXVECTOR2(-50000.0f, -50000.0f);
	crystal->Position(-50000.0f, -50000.0f);
	crystalMoney->Position(position);
	bCheck = false;
	//crystalMoney->DrawBoundStopRange(true);
	//hitCount = 0.0f;
	}
	if (bCheck) {
		hitCount++;
		bCheck = false;
		
		
	}
	//bCheckRange = true;
	if (bCheckRange) {

		
	if (position.x - playerPos.x >= 5.0f) {
		position.x -= moveSpeed * Time::Delta();
	}
	else if (position.x - playerPos.x < 5.0f) {
		position.x += moveSpeed * Time::Delta();
	}

	if (position.y- playerPos.y >=5.0f ) {
		position.y -= moveSpeed * Time::Delta();
	}
	else if (position.y- playerPos.y <5.0f ) {
		position.y += moveSpeed * Time::Delta();
	}
	crystalMoney->Position(position);

	
     }
	if (bCheckMoney) {
		position = D3DXVECTOR2(-50000.0f, -50000.0f);
		crystal->Position(-50000.0f, -50000.0f);
		crystalMoney->Position(-50000.0f, -50000.0f);
	}
	crystalMoney->Scale(scale);
	crystal->Scale(scale);
	crystal->Update(V, P);
	crystalMoney->Update(V, P);
}

void HLDCrystal::Render()
{
	//if (!bCheck) {
		crystal->Render();
		crystalMoney->Render();
	//}

}

Sprite * HLDCrystal::GetSprite()
{
	return crystal;
}

Sprite * HLDCrystal::GetSpriteMoney()
{
	return crystalMoney;
}
