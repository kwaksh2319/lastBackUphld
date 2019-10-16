
#include "stdafx.h"
#include "Sonic.h"

#include "./Viewer/Following.h"

#include "./Render/Line.h"
#include "./Object/Ring.h"
#include "./Object/Fish.h"
#include "./Object/SonicPlayer.h"


Sonic::Sonic(SceneValues* values)
	:Scene(values), lineVisible(false), slope(0)
{
	wstring backgroundFile = Textures + L"Sonic.png";
	wstring shaderFile = Shaders + L"Effect.fx";

	background = new Sprite(backgroundFile, shaderFile);

	//	player = new SonicPlayer(D3DXVECTOR2(0, 0), D3DXVECTOR2(1, 1));
		//선 로드
	FileManger::LoadLines();
	linePoints = FileManger::GetMarker2();
	for (size_t i = 0; i < linePoints.size(); i++)
		lines.push_back(new Line(linePoints[i].first, linePoints[i].second));

	//링 로드
	FileManger::Load(L"ring.bin");
	ringPoints = FileManger::GetMarker();
	for (size_t i = 0; i < ringPoints.size(); i++)
		rings.push_back(new Ring(ringPoints[i]));

	//적(Fish) 로드
	FileManger::Load(L"fish.bin");
	fishPoints = FileManger::GetMarker();
	for (size_t i = 0; i < fishPoints.size(); i++)
		fishes.push_back(new Fish(fishPoints[i]));
	player = new SonicPlayer(D3DXVECTOR2(-5500, 150), D3DXVECTOR2(1, 1));

	SAFE_DELETE(values->MainCamera);
	values->MainCamera = new Following(player);

}
Sonic::~Sonic()
{
	SAFE_DELETE(background);
	SAFE_DELETE(player);

	for (Line* line : lines)
		SAFE_DELETE(line);
	for (Ring* ring : rings)
		SAFE_DELETE(ring);
	for (Fish* fish : fishes)
		SAFE_DELETE(fish);

}

void Sonic::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	D3DXVECTOR2 playerPos = player->Position();

	//링
	{
		//플레이어가 일정 거리에 있을 경우만 업데이트
		for (Ring* ring : rings)
		{
			if ((playerPos.x - Width < ring->Position().x &&
				playerPos.x + Width > ring->Position().x) &&
				(playerPos.y - Height < ring->Position().y &&
					playerPos.y + Height > ring->Position().y))
				ring->Visible(true);
			else
				ring->Visible(false);
		}
	}

	//라인 충돌
	for (Line* line : lines)
	{
		if (Math::SementIntersects
		(
			player->Position(),
			player->BottomVector(),
			line->LeftPoint(),
			line->RightPoint()
		))
		{
			line->DrawCollision(true);
			player->LineBottomCollision(true);
			
			player->LineLeftPoint(line->LeftPoint());
			player->LineRightPoint(line->RightPoint());

			
		//	slope = line->Slope();
			break;
		}
		else {
			line->DrawCollision(false);
			player->LineBottomCollision(false);
			slope = -99.0f;
		}



	}

	for (Line* line : lines)
	{

		if (Math::SementIntersects
		(
			player->Position(),
			player->LeftVector(),
			line->LeftPoint(),
			line->RightPoint()
		))
		{
			line->DrawCollision(true);
			player->LeftCollision(true);
			player->LineLeftPoint_Left(line->LeftPoint());
			player->LineRightPoint_Left(line->RightPoint());
			//slope = line->Slope();
			break;
			//

		}
		else {
			line->DrawCollision(false);
			player->LeftCollision(false);
			//slope = -99.0f;
		}

	}
	for (Line* line : lines)
	{
		if (Math::SementIntersects
		(
			player->Position(),
			player->RightVector(),
			line->LeftPoint(),
			line->RightPoint()
		))
		{
			line->DrawCollision(true);
			player->RightCollision(true);
			player->LineLeftPoint_Right(line->LeftPoint());
			player->LineLeftPoint_Right(line->RightPoint());
			//slope = line->Slope();
			break;
		
			//aaaa			

		}
		else {
			line->DrawCollision(false);
			player->RightCollision(false);
			//slope = -99.0f;
		}
	}
	for (Line* line : lines)
	{
		if (Math::SementIntersects
		(
			player->Position(),
			player->TopVector(),
			line->LeftPoint(),
			line->RightPoint()
		))
		{
			line->DrawCollision(true);
			player->TopCollision(true);
			player->LineLeftPoint_Top(line->LeftPoint());
			player->LineRightPoint_Top(line->RightPoint());
			slope = line->Slope();
			break;

			//aaaa			

		}
		else {
			line->DrawCollision(false);
			player->TopCollision(false);
			//slope = -99.0f;
		}
	}
	
	
	background->Update(V, P);

	if (lineVisible) {
		for (Line* line : lines)
			line->Update(V, P);
	}



	for (Ring* ring : rings)
		ring->Update(V, P);

	for (Fish* fish : fishes)
		fish->Update(V, P);

	player->Update(V, P);


}

void Sonic::Render()
{
	ImGui::Checkbox("Line visible", &lineVisible);

	background->Render();
	if (lineVisible) {
		for (Line* line : lines)
			line->Render();
	}
	for (Ring* ring : rings)
		ring->Render();
	for (Fish* fish : fishes)
		fish->Render();

	player->Render();
}



