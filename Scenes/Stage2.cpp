#include"stdafx.h"
#include"Stage2.h"
#include"Object/Player.h"
#include"Viewer/Following.h"



Stage2::Stage2(SceneValues * values)
	:Scene(values)   //부모 생성자 초기화 
{
	wstring textureFile = L"";
	wstring shaderFile = Shaders+L"./Effect.fx";
	
	background = new Sprite(Textures+L"Stage.png",shaderFile);

	SAFE_DELETE(values->MainCamera);


	
	player = new Player(D3DXVECTOR2(100, 500), D3DXVECTOR2(2.5f, 2.5f));
	values->MainCamera = new Following(player);
	
}

Stage2::~Stage2()
{
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(background);
	SAFE_DELETE(player);

}

void Stage2::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	background->Update(V,P);

	player->Update(V, P);

}

void Stage2::Render()
{
	RenderBackground();

	player->Render();

}

Player * Stage2::GetPlayer()
{
	return player;
}

void Stage2::RenderBackground()
{
	static D3DXVECTOR2 position(640, 320);
	static D3DXVECTOR2 scale(1.5f, 1.5f);
	ImGui::SliderFloat2("bg position", (float*)position, 0, 1000);
	ImGui::SliderFloat2("bg scale", (float*)scale, 0, 1000);

	//world를 이용해서 여러개를 찍어보자
	background->Position(position);
	background->Scale(scale);
	background->Render();
}