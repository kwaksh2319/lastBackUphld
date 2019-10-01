#include"stdafx.h"
#include"Stage1.h"
#include"./Object/Player.h"
#include"./Viewer/Following.h"
#include"./Object/Bullet.h"
#include"./Viewer/FreeCamera.h"
#include"./Object/Fire.h"


Stage1::Stage1(SceneValues * values)
	:Scene(values)   //부모 생성자 초기화 
{
	wstring textureFile = L"";
	wstring shaderFile = Shaders+L"./Effect.fx";
	
	background = new Sprite(Textures+L"CastleStage.png",shaderFile);
	
	


	
	player = new Player(D3DXVECTOR2(100, 170), D3DXVECTOR2(2.5f, 2.5f));
	bullet = new Bullet(shaderFile,D3DXVECTOR2(300,300),0,0);
	fire = new Fire(shaderFile, D3DXVECTOR2(300, 170));
	SAFE_DELETE(values->MainCamera);
	values->MainCamera = new Following(player);

}

Stage1::~Stage1()
{
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(background);
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);
	SAFE_DELETE(fire);

}

void Stage1::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	background->Update(V,P);

	player->Update(V, P);
	bullet->Update(V, P);
	fire->Update(V, P);

}

void Stage1::Render()
{

	static bool bCheck = false;

	Sprite* playerRect =player ->GetSprite();
	bCheck = Sprite::Aabb(playerRect, bullet->postion());
	//bCheck = playerRect->Aabb(bullet->postion());
    ImGui::LabelText("AABB:","%d",bCheck?1:0);

	static bool bCheck2 = false;
	Sprite*fireRect = fire->GetClip()->GetSprite();
	bCheck2 = Sprite::Aabb(playerRect, fireRect);
	ImGui::LabelText("AABB2:", "%d", bCheck2 ? 1 : 0);




	//OBB
	static bool bCheck3 = false;

	Sprite* bullet_rect = bullet->GetClip()->GetSprite();
	bCheck3 = Sprite::Obb(bullet_rect, fireRect);
	ImGui::LabelText("OBB", "%d", bCheck3 ? 1 : 0);
	bullet_rect->DrawCollision(bCheck3);
	fireRect->DrawCollision(bCheck3);

	//마우스태스트
	ImGui::LabelText("MousePosition", "%.2f,%.2f", Mouse->Position().x, Mouse->Position().y);
	ImGui::LabelText("MouseButton", "%d", Mouse->DoubleClick(0));


	//RenderBackground();
	//player->Render();
	bullet->Render();
	fire->Render();
}

Player * Stage1::GetPlayer()
{
	return player;
}

void Stage1::RenderBackground()
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