#include"stdafx.h"
#include"Astar.h"
#include"./Object/AstarPlayer.h"
#include"./Object/AstarMonster.h"
#include"./FindPath/Node.h"
#include"./Viewer/FreeCamera.h"







Astar::Astar(SceneValues * values)
	:Scene(values), mouse(0, 0), cameraPos(0, 0), position(0, 0), massSize(0, 0), bMove(false)   //부모 생성자 초기화 
{
	wstring textureFile = Textures + L"./Astar/Map.png";
	wstring shaderFile = Shaders+L"./Effect.fx";
	
	background = new Sprite(textureFile, shaderFile);
	player = new AstarPlayer(D3DXVECTOR2(-10, -150), D3DXVECTOR2(2, 2));
	monster = new AstarMonster(D3DXVECTOR2(227, 108), D3DXVECTOR2(3, 3));
	playerRect = player->GetSprite();
	monsterRect = monster->GetSprite();
	float tempX = monster->Scale().x*monsterRect->TextureSize().x;
	float tempY = monster->Scale().y*monsterRect->TextureSize().y;
	massSize = D3DXVECTOR2(tempX, tempY);

	node = new Node(monster->Position(),massSize);

	values->MainCamera = new FreeCamera;

} 

Astar::~Astar()
{
	SAFE_DELETE(background);
	SAFE_DELETE(player);
	SAFE_DELETE(monster);
	SAFE_DELETE(node);

}

void Astar::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P=values->Projection;

	mouse = Mouse->Position();
	mouse.x = mouse.x - (float)Width*0.5f;
	mouse.y = (mouse.y - (float)Height*0.5f)*-1.0f;
	cameraPos = values->MainCamera->Position();
	position = mouse + cameraPos;

	node->GetMouseCursor(position);
	bMove = monster->Move();

	node->ReadyToStart(bMove == false && Mouse->Down(1));
	
	node->GetStartPos(monster->Position());
	node->GetGoalPos(player->Position());
	
	node->Update(V, P);

	background->Update(V, P);
	player->Update(V, P);
	monster->Update(V, P);
	

	
}

void Astar::Render()
{
	background->Render();
	player->Render();
	monster->Render();
	node->Render();
	
}
