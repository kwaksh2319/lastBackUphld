#include"stdafx.h"
#include"InventoryHDL.h"


#define Iven inventory[j][i]
InventoryHDL::InventoryHDL(D3DXVECTOR2 pos, D3DXVECTOR2 size)
	:HLDPlayer(HLDPlayer::position), bCheck(false)
{

	wstring shaderFile = Shaders + L"Rect.fx";
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			float positionX = i * size.x - Width * 0.5f;
			float positionY = j * size.y - Height * 0.5f;
			Iven =new Rect(shaderFile, D3DXVECTOR2(positionX, positionY), size);
		
		
		
		}
	}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			Iven->Position(-50000.0f, -50000.0f);
		    
		}
	}
}

InventoryHDL::~InventoryHDL()
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 4; j++) {
			SAFE_DELETE(Iven);

		}
	}
}

void InventoryHDL::Position(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Position(input);
}

void InventoryHDL::Position(D3DXVECTOR2 val)
{
	position = val;
}

void InventoryHDL::Scale(float x, float y)
{
	D3DXVECTOR2 input = D3DXVECTOR2(x, y);
	Scale(input);
}

void InventoryHDL::Scale(D3DXVECTOR2 val)
{
	scale = val;
}

void InventoryHDL::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	//player->Update(V, P);
	//if(HLDPlayer::bCheckInven){
	
	//HLDPlayer::KeyDirection();
	//player->Update(V, P);
	if (Key->Down('I')) {
		bCheck = !bCheck;
	}
	if (bCheck) {
		int count = 0;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {

				Iven->Position(position.x + 60.0f*j, position.y + 60.0f*i);
				Iven->Color(0, 0, 0);
				Iven->Update(V, P);
			}
		}
		for (Sprite *itemMoneys : itemMoney) {
			     
			int share=count/12;
			int remainder=count%12;

			itemMoneys->Position(inventory[remainder][share]->Position().x, inventory[remainder][share]->Position().y);
			itemMoneys->Update(V, P);
			count++;
			
		}
	}


	
	if (!bCheck) {
		for (Sprite *itemMoneys : itemMoney) {
			itemMoneys->Position(-50000.0f, -50000.0f);
			itemMoneys->Update(V, P);
		}
	}
	
	//}
}

void InventoryHDL::Render()
{
	//if (HLDPlayer::bCheckInven) {
	if (bCheck) {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 4; j++) {
				Iven->Render();
			}
		}

		for (Sprite *itemMoneys : itemMoney) {
			//itemMoneys->Position(inventory[0][0]->Position().x, inventory[0][0]->Position().y);
			itemMoneys->Render();
		}
	}
	//}
}

void InventoryHDL::SetSprite(Sprite * data)
{
	itemMoney.push_back(data);
}
