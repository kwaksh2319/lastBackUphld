#include"stdafx.h"
#include"Fire.h"


Fire::Fire(wstring shaderFile, D3DXVECTOR2 start)
	: scale(1,1), rotation(0,0,0)

{
	wstring textureFile = Textures + L"fire.png";

	clip = new Clip(PlayMode::Loop);
	for (int y = 0; y < 3; y++) {
		for (int x = 0; x < 5; x++) {

			float startX = x * 43;
			float startY = y * 67;
			float endX = (x + 1) * 43;
			float endY = (y + 1) * 67;

			clip->AddFrame(new Sprite(textureFile, shaderFile, startX, startY, endX, endY),0.1f);

		}
	}


	position = start;
	clip->Position(position);
	clip->Scale(scale);
	clip->RotationDegree(rotation);
	clip->Play();

	clip->DrawBound(true);


}

Fire::~Fire()
{
	SAFE_DELETE(clip);

}

void Fire::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	

	clip->Position(position);
	clip->Update(V,P);
}

void Fire::Render()
{
	
	ImGui::Separator();
	ImGui::SliderFloat2("Fire Scale", (float*)&scale, 1, 5);
	ImGui::SliderFloat3("Fire rotation", (float*)&rotation, -179.9, 179.9);
	
	clip->Scale(scale);
	clip->Rotation(rotation);

	clip->Render();

}
