#include"stdafx.h"
#include"OpeningHLD.h"
#include "./Viewer/Following.h"
#include"./Viewer/FreeCamera.h"

OpeningHLD::OpeningHLD(SceneValues * values)
	:Scene(values), bNext(false)
{
	//	wstring textureFile = Textures + L"./HDL/HDLLibrary.png";
	//wstring textureFile = Textures + L"./HDL/HDLresizeMenu.png";
	wstring textureFile = Textures + L"./HDL/opening.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	//wstring shaderRectFile = Shaders + L"Rect.fx";
	opening = new Animation;
	SAFE_DELETE(values->MainCamera);
	values->MainCamera = new Following;
	
	Clip*clip;
	{
		clip = new Clip(PlayMode::LoopStop);
		for (int j = 0; j < 52; j++) {
		 for (int i = 0; i < 5; i++) {
			
				clip->AddFrame(new Sprite(textureFile, shaderFile, i*300, j*169, (i+1)*300, (j+1)*169), 0.15f);
			
		   }
		}
		clip->AddFrame(new Sprite(textureFile, shaderFile,0,8788 , 300,8957 ), 0.15f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 300, 8788, 600,8957 ), 0.15f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 600, 8788, 900,8957 ), 0.15f);
		opening->AddClip(clip);
	}

	
	opening->Scale(1.0f, 1.0f);
	opening->Play(0);

}

OpeningHLD::~OpeningHLD()
{
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(opening);
}

void OpeningHLD::Position(float x, float y)
{
}

void OpeningHLD::Position(D3DXVECTOR2 val)
{
}



void OpeningHLD::Scale(float x, float y)
{
}

void OpeningHLD::Scale(D3DXVECTOR2 val)
{
}



void OpeningHLD::Update()
{



	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	opening->Scale(2.7f, 3.55f);
	opening->Play(0);
	if (!opening->GetClip()->EndFramePattern()) {
		bNext = true;
	}
	opening->Update(V, P);
}

void OpeningHLD::Render()
{
	opening->Render();

}
