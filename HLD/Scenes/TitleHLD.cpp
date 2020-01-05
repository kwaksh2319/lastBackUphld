#include"stdafx.h"
#include"TitleHLD.h"
#include "./Viewer/Following.h"
#include"./Viewer/FreeCamera.h"

TitleHLD::TitleHLD(SceneValues * values)
	:Scene(values),bNext(false),bCheckSelect(false)
{
//	wstring textureFile = Textures + L"./HDL/HDLLibrary.png";
	wstring textureFile = Textures + L"./HDL/HDLresizeMenu.png";
	//wstring textureFile = Textures + L"./HDL/opening.png";
	wstring shaderFile = Shaders + L"Effect.fx";
	wstring shaderRectFile = Shaders + L"Rect.fx";
	title = new Animation; 
	SAFE_DELETE(values->MainCamera);
	values->MainCamera = new Following;
	rectSelect = new Rect(shaderRectFile);
	Clip*clip;
	{
		clip = new Clip(PlayMode::LoopStop);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 580, 530, 914), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 580, 1130, 914), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 580, 1730, 914), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 580, 2330, 914), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 580, 2930, 914), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 920, 530, 1254), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 920, 1130, 1254), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 920, 1730, 1254), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 920, 2330, 1254), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 920, 2930, 1254), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 1255, 530, 1589), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 1255, 1130, 1589), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 1255, 1730, 1589), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 1255, 2330, 1589), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 1255, 2930, 1589), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 1595, 530, 1929), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 1595, 1130, 1929), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 1595, 1730, 1929), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 1595, 2330, 1929), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 1595, 2930, 1929), 0.1f);


		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 1934, 530, 2268), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 1934, 1130, 2268), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 1934, 1730, 2268), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 1934, 2330, 2268), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 1934, 2930, 2268), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 2270, 530, 2604), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 2270, 1130, 2604), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 2270, 1730, 2604), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 2270, 2330, 2604), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 2270, 2930, 2604), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 2609, 530, 2943), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 2609, 1130, 2943), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 2609, 1730, 2943), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 2609, 2330, 2943), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 2609, 2930, 2943), 0.1f);


		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 2947, 530, 3281), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 2947, 1130, 3281), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 2947, 1730, 3281), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 2947, 2330, 3281), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 2947, 2930, 3281), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 3285, 530, 3619), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 3285, 1130, 3619), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 3285, 1730, 3619), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 3285, 2330, 3619), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 3285, 2930, 3619), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 3623, 530, 3957), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 3623, 1130, 3957), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 3623, 1730, 3957), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 3623, 2330, 3957), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 3623, 2930, 3957), 0.1f);


		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 3960, 530, 4294), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 3960, 1130, 4294), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 3960, 1730, 4294), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 3960, 2330, 4294), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 3960, 2930, 4294), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 4301, 530, 4635), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 4301, 1130, 4635), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 4301, 1730, 4635), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 4301, 2330, 4635), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 4301, 2930, 4635), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 4636, 530, 4970), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 4636, 1130, 4970), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 4636, 1730, 4970), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 4636, 2330, 4970), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 4636, 2930, 4970), 0.1f);


		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 4975, 530, 5309), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 4975, 1130, 5309), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 4975, 1730, 5309), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 4975, 2330, 5309), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 4975, 2930, 5309), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 5312, 530, 5646), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 5312, 1130, 5646), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 5312, 1730, 5646), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 5312, 2330, 5646), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 5312, 2930, 5646), 0.1f);

		clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 5650, 530, 5984), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 5650, 1130, 5984), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 5650, 1730, 5984), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 5650, 2330, 5984), 0.1f);
		clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 5650, 2930, 5984), 0.1f);
		title->AddClip(clip);
	}

	{
	clip = new Clip(PlayMode::Loop);

	clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 5988, 530, 6322), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 5988, 1130, 6322), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 5988, 1730, 6322), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 5988, 2330, 6322), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 5988, 2930, 6322), 0.1f);


	clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 6326, 530, 6660), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 6326, 1130, 6660), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 6326, 1730, 6660), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 6326, 2330, 6660), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 6326, 2930, 6660), 0.1f);

	clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 6664, 530, 6998), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 6664, 1130, 6998), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 6664, 1730, 6998), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 6664, 2330, 6998), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 6664, 2930, 6998), 0.1f);

	clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 7002, 530, 7336), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 7002, 1130, 7336), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 7002, 1730, 7336), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 7002, 2330, 7336), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 7002, 2930, 7336), 0.1f);

	clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 7340, 530, 7674), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 7340, 1130, 7674), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 7340, 1730, 7674), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 7340, 2330, 7674), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 7340, 2930, 7674), 0.1f);

	clip->AddFrame(new Sprite(textureFile, shaderFile, 55, 7680, 530, 8014), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 655, 7680, 1130, 8014), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1255, 7680, 1730, 8014), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 1855, 7680, 2330, 8014), 0.1f);
	clip->AddFrame(new Sprite(textureFile, shaderFile, 2455, 7680, 2930, 8014), 0.1f);

	

	title->AddClip(clip);
	}
	state = TitlState::Appear;
	title->Scale(1.0f, 1.0f);
	title->Play(UINT(state));

}

TitleHLD::~TitleHLD()
{
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(title);
}

void TitleHLD::Position(float x, float y)
{
}

void TitleHLD::Position(D3DXVECTOR2 val)
{
}



void TitleHLD::Scale(float x, float y)
{
}

void TitleHLD::Scale(D3DXVECTOR2 val)
{
}



void TitleHLD::Update()
{



	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	
	switch (state)
	{
	case TitlState::Appear:
		title->Play(UINT(state));
		if (!title->GetClip()->EndFramePattern()) {
			state = TitlState::Idle;
		}

		break;

	case TitlState::Idle:
		title->Play(UINT(state));
		if (Key->Down(VK_UP) || Key->Down(VK_DOWN)) {
			bCheckSelect = !bCheckSelect;
		}
		if (!bCheckSelect) {
			rectSelect->Position(0, -210.0f);
		}
		else if (bCheckSelect) {
			rectSelect->Position(0, -235.0f);
		}
		if(!bCheckSelect){
		if (Key->Down(VK_RETURN)) {
			bNext = true;
		 }
		}
		break;


	default:
		break;
	}
	
	
	rectSelect->Scale(110.0f, 20.0f);
		
	rectSelect->Color(1.0f, 0.0f, 1.0f);
	rectSelect->Update(V, P);
	title->Update(V, P);
}

void TitleHLD::Render()
{
	title->Render();
	
	if (state == TitlState::Idle) {
		rectSelect->Render();
		DirectWrite::GetDC()->BeginDraw(); {

			RECT rects = { 0,0,500,200 };
			rects.top += 500;
			rects.bottom += 500;
			rects.left += 350;
			rects.right += 350;
			wstring text = L"Enter to Play";
			DirectWrite::RenderText(text, rects);
			rects.left += 40;
			rects.right += 40;
			rects.top += 25;
			rects.bottom += 25;
			text = L"Exit";
			DirectWrite::RenderText(text, rects);
			/*
			rect.top += 20;
			rect.bottom += 20;
			text = L"ImGUI::FPS:" + to_wstring(ImGui::GetIO().Framerate);
			DirectWrite::RenderText(text, rect);


			rect.top += 20;
			rect.bottom += 20;
			text = L"Timer::FPS:" + to_wstring(Time::Get()->FPS());
			DirectWrite::RenderText(text, rect);
			*/


		}
		DirectWrite::GetDC()->EndDraw();
		
		//SwapChain->Present(0, 0);


	}
}
