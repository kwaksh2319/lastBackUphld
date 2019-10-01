#include "stdafx.h"
#include "./System/Device.h"
#include"./Viewer/FreeCamera.h"
#include"./Viewer/Following.h"
#include"./Scenes/Scene.h"
#include"./Scenes/Stage1.h"
#include"./Scenes/Stage2.h"
#include"./Scenes/MarkingTest.h"
#include"./Scenes/LineTest.h"


//Sprite* mario;
//Background* background;




SceneValues* values;
vector<Scene*> scenes;


void InitScene()
{
	
	values = new SceneValues;
	values->MainCamera = new FreeCamera;//view

	D3DXMatrixIdentity(&values->Projection);
	//stage1=new Stage1();
	scenes.push_back(new LineTest(values));

	
	
	
	
}

void DestroyScene()
{
	for (Scene*scene : scenes)
		SAFE_DELETE(scene);
	
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(values);
	


}
D3DXVECTOR3 eye(0, 0, -1);

//D3DXVECTOR2 horizental(0,Width),vertical(0,Height);

void Update()
{
	

	values->MainCamera->Update();
	

	//Projection
	
	D3DXMatrixOrthoOffCenterLH(
		&values->Projection, 
		(float)Width*-0.5, (float)Width*0.5, (float)Height*-0.5, (float)Height*0.5,
		-10, 10

	);

	/*
	D3DXMatrixOrthoOffCenterLH(
		&values->Projection,
		horizental.x, horizental.y, vertical.x, vertical.y,
		-10, 10
	);*/

	for (Scene* scene : scenes)
		scene->Update();
	
	




}

void Render()
{
	


	D3DXCOLOR bgColor = D3DXCOLOR(0,0,0,1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		
		for (Scene* scene : scenes)
			scene->Render();
		


	}
	ImGui::Render();

	//DirectWrite::GetDC()->Clear();
	DirectWrite::GetDC()->BeginDraw(); {
		
		RECT rect = { 0,0,500,200 };
		wstring text = L"우리의 게임";
		DirectWrite::RenderText(text, rect);
	    
		rect.top += 20;
		rect.bottom += 20;
		text = L"ImGUI::FPS:" + to_wstring(ImGui::GetIO().Framerate);
		DirectWrite::RenderText(text, rect);


		rect.top += 20;
		rect.bottom += 20;
		text = L"Timer::FPS:" + to_wstring(Time::Get()->FPS());
		DirectWrite::RenderText(text, rect);



	}
	DirectWrite::GetDC()->EndDraw();
	
	SwapChain->Present(0, 0);
}