#include "stdafx.h"
#include "LineTest.h"

#include "./Render/Line.h"
#include "./Viewer/FreeCamera.h"



LineTest::LineTest(SceneValues * values)
	:Scene(values), mouse(0, 0), cameraPos(0, 0), position(0, 0)
{
	wstring backgroundFile = Textures + L"Sonic.png";
	wstring shaderFile = Shaders + L"Effect.fx";

	background = new Sprite(backgroundFile, shaderFile);
	
	values->MainCamera = new FreeCamera;

}

LineTest::~LineTest()
{	
	SAFE_DELETE(background);
	
	for (Line* line : lines)
		SAFE_DELETE(line);

}

void LineTest::Update()
{
	
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	

	background->Update(V, P);	
	
	//EditLine();

	for (Line* line : lines)
		line->Update(V, P);

	//마우스 포지션 매핑
	mouse = Mouse->Position();
	mouse.x = mouse.x - (float)Width * 0.5f;
	mouse.y = (mouse.y - (float)Height * 0.5f) * -1.0f;

	//카메라 위치 보장
	cameraPos = values->MainCamera->Position();
	position = mouse + cameraPos;
//	position = D3DXVECTOR2(0, 0);

}

void LineTest::Render()
{
	RenderImGui();

	background->Render();

	for (Line* line : lines)
		line->Render();
}

void LineTest::EditLine()
{
	bool hovering = ImGui::GetIO().WantCaptureMouse;

	//시작점 저장
	if (Mouse->Down(0) && hovering == false)
	{
		lastPosition = position;
	}

	//마우스를 떼면 라인 1개 그리기
	else if (Mouse->Up(0) && hovering == false)
	{
		//수평선 만들기
		if (Key->Press(VK_SHIFT))
		{
			position.y = lastPosition.y;

			lines.push_back(new Line(lastPosition, position));
			linePoints.push_back(pair<D3DXVECTOR2, D3DXVECTOR2>(lastPosition, position));
		}
		//일반선 그리기
		else
		{
			lines.push_back(new Line(lastPosition, position));
			linePoints.push_back(pair<D3DXVECTOR2, D3DXVECTOR2>(lastPosition, position));
		}
	}
	if (Mouse->Press(2)) {
		for (UINT i = 0; i < lines.size(); i++) {
			if (position.x <lines[i]->LeftPoint().x + 10.0f&&
				position.x > lines[i]->LeftPoint().x - 10.0f&&
				position.y > lines[i]->LeftPoint().y - 10.0f&&
				position.y < lines[i]->LeftPoint().y + 10.0f)
			{
				lines[i]->LeftPoint(position);
				linePoints[i].first = position;

			}

			if (position.x <lines[i]->RightPoint().x + 10.0f&&
				position.x > lines[i]->RightPoint().x - 10.0f&&
				position.y > lines[i]->RightPoint().y - 10.0f&&
				position.y < lines[i]->RightPoint().y + 10.0f)
			{
				lines[i]->RightPoint(position);
				linePoints[i].second = position;
			}



		}
	}
	if (Mouse->Down(1)) {
		for (UINT i = 0; i < lines.size(); i++) {

			if (position.x <lines[i]->RightPoint().x + 10.0f&&
				position.x > lines[i]->RightPoint().x - 10.0f&&
				position.y > lines[i]->RightPoint().y - 10.0f&&
				position.y < lines[i]->RightPoint().y + 10.0f)
			{
				lines.erase(lines.begin() + i);
				linePoints.erase(linePoints.begin() + i);
				
			}
		}

	}
	


}

void LineTest::RenderImGui()
{
	//for (Line* line : lines)
	//	ImGui::LabelText("", "%f %f %f %f", line->RightPoint().x, line->RightPoint().y, line->LeftPoint().x, line->LeftPoint().y);
	static int combo_item = 0;
	bool valueChanged = ImGui::Combo("item", &combo_item, "None\0Line\0\0");


	if (combo_item == 1) {
		EditLine();
	}
	//=====================================================================
	//button
	//=====================================================================
	
	//Line
	if (ImGui::Button("Save Line") == true) {

		FileManger::SetMarker2(linePoints);
		FileManger::SaveLines();
	}
	ImGui::SameLine();
	if (ImGui::Button("Load Line") == true) {

		for (UINT i = 0; i < lines.size(); i++)
			SAFE_DELETE(lines[i]);
		lines.clear();
		linePoints.clear();

		FileManger::LoadLines();
		linePoints = FileManger::GetMarker2();

		for (UINT i = 0; i < linePoints.size(); i++)
			lines.push_back(new Line(linePoints[i].first, linePoints[i].second));
	}


	//=====================================================================
	//debug
	//=====================================================================
	ImGui::Separator();
	ImGui::LabelText("Lines", "%d", lines.size());
	ImGui::LabelText("LinePt", "%d", linePoints.size());
	ImGui::LabelText("GetMarker2", "%d", FileManger::GetMarker2().size());
}

