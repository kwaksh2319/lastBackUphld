#include "stdafx.h"
#include "LineTest.h"
#include "./Viewer/FreeCamera.h"
#include "./Render/Line.h"

#include"./Object/Ring.h"
#include"./Object/Fish.h"
#define fishCoverage position.x <fishes[i]->Position().x + 10.0f&&position.x > fishes[i]->Position().x - 10.0f&&position.y > fishes[i]->Position().y - 10.0f&&position.y < fishes[i]->Position().y + 10.0f

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

	for (Ring* ring : rings)
		SAFE_DELETE(ring);

	for (Fish* fish : fishes)
		SAFE_DELETE(fish);

}

void LineTest::Update()
{
	
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	

	background->Update(V, P);	
	
	//EditLine();

	for (Line* line : lines)
		line->Update(V, P);


	for (Ring*ring : rings)
		ring->Update(V, P);

	for (Fish* fish : fishes)
		fish->Update(V, P);

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

	for (Ring*ring : rings)
		ring->Render();

	for (Fish* fish : fishes)
		fish->Render();
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

void LineTest::EditRing()
{

	bool hovering = ImGui::GetIO().WantCaptureMouse;

	

	if (Mouse->Down(0) && hovering == false) {
		rings.push_back(new Ring(position));
		ringPoints.push_back(position);
	}
	if (Mouse->Press(2)) {
		for (size_t i = 0; i < rings.size(); i++) {
			if (position.x <rings[i]->Position().x + 10.0f&&
				position.x > rings[i]->Position().x - 10.0f&&
				position.y > rings[i]->Position().y - 10.0f&&
				position.y < rings[i]->Position().y + 10.0f) {
				rings[i]->Position(position);
				ringPoints[i] = position;
			}
		}
	}
	
	if (Mouse->Down(1) && hovering == false) {
		for (size_t i = 0; i < rings.size(); i++) {
			if (position.x <rings[i]->Position().x + 10.0f&&
				position.x > rings[i]->Position().x - 10.0f&&
				position.y > rings[i]->Position().y - 10.0f&&
				position.y < rings[i]->Position().y + 10.0f) {

				rings.erase(rings.begin()+i);
				ringPoints.erase(ringPoints.begin() + i);
			}

		}
		

	}
}

void LineTest::EditFish()
{

	bool hovering = ImGui::GetIO().WantCaptureMouse;



	if (Mouse->Down(0) && hovering == false) {
		fishes.push_back(new Fish(position));
		fishPoints.push_back(position);
	}
	if (Mouse->Press(2)) {
		for (size_t i = 0; i < fishes.size(); i++) {
			if (position.x <fishes[i]->Position().x + 10.0f&&
				position.x > fishes[i]->Position().x - 10.0f&&
				position.y > fishes[i]->Position().y - 10.0f&&
				position.y < fishes[i]->Position().y + 10.0f) {
				fishes[i]->Position(position);
				fishPoints[i] = position;
			}
		}
	}

	if (Mouse->Down(1) && hovering == false) {
		for (size_t i = 0; i < fishes.size(); i++) {
			if (position.x <fishes[i]->Position().x + 10.0f&&
				position.x > fishes[i]->Position().x - 10.0f&&
				position.y > fishes[i]->Position().y - 10.0f&&
				position.y < fishes[i]->Position().y + 10.0f) {

				fishes.erase(fishes.begin() + i);
				fishPoints.erase(fishPoints.begin() + i);
			}

		}


	}
}

void LineTest::RenderImGui()
{
	//for (Line* line : lines)
	//	ImGui::LabelText("", "%f %f %f %f", line->RightPoint().x, line->RightPoint().y, line->LeftPoint().x, line->LeftPoint().y);
	static int combo_item = 0;
	bool valueChanged = ImGui::Combo("item", &combo_item, "None\0Line\0Ring\0Fish\0Magician\0\0");


	if (combo_item == 1) {
		EditLine();
	}
	else if (combo_item == 2) {
		EditRing();
	}
	else if (combo_item == 3) {
		EditFish();
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

	if (ImGui::Button("Save Ring") == true) {
		FileManger::SetMarker(ringPoints);
		FileManger::Save(L"ring.bin");
	}
	ImGui::SameLine();
	if (ImGui::Button("Load Ring") == true) {
		for (size_t i = 0; i < rings.size(); i++)
			SAFE_DELETE(rings[i]);

		rings.clear();
		ringPoints.clear();

		FileManger::Load(L"ring.bin");
		ringPoints = FileManger::GetMarker();

		for (size_t i = 0; i < ringPoints.size(); i++)
			rings.push_back(new Ring(ringPoints[i]));

	}


	//fish


	if (ImGui::Button("Save Fish") == true) {
		FileManger::SetMarker(fishPoints);
		FileManger::Save(L"fish.bin");
	}
	ImGui::SameLine();
	if (ImGui::Button("Load Fish") == true) {
		for (size_t i = 0; i < fishes.size(); i++)
			SAFE_DELETE(fishes[i]);

		fishes.clear();
		fishPoints.clear();

		FileManger::Load(L"fish.bin");
		fishPoints = FileManger::GetMarker();

		for (size_t i = 0; i < fishPoints.size(); i++)
			fishes.push_back(new Fish(fishPoints[i]));

	}


	//=====================================================================
	//debug
	//=====================================================================
	ImGui::Separator();
	ImGui::LabelText("Lines", "%d", lines.size());
	ImGui::LabelText("LinePt", "%d", linePoints.size());
	ImGui::LabelText("GetMarker2", "%d", FileManger::GetMarker2().size());
}

