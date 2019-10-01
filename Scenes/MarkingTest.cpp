#include"stdafx.h"
#include"MarkingTest.h"
#include"Object/Player.h"
#include"Object/Marker.h"
#include"Viewer/FreeCamera.h"
#include"./System/SoundManager.h"




MarkingTest::MarkingTest(SceneValues * values)
	:Scene(values)   //부모 생성자 초기화 
{
	wstring textureFile = L"";
	wstring shaderFile = Shaders+L"./Effect.fx";
	
	background = new Sprite(Textures+L"Sonic.png",shaderFile);

	

	
	player = new Player(D3DXVECTOR2(100, 500), D3DXVECTOR2(2.5f, 2.5f));
	values->MainCamera = new FreeCamera;
	//((FreeCamera*)(values->MainCamera)->Position)(0, 0);

	background->Position(0, 0);
	background->Scale(1.0f, 1.0f);
	soundManger = new SoundManager;
	soundManger->AddSound("BANG", "./_Sounds/gun.wav", true);
}

MarkingTest::~MarkingTest()
{
	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(background);
	SAFE_DELETE(player);

	for (Marker* marker : markers)
		SAFE_DELETE(marker);

}

void MarkingTest::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;
	background->Update(V,P);
	for (Marker* marker : markers)
		marker->Update(V, P);

	//player->Update(V, P);
	//마우스 포지션 매핑
	D3DXVECTOR2 mouse = Mouse->Position();
	mouse.x = mouse.x - (float)Width*0.5f;
	mouse.y = (mouse.y -((float)Height*0.5f))*(-1.0f);
	//카메라 위치 보장
	D3DXVECTOR2 camera = values->MainCamera->Position();
	D3DXVECTOR2 position = mouse + camera;
	if (Mouse->Up(0)){
		soundManger->Play("BANG");
	
		markers.emplace_back(new Marker(Shaders + L"Effect.fx", position));
	}
	
}

void MarkingTest::Render()
{
	ImGui::LabelText("Mouse Position", "%.2f,%.2f", Mouse->Position().x, Mouse->Position().y);
	if (ImGui::Button("OpenFile") == true) {
		function<void(wstring)> f = bind(&MarkingTest::OpenComplete, this, placeholders::_1);
		Path::OpenFileDialog(L"",Path::ImageFilter, L"./_Textures",f,Hwnd);
		//Path::OpenFileDialog(L"",  L"", L"", f, Hwnd); //default 내문서
	}



	for (Marker* marker : markers)
		marker->Render();

	if (ImGui::Button("Save Text") == true) {

		FILE* fp = NULL;
		fopen_s(&fp, "marker.txt", "w");

		//마커의 갯수
		fprintf(fp, "%d\n", markers.size());

		for (UINT i = 0; i < markers.size();i++ ) {
			//인덱스,x좌표,y좌표
			fprintf(fp, "%d,%f,%f\n", i, markers[i]->postion().x, markers[i]->postion().y);

		}
		fclose(fp);
	}
	ImGui::SameLine();
		//load
		if (ImGui::Button("Load Text") == true) {
			//파일 존재여부 검사
			if (Path::ExistFile("marker.txt") == true) {
				//불러오기 전에 현재  화면 지우기
				for (Marker* marker : markers)
					SAFE_DELETE(marker);
				markers.clear();

				FILE* fp;
				fopen_s(&fp, "marker.txt","r");

				UINT count;
				fscanf_s(fp, "%d\n",&count);

				for (UINT i = 0; i < count; i++) {
					UINT index;
					D3DXVECTOR2 position;

					fscanf_s(fp, "%d,%f,%f\n", &index, &position.x, &position.y);
					markers.emplace_back(new Marker(Shaders + L"Effect.fx",position));
				
				}
				fclose(fp);
			}
		}

		if (ImGui::Button("Save Bin") == true) {
			
			function<void(wstring)>f = bind(&MarkingTest::SaveComplete, this, placeholders::_1);
			Path::SaveFileDialog(L"", L"Binary\0*.bin", L"./",f,Hwnd);
		}//Save Bin
		//Load Bin
		ImGui::SameLine();
		if (ImGui::Button("Load Bin") == true) {
			function<void(wstring)>f = bind(&MarkingTest::OpenComplete, this, placeholders::_1);
			Path::OpenFileDialog(L"", L"Binary\0*.bin", L"./", f, Hwnd);
				
		}




	RenderBackground();

//	player->Render();

}

Player * MarkingTest::GetPlayer()
{
	return player;
}

void MarkingTest::RenderBackground()
{
	static D3DXVECTOR2 position(640, 320);
	static D3DXVECTOR2 scale(1.5f, 1.5f);
	ImGui::SliderFloat2("bg position", (float*)position, 0, 1000);
	ImGui::SliderFloat2("bg scale", (float*)scale, 0, 1000);

	//world를 이용해서 여러개를 찍어보자
	//background->Position(position);
	//background->Scale(scale);
	background->Render();
}

void MarkingTest::OpenComplete(wstring fileName)
{
	MessageBox(Hwnd, fileName.c_str(), L"Open", MB_OK);
	//BinaryWriter*w = new BinaryWriter;
	
		for (Marker* marker : markers)
			SAFE_DELETE(marker);
		markers.clear();

		BinaryReader* r = new BinaryReader;
		r->Open(fileName);

		UINT count;
		count = r->UInt();
		for (UINT i = 0; i < count; i++) {
			UINT number = r->UInt();
			D3DXVECTOR2 position = r->Vector2();

			markers.emplace_back(new Marker(Shaders + L"Effect.fx", position));
		}
		r->Close();
		SAFE_DELETE(r);
	
}

void MarkingTest::SaveComplete(wstring fileName)
{
	BinaryWriter*w = new BinaryWriter;

	//쓰기
	w->Open(fileName);

	//마커 갯수 저장
	w->UInt(markers.size());
	for (UINT i = 0; i < markers.size(); i++) {
		w->UInt(i);//인덱스
		w->Vector2(markers[i]->postion());
	}

	w->Close();
	SAFE_DELETE(w);

	wstring temp = fileName + L"\n 저장이 완료되었습니다.";
	MessageBox(Hwnd, temp.c_str(), L"저장완료", MB_OK);
}
