#include"stdafx.h"
#include"FileManger.h"
#include<algorithm>


vector<D3DXVECTOR2>FileManger::markers = { D3DXVECTOR2(0.0f, 0.0f) };
vector<pair<D3DXVECTOR2, D3DXVECTOR2>>FileManger::markers2 = { pair<D3DXVECTOR2,D3DXVECTOR2>(D3DXVECTOR2(0.0f,0.0f),D3DXVECTOR2(0.0f,0.0f)) };

void FileManger::Save(wstring filename)
{
	int reply=MessageBox(Hwnd, L"파일저장?", L"Save File", MB_YESNO);
	if (reply == IDYES) {
		BinaryWriter*w = new BinaryWriter();
		w->Open(filename);

		//오름차순 정렬
		sort(markers.begin(), markers.end(), FileManger::CompareX);

		w->UInt(markers.size());
		w->Byte(&markers[0], sizeof(D3DXVECTOR2)*markers.size());

		w->Close();
		SAFE_DELETE(w);

		markers.clear();
		wstring temp = filename + L"\n";
		MessageBox(Hwnd, temp.c_str(), L"완료", MB_OK);
	}
}

void FileManger::SaveLines()
{
	int reply = MessageBox(Hwnd, L"Line.bin저장?", L"Line", MB_YESNO);

	if (reply==IDYES) {
		BinaryWriter*w = new BinaryWriter();
		//파일 다이알로그 사용 x
		w->Open(L"line.bin");

		sort(markers2.begin(), markers2.end(), FileManger::CompareX2);

		w->UInt(markers2.size());
		w->Byte(&markers2[0], sizeof(pair<D3DXVECTOR2, D3DXVECTOR2>)*markers2.size());

		w->Close();
		SAFE_DELETE(w);

		markers2.clear();
		wstring temp = L"line.bin\n";
		MessageBox(Hwnd, temp.c_str(), L"완료", MB_OK);

	}
}

void FileManger::Load(wstring filename)
{
	
	BinaryReader*r = new BinaryReader;
	if (Path::ExistFile(filename) == true)
		r->Open(filename);
	else
		assert(false);

	UINT count;
	count = r->UInt();

	vector<D3DXVECTOR2> v;
	v.assign(count, D3DXVECTOR2());

	void* ptr = (void*)&(v[0]);
	r->Byte(&ptr, sizeof(D3DXVECTOR2)*count);
	r->Close();
	SAFE_DELETE(r);
	SetMarker(v);
    
}

void FileManger::LoadLines()
{
	BinaryReader*r = new BinaryReader;

	if (Path::ExistFile("line.bin") == true)
		r->Open(L"line.bin");
	else
		assert(false);

	UINT count;
	count = r->UInt();

	vector<pair<D3DXVECTOR2, D3DXVECTOR2>> v;

	v.assign(count, pair<D3DXVECTOR2, D3DXVECTOR2>());

	void* ptr = (void*)&(v[0]);
	r->Byte(&ptr, sizeof(pair<D3DXVECTOR2, D3DXVECTOR2>)*count);
	r->Close();
	SAFE_DELETE(r);
	SetMarker2(v);


}

void FileManger::SetMarker(vector<D3DXVECTOR2>& v)
{
	markers.clear();

	markers.assign(v.begin(), v.end());


}

void FileManger::SetMarker2(vector<pair<D3DXVECTOR2, D3DXVECTOR2>>& v)
{
	markers2.clear();

	markers2.assign(v.begin(), v.end());
}

vector<D3DXVECTOR2> FileManger::GetMarker()
{
	return markers;
}

vector<pair<D3DXVECTOR2, D3DXVECTOR2>> FileManger::GetMarker2()
{
	return markers2;
}
