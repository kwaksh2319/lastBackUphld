#pragma once
class DirectWrite {
private:
	DirectWrite();
	~DirectWrite();

private:
	static DirectWrite* instance;

private:
	ID2D1Factory1*factory;
	static IDWriteFactory* writeFactory;

	ID2D1Device* device;
	static ID2D1DeviceContext* deviceContext;

	static ID2D1Bitmap1* bitmap;
	static IDXGISurface* surface;

	//폰트
	static ID2D1SolidColorBrush* brush;
	static IDWriteTextFormat* format;



public:
	//singleton func
	static void Create();
	static void Delete();

	static DirectWrite* Get();
	static ID2D1DeviceContext* GetDC() { return deviceContext; }
	//2D용 백버퍼 관리 함수
	static void CreateBackBuffer();
	static void DeleteBackBuffer();
	//글자출력
	static void RenderText(wstring& text, RECT & rect);


};