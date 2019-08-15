#include "Device.h"

int APIENTRY WinMain(HINSTANCE hinstance, HINSTANCE  previntance, LPSTR IpCmdLine, int mCmdShow) {
	InitWidow(hinstance, mCmdShow);
	InitDircet3D(hinstance);
	Running();
	Destory();

}

HWND Hwnd = NULL;
wstring Title = L"D2D GAME";

//i-interface 
//swapchain back buffer 관리 
IDXGISwapChain* SwapChain;//back buffer mangement
ID3D11Device* Device; //setting
ID3D11DeviceContext* DeviceContext; //setting input
ID3D11RenderTargetView* RTV;//page? display


//shader load
ID3D11VertexShader* VertexShader;
ID3D11PixelShader* PixelShader; 
ID3D10Blob* VsBlob;
ID3D10Blob* PsBlob;


void InitWidow(HINSTANCE hinstance, int nCMdShow)
{
	//RegisterWindow
	{   //window api
		WNDCLASSEX wc;
		wc.cbSize = sizeof(WNDCLASSEX);
		wc.style = CS_HREDRAW | CS_VREDRAW; //r가로 세로 그려주기
		wc.lpfnWndProc = WndProc;//윈도우 프로시져
		wc.cbClsExtra = NULL;
		wc.cbWndExtra = NULL;
		wc.hInstance = hinstance;
		wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wc.hCursor = LoadCursor(NULL, IDC_ARROW);//화살표 아이콘
		wc.hbrBackground = static_cast<HBRUSH>(WHITE_BRUSH);
		wc.lpszMenuName = NULL;
		wc.lpszClassName = Title.c_str();//윈도우 창의 식별문자
		wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

		WORD check = RegisterClassEx(&wc);
		assert(check != NULL); //check !!



	}
	
	//CreateHandle
	{
		Hwnd = CreateWindowEx
		(NULL,
			Title.c_str(),
			Title.c_str(),
			WS_OVERLAPPEDWINDOW,   //우리가 만든 창위로 오버랩
			CW_USEDEFAULT,  
			CW_USEDEFAULT,
			Width,
			Height,
			NULL,
			NULL,
			hinstance,
			NULL
		);

		assert(Hwnd != NULL);




	}

	ShowWindow(Hwnd, nCMdShow);
	UpdateWindow(Hwnd);


}

void InitDircet3D(HINSTANCE hinstance)
{
	//SwapChain direct back buffer 총괄자 

	//swaochain buffer
	DXGI_MODE_DESC bufferDesc;
	ZeroMemory(&bufferDesc, sizeof(DXGI_MODE_DESC));
	bufferDesc.Width = Width;
	bufferDesc.Height = Height;
	bufferDesc.RefreshRate.Numerator = 60;
	bufferDesc.RefreshRate.Denominator = 1;
	bufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;//rgb model 
	bufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

	//sampling
	DXGI_SWAP_CHAIN_DESC swapDesc ;
	ZeroMemory(&swapDesc, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapDesc.BufferDesc = bufferDesc;
	swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapDesc.BufferCount = 1;
	swapDesc.SampleDesc.Count = 1;
	swapDesc.SampleDesc.Quality = 0;
	swapDesc.OutputWindow = Hwnd;
	swapDesc.Windowed = TRUE;
	swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;


	//기능수준정의 version
	vector<D3D_FEATURE_LEVEL>feature_level = {
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	//create Device swap Chain
	HRESULT hr = D3D11CreateDeviceAndSwapChain
	(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,           //graphic mode
		NULL,
		NULL,
		feature_level.data(),
		feature_level.size(),
		D3D11_SDK_VERSION,
		&swapDesc,
		&SwapChain,
		&Device,
		NULL,
		&DeviceContext
		

	);
	assert(SUCCEEDED(hr));

	//backbuffer

	ID3D11Texture2D *BackBuffer;
	hr = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&BackBuffer);
    assert(SUCCEEDED(hr));

//create RTV

    hr = Device->CreateRenderTargetView(BackBuffer, NULL, &RTV);
    assert(SUCCEEDED(hr));
    BackBuffer->Release();


//OM output merge
DeviceContext->OMSetRenderTargets(1, &RTV, NULL);


//Create shader

{
	//vertax Blob
	HRESULT hr;
	hr = D3DX10CompileFromFile(
		L"Effect.hlsl", 0, 0, "VS", "vs_5_0",
		0, 0, 0,
		&VsBlob, 0, 0

	);
	assert(SUCCEEDED(hr));


	//pixel Blob
	hr = D3DX11CompileFromFile(
		L"Effect.hlsl", 0, 0, "PS", "ps_5_0",
		0, 0, 0,
		&PsBlob, 0, 0
	);
	assert(SUCCEEDED(hr));

	//create shader
	hr = Device->CreateVertexShader(
		VsBlob->GetBufferPointer(),
		VsBlob->GetBufferSize(),
		NULL,
		&VertexShader

	);
	assert(SUCCEEDED(hr));

	hr = Device->CreatePixelShader(
		PsBlob->GetBufferPointer(),
		PsBlob->GetBufferSize(),
		NULL,
		&PixelShader

	);
	assert(SUCCEEDED(hr));


	//Set Shader
	DeviceContext->VSSetShader(VertexShader, 0, 0);
	DeviceContext->PSSetShader(PixelShader, 0, 0);

}


//create view port
{
	D3D11_VIEWPORT viewPort;
	ZeroMemory(&viewPort, sizeof(D3D11_VIEWPORT));
	viewPort.TopLeftX = 0;
	viewPort.TopLeftY = 0;
	viewPort.Width = Width;
	viewPort.Height = Height;

	DeviceContext->RSSetViewports(1, &viewPort);
}






}




void Destory()
{

	PixelShader->Release();
	VertexShader->Release();
	PsBlob->Release();
	VsBlob->Release();

	RTV->Release();
	DeviceContext->Release();
	SwapChain->Release();
	Device->Release();
}



WPARAM Running()
{
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));
	InitScene();
	////////////////////////////
	while (true) {

		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)){
		 if (msg.message == WM_QUIT)break;
		   TranslateMessage(&msg);
		     DispatchMessage(&msg);
          }
		else {
			Update();
			Render();
		}
	}


	///////////////////////////
	DestoryScene();
	return msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wPARAM, LPARAM Lparam)
{

	switch (msg)
	{
	case WM_DESTROY: PostQuitMessage(0); return 0;

		break;
	}
	return DefWindowProc(hwnd, msg, wPARAM, Lparam);
}
