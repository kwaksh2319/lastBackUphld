#pragma once

#include<Windows.h>
#include<assert.h>

#include<vector>
#include<string>


using namespace std;


#include<d3d11.h>
#include<D3DX11.h>
#include<D3DX10.h>
#include<D3DX10math.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dx11.lib")
#pragma comment(lib,"d3dx10.lib")

//Global

const UINT Width = 1024;
const UINT Height = 768;

extern HWND Hwnd;
extern wstring Title;

//DX Interface

extern IDXGISwapChain* SwapChain;
extern ID3D11Device* Device;
extern ID3D11DeviceContext* DeviceContext;
extern ID3D11RenderTargetView* RTV;

extern ID3D11VertexShader* VertexShader;
extern ID3D11PixelShader* PixelShader;
extern ID3D10Blob* VsBlob;
extern ID3D10Blob* PsBlob;

//INIT FUNC

void InitWidow(HINSTANCE hinstance, int nCMdShow);
void InitDircet3D(HINSTANCE hinstance);
void Destory();
WPARAM Running();
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wPARAM, LPARAM Lparam);

//scene
void InitScene();
void DestoryScene();
void Update();
void Render();





