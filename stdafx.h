#pragma once

//Window
#include <Windows.h>
#include <assert.h>
#include <time.h>

//STL
#include <vector>
#include <string>
#include <map>
#include <functional>
using namespace std;

//DirectX
#include <d3d11.h>
#include <D3DX11.h>
#include <D3DX10.h>
#include <D3DX10math.h>
#include <d3dx11effect.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "d3dx10.lib")

#pragma comment(lib, "effects11d.lib")
#pragma comment(lib, "d3dcompiler.lib")

//ImGui
#include <imgui.h>
#include <imguiDx11.h>
#pragma comment(lib, "imgui.lib")

//DirectWrite
#include<d2d1_2.h>
#include<dwrite.h>
#pragma comment(lib,"d2d1.lib")
#pragma comment(lib,"dwrite.lib")

//Fmod
#include"./FMOD/fmod.hpp"
#pragma comment(lib,"./FMOD/fmodex_vc.lib")

//Framework
#include "./System/Keyboard.h"
#include"./System/CMouse.h"
#include"./System/Time.h"
#include"./System/Dwrite.h"
#include"./System/SoundManager.h"
#include"./System/FileManger.h"



#include "./Render/Shader.h"
#include"./Render/Rect.h"
#include "./Utility/String.h"
#include"./Utility/Math.h"
#include"./Utility/BinaryFile.h"
#include"./Utility/Path.h"
#include"./Utility/Xml.h"


#include "./Render/Sprite.h"
#include"./Render/Clip.h"
#include"./Render/Animation.h"

//Macro
#define SAFE_RELEASE(p) { if(p) {(p)->Release(); (p) = nullptr; }}
#define SAFE_DELETE(p) { if(p) {delete (p); (p) = nullptr; }}
#define SAFE_DELETE_ARRAY(p) { if(p) {delete[] (p); (p) = nullptr; }}

//Global
extern UINT Width ;
extern UINT Height;

const wstring Textures = L"./_Textures/";
const wstring Shaders = L"./_Shader2D/";

extern HWND Hwnd;
extern wstring Title;

//DX Interfaces
extern IDXGISwapChain* SwapChain;
extern ID3D11Device* Device;
extern ID3D11DeviceContext* DeviceContext;
extern ID3D11RenderTargetView* RTV;


extern Keyboard* Key;
extern CMouse* Mouse;