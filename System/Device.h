#pragma once

//Init Function
void InitWindow(HINSTANCE hInstance, int nCmdShow);
void InitDirect3D(HINSTANCE hInstance);
void Destroy();
WPARAM Running();
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

//Scene
void InitScene();
void Destroy();
void Update();
void Render();

void CreateBackBuffer();
void DeleteBackBuffer();