#pragma once



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





