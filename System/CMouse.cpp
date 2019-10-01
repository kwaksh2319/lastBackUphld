#include "stdafx.h"
#include "CMouse.h"

CMouse::CMouse(HWND handle)
	:handle(handle), position(0, 0)
	, wheelValue(0), wheelPrevValue(0), wheelMoveValue(0)
{
	ZeroMemory(buttonStatus, sizeof(short) * 8);
	ZeroMemory(buttonPrevStatus, sizeof(short) * 8);
	ZeroMemory(buttonMap, sizeof(Button) * 8);

	ZeroMemory(buttonCount, sizeof(int) * 8); //몇번 눌렸냐.


	doubleClickTime = GetDoubleClickTime(); //OS에 설정된 더블클릭 타임을 읽어오는 함수
	startDoubleClickTime[0] = GetTickCount(); //OS가 부팅되고 현재까지 시간을 ms단위로 기록

	for (int i = 1; i < 8; i++)//0번은 넣었으니까 제외
		startDoubleClickTime[i] = startDoubleClickTime[0]; //GetTickCount가 들어 있음
}

CMouse::~CMouse()
{
}

void CMouse::WndProc(UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	if (iMessage == WM_MOUSEMOVE)
	{
		position.x = (float)LOWORD(lParam);
		position.y = (float)HIWORD(lParam);
	}

	if (iMessage == WM_MOUSEWHEEL)
	{
		short temp = (short)HIWORD(wParam); //wparam!

		wheelPrevValue = wheelValue; //최초 0 + 0
		wheelValue += (float)temp; //wParam 만큼 증가->스크롤 만큼 증감
	}
}

void CMouse::Update()
{
	memcpy(buttonPrevStatus, buttonStatus, sizeof(byte) * 8); //현재의 버튼 상태[8](업,다운,프레스 등) 배열을 통째로 이전 상태로 복사

	ZeroMemory(buttonStatus, sizeof(byte) * 8);
	ZeroMemory(buttonMap, sizeof(byte) * 8);

	buttonStatus[0] = GetAsyncKeyState(VK_LBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[1] = GetAsyncKeyState(VK_RBUTTON) & 0x8000 ? 1 : 0;
	buttonStatus[2] = GetAsyncKeyState(VK_MBUTTON) & 0x8000 ? 1 : 0;	//사실 그 외에 버튼이 더 있지만..

	for (UINT i = 0; i < 8; i++) //버튼맵 8개
	{
		short prevStatus = buttonPrevStatus[i]; //버튼의 이전 상태(업,다운..)을 지역 변수에 담아서
		short currentStatus = buttonStatus[i]; //현재 눌린 버튼을 current에 저장

		if (prevStatus == 0 && currentStatus == 1)
			buttonMap[i] = Button::Down;
		else if (prevStatus == 1 && currentStatus == 0)
			buttonMap[i] = Button::Up;
		else if (prevStatus == 1 && currentStatus == 1)
			buttonMap[i] = Button::Press;
		else
			buttonMap[i] = Button::None;
	}

	//더블클릭
	UINT buttonStatus = GetTickCount();
	for (UINT i = 0; i < 8; i++)
	{
		if (buttonMap[i] == Button::Down) //(3)특정 버튼이 눌린적이 있다면
		{
			if (buttonCount[i] == 1) //1번 눌린 경우
			{
				//더블클릭 안됨(넘 늦게 눌러서) : 해석 - 두번째 누른 타임스탬프 - 첫번째 누른 타임 스탭트 > 더블클릭 허용시간 
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime)
					buttonCount[i] = 0; //누른 회수를 0으로 다시 초기화
			}

			buttonCount[i]++; //(1)현재 다운 상태기 때문에 1번 누른 상태로 증가시켜준다.

			if (buttonCount[i] == 1)
				startDoubleClickTime[i] = buttonStatus; //(2)현재 버튼을 누른 시간을 지정
		}

		if (buttonMap[i] == Button::Up)
		{
			//뗐을 때 다시 확인(더블 클릭은 dowon->up->down 과정이므로 up에서도 검사 수행)
			if (buttonCount[i] == 1)
			{
				//더블클릭 실패(시간 초과)
				if (buttonStatus - startDoubleClickTime[i] >= doubleClickTime)
					buttonCount[i] = 0;
			}
			//up시간 기준
			else if (buttonCount[i] == 2) //두번 눌렀는지
			{

				if (buttonStatus - startDoubleClickTime[i] <= doubleClickTime)//더블클릭 성립
					buttonMap[i] = Button::DoubleClick;

				buttonCount[i] = 0; //다시 누른 회수를 0으로
			}
		}
	}

	POINT point;
	GetCursorPos(&point);//마우스의 위치(OS상의..)
	ScreenToClient(handle, &point);//우리 화면에 반영

	wheelPrevValue = wheelValue;
	wheelMoveValue = wheelValue - wheelPrevValue;
}
