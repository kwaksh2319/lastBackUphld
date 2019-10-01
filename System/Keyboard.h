#pragma once
#include <bitset>
/*
bool type을 갖는 자료구조
set() : bit를 모두 1로 설정
reset() : bit를 모두 0으로 설정
set(i, value) : i번째 값을 value로 설정
[] 배열 형태로 접근 가능 ex) bit[10] = false;
flip() : bit값을 1<->0
all() : 모든 bit가 1일 때 true 반환
none() : 모든 bit 0일 때 true 반환
any() : 1개라도 1이면 true 반환
count() : 값이 1로 세팅된 비트의 개수 반환
*/

#define KEYMAX 256

class Keyboard
{
private:
	//키가 눌렸을 때 true, 안눌리면 false
	bitset<KEYMAX> up; // bool up[KEYMAX]
	bitset<KEYMAX> down;

public:
	Keyboard();
	~Keyboard();

	bool Down(int key);
	bool Up(int key);
	bool Press(int key);
	bool Toggle(int key);

};