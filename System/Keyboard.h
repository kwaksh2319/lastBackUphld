#pragma once
#include<bitset>
/* bool type 갖는 자료구조 
set():bit 르르 모두 1로 설정
reset():bit 를 모두 0으로 설정
set(i,value):i번째 값을 value 설정
[]배열 형태로 접근가능 bit[10]=false;
flip():bit값을 1<->0
all() 모든 bit 가 1일때 true
none() 모든 bit 0일때 true
any() 1개라도 1이면 true
count() 값이 1로 세팅된 비트이 개수 반환
*/
#define KEYMAX 256
class Keyboard {
private:
	//키가 눌릴때 true, 안눌리면 false
	bitset<KEYMAX> up; //bool up[256] 
	bitset<KEYMAX> down; 


public:
	Keyboard();
	~Keyboard();
	bool Down(int key);
	bool Up(int key);
	bool Press(int key);
	bool Toggle(int key);

};
