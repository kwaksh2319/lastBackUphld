#include"stdafx.h"
#include"Following.h"

Following::Following(IFollowing * focus)
	:focus(focus)
{
}

Following::~Following()
{
}

void Following::Change(IFollowing * focus)
{
	this->focus = focus;
}

void Following::Update()
{
	if (focus == NULL)
		return;
	//D3DXVECTOR2 location;//position 부모의 맴버변수랑 겹쳐서
	D3DXVECTOR2 location, size;
	
	//포커스는 누가들어올지 알수 없고 알필요 없음
    focus->Focus(&location, &size);

	//화면 중심으로 포커스
	D3DXVECTOR2 temp = location;
	temp.x -= (float)Width*0.5f;
	temp.y -= (float)Height*0.5f;

	temp.x += size.x*0.5f;
	temp.y += size.y*0.5f;//?

	position = temp;

	__super::Update();

}
 