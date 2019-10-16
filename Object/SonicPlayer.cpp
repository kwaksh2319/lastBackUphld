#include "stdafx.h"
#include "SonicPlayer.h"

#define MAX_SPEED 800.0f
#define MAX_ROLL_SPEED 3000.0f
#define MOVE_SPEED 0.0f
#define ACCEL_SPEED 200.0f

SonicPlayer::SonicPlayer(D3DXVECTOR2 position, D3DXVECTOR2 scale)
	:moveSpeed(MOVE_SPEED), focusOffset(-500, -400), state(PlayerState::IDLE)
	, accel(ACCEL_SPEED), rollSpeed(0.0f), direction(true)
	, gravity(-10.0f), velocity(0.0f), bGround(true)
	, bLeftCollision(false), bRightCollision(false), bTopCollision(false), bBottomCollision(false)
	, degree(0, 0, 0), position(position), scale(scale)
{
	player = new Animation;
	wstring spriteFile = Textures + L"./Sonic/ssonic.png";
	wstring shaderFile = Shaders + L"Effect.fx";

	Clip* clip;

	//Idle(0 ~ 1)
	{
		clip = new Clip(PlayMode::END);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 2, 37, 30, 78), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 28, 37, 58, 78), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 55, 37, 86, 78), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 83, 37, 117, 78), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 115, 37, 147, 78), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 147, 37, 181, 78), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 178, 37, 213, 78), 0.3f);
		player->AddClip(clip);

		//idle2
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 93, 427, 119, 466), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 123, 426, 148, 465), 0.3f);
		player->AddClip(clip);
	}

	//Run(2 ~ 3)
	{
		//Normal Run
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 4, 80, 32, 119), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 36, 80, 62, 119), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 65, 80, 96, 119), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 96, 80, 135, 119), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 134, 80, 166, 119), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 170, 80, 202, 119), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 208, 80, 230, 119), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 236, 80, 263, 119), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 266, 80, 293, 119), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 293, 80, 331, 119), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 332, 80, 366, 119), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 368, 80, 400, 119), 0.1f);
		player->AddClip(clip);

		//Fast Run
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 72, 238, 102, 274), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 111, 238, 140, 274), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 149, 238, 178, 274), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 185, 238, 218, 274), 0.1f);
		player->AddClip(clip);
	}

	//Sit Down(4)
	{
		clip = new Clip(PlayMode::END);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 267, 43, 295, 76), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 299, 50, 331, 76), 0.3f);
		player->AddClip(clip);
	}

	//Roll(5)[Turbo]
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 71, 282, 111, 318), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 282, 164, 318), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 171, 282, 211, 318), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 216, 282, 259, 318), 0.1f);

		player->AddClip(clip);
	}

	//Jump or Roll이 끝난후(6)
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 1, 169, 31, 200), 0.02f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 34, 169, 62, 200), 0.02f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 67, 169, 99, 200), 0.02f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 130, 169, 161, 200), 0.02f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 192, 169, 223, 200), 0.02f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 228, 169, 260, 200), 0.02f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 264, 169, 300, 200), 0.02f);

		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 205, 31, 233), 0.02f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 34, 205, 67, 233), 0.02f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 69, 205, 100, 233), 0.02f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 105, 205, 133, 233), 0.02f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 139, 205, 167, 233), 0.02f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 173, 205, 203, 233), 0.02f);

		player->AddClip(clip);
	}

	//Push(7)
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 8, 436, 37, 472), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 48, 435, 72, 472), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 80, 436, 108, 472), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 120, 435, 144, 472), 0.3f);
		player->AddClip(clip);
	}

	player->Position(position);
	player->Scale(scale);
	player->Play(static_cast<int>(state));

	player->DrawBound(true);

}

SonicPlayer::~SonicPlayer()
{
	SAFE_DELETE(player);
}

float pressKeyTime = 0.0f; //키가 눌린 시간
void SonicPlayer::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	textureSize.x = player->Scale().x * player->TextureSize().x;
	textureSize.y = player->Scale().y *player->TextureSize().y;

	//업데이트 된 위치 정보를 각 변수에 저장
	{
		topVector.x = position.x;
		topVector.y = position.y + textureSize.y * 0.5f+40;

		bottomVector.x = position.x;
		bottomVector.y = position.y - textureSize.y * 0.5f - 40;

		rightVector.x = position.x + textureSize.x  ;
		rightVector.y = position.y ;

		rightBottomVector.x = position.x + textureSize.x * 0.5f;
		rightBottomVector.y = position.y - textureSize.y * 0.5f;

		leftVector.x = position.x - textureSize.x  ;
		leftVector.y = position.y;



	}
	
	//속도가 0이면
	if (moveSpeed == 0.0f)
	{
		if (state != PlayerState::IDLE_LIE_DOWN &&
			state != PlayerState::TURBO &&
			bGround)
		{
			state = PlayerState::IDLE;
			if (player->GetCurrentClip() == 0 &&
				player->GetClip()->EndFrame())
				state = PlayerState::IDLE_LIE_DOWN;
		}
	}

	this->position.x += moveSpeed * Time::Delta();

	//라인 위에 있을 때

	if (bGround && bLineBottomCollision)
	{
		slope = (lineRightPoint.y - lineLeftPoint.y) / (lineRightPoint.x - lineLeftPoint.x);
	
		position.y = slope * (position.x - lineLeftPoint.x) + lineLeftPoint.y + (textureSize.y*0.5f);
	    
	}
	else
	{
		bGround = false;
	}

	//y축 가속도 업데이트
	velocity += gravity * Time::Delta();

	//이동키
	if (Key->Press('A') && !bLeftCollision )
	{
		
		
		MoveLeft();
		if (bLineBottomCollision)
		{
			
			degree.z = Math::ToDegree(slope);
		}
		else
			degree.z = 0.0f;
	}
	else if (Key->Press('D') &&
		!bRightCollision)
	{
		
		MoveRight();
		if (bLineBottomCollision)
		{
			degree.z = Math::ToDegree(slope);
		}
		else
			degree.z = 0.0f;
	}

	else if (Key->Press('S') && moveSpeed == 0.0f)
	{
		SitDown();
	}

	else
	{
		//감속
		if (moveSpeed > 0.0f)
			moveSpeed -= accel * 10 * Time::Delta();
		else if (moveSpeed < 0.0f)
			moveSpeed += accel * 10 * Time::Delta();

		//정지
		if (moveSpeed < 10.0f && moveSpeed > -10.0f)
			moveSpeed = 0.0f;
	}

	//앉았다 일어날 때
	if (Key->Up('S'))
	{
		if (rollSpeed != 0.0f)
			state = PlayerState::ROLL;
		moveSpeed = rollSpeed;
		rollSpeed = 0.0f;
	}

	//점프
	if (bGround == false)
	{
		position.y += velocity;
	}

	if (bLineBottomCollision)
	{

		velocity = 0.0f;

		bGround = true;

	}

	if (Key->Press(VK_SPACE) &&
		state != PlayerState::TURBO)
	{
		if (bGround == true)
		{
			velocity = 2.5f;
			bGround = false;
			state = PlayerState::ROLL;
		}
	}

	else if (Key->Up(VK_SPACE))
	{
		if (velocity > 0.25f)
			velocity = 0.25f;
	}

	if (Key->Up('A'))
		pressKeyTime = 0.0f;
	if (Key->Up('D'))
		pressKeyTime = 0.0f;
	//bLeftCollision = true;
	
	
	if ((bLeftCollision || bRightCollision ) && moveSpeed != 0.0f) {
		
		state = PlayerState::PUSH;
		//slope = (lineRightPoint.x - lineLeftPoint.x)/ (lineRightPoint.y - lineLeftPoint.y)  ;
		if(bRightCollision){
			slope_Right = (lineRightPoint_Right.y - lineLeftPoint_Right.y) / (lineRightPoint_Right.x - lineLeftPoint_Right.x);
			if (slope_Right<=0) {
				moveSpeed *= -1;
				//degree.z = Math::ToDegree(3.141592);
			
			position.y = slope_Right * (position.x - lineLeftPoint_Right.x) + lineLeftPoint_Right.y + (textureSize.y*0.5f);
			}
			//position.x = slope * (position.y - lineRightPoint.y) + lineRightPoint.x-(textureSize.x*0.5f) ; //; //+ ;
		//bRightCollision = false;
		}
		if (bLeftCollision) {
			slope_Left = (lineRightPoint_Left.y - lineLeftPoint_Left.y) / (lineRightPoint_Left.x - lineLeftPoint_Left.x);
			if (slope_Left <= 0) {
				moveSpeed *= -1;
				//degree.z = Math::ToDegree(3.141592);

				position.y = slope_Left * (position.x - lineLeftPoint_Left.x) + lineLeftPoint_Left.y + (textureSize.y*0.5f);
			}
		//	position.x = lineLeftPoint.x - (textureSize.x*0.5f); // lineRightPoint.x + (textureSize.x); //slope * (position.y - lineLeftPoint.y) +
			//bLeftCollision = false;
		}
		//gravity = 0.0f;
		//moveSpeed = 0.0f;
		

	}

	
	if (bTopCollision&& moveSpeed != 0.0f) {
		state = PlayerState::PUSH;
		slope_Top = (lineRightPoint_Top.y - lineLeftPoint_Top.y) / (lineRightPoint_Top.x - lineLeftPoint_Top.x);
		//if (slope_Top <= 0) {
			//degree.x = Math::ToDegree(slope_Top*-1);
		//moveSpeed *= -1;
		//accel *= -1;
		//slope_Top * (position.x - lineLeftPoint_Top.x)+
		//}
	//	if (slope_Top <= 0&& bRightCollision) {
			position.y = slope_Top * (position.x - lineLeftPoint_Top.x) + lineLeftPoint_Top.y + (textureSize.y*0.5f);
		//}
		//	slope = (lineRightPoint.y - lineLeftPoint.y) / (lineRightPoint.x - lineLeftPoint.x);
		//slope = Math::ToRadian(100);
		//position.y = slope * (position.x - lineLeftPoint.x) + lineLeftPoint.y + (textureSize.y*0.5f);
	//}
	}

	player->Play(static_cast<UINT>(state));
	player->Position(position);
	
	player->RotationDegree(degree);
	player->Update(V, P);

}

void SonicPlayer::Render()
{
	
	ImGui::Separator();
	ImGui::LabelText("Roll Speed", "%0.2f", rollSpeed);
	ImGui::LabelText("Move Speed", "%0.2f", moveSpeed);
	ImGui::LabelText("Sonic State", "%d", state);
	ImGui::LabelText("Sonic Position", "%0.2f, %0.2f", position.x, position.y);
	ImGui::LabelText("On Ground", "%d", bGround ? 1 : 0);
	ImGui::LabelText("bRightCollision", "%d", bRightCollision ? 1 : 0);
	ImGui::LabelText("bLeftCollision", "%d", bLeftCollision ? 1 : 0);
	ImGui::LabelText("bTopCollision", "%d", bTopCollision ? 1 : 0);
	player->Render();
}

void SonicPlayer::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = player->Position() - focusOffset;
	*size = D3DXVECTOR2(1, 1);
}

Sprite * SonicPlayer::GetSprite()
{
	return player->GetSprite();
}

void SonicPlayer::MoveLeft()
{
	direction = false;

	pressKeyTime += Time::Delta();

	if (moveSpeed > -MAX_SPEED)
		moveSpeed -= accel * Time::Delta();
	else
		moveSpeed = -MAX_SPEED;

	//미끄럼 방지
	if (moveSpeed > 0.0f)
		moveSpeed -= accel * 5.0f * Time::Delta();

	//방향키가 눌린 시간에 따라 달리는 모션 바꾸기
	if (moveSpeed < -300.0f &&
		((state != PlayerState::ROLL && state != PlayerState::PUSH) || bGround))
	{
		state = PlayerState::FAST_RUN;
	}
	else if ((state != PlayerState::ROLL &&state != PlayerState::PUSH) || bGround) {
		state = PlayerState::NORMAL_RUN;
	}

	degree.y = 180.0f;
}

void SonicPlayer::MoveRight()
{
	direction = true;
	pressKeyTime += Time::Delta();

	if (moveSpeed < MAX_SPEED)
		moveSpeed += accel * Time::Delta();
	else
		moveSpeed = MAX_SPEED;

	
	//미끄럼 방지
	if (moveSpeed < 0.0f)
		moveSpeed += accel * 5.0f * Time::Delta();

	//방향키가 눌린 시간에 따라 달리는 모션 바꾸기
	if (moveSpeed > 300.0f &&
		((state != PlayerState::ROLL && state != PlayerState::PUSH)|| bGround))
		state = PlayerState::FAST_RUN;

	else if ((state != PlayerState::ROLL &&state != PlayerState::PUSH) || bGround)
		state = PlayerState::NORMAL_RUN;

	

	degree.y = 0.0f;
}

void SonicPlayer::SitDown()
{
	if (state != PlayerState::TURBO)
		state = PlayerState::SIT_DOWN;
	if (Key->Press(VK_SPACE))
	{
		state = PlayerState::TURBO;

		if (direction && rollSpeed< MAX_ROLL_SPEED)
			rollSpeed += accel * 20 * Time::Delta();
		else if (direction == false && rollSpeed > -MAX_ROLL_SPEED )
			rollSpeed -= accel * 20 * Time::Delta();
	}
}

void SonicPlayer::Scale(D3DXVECTOR2 vec)
{
	player->Scale(vec);
}
