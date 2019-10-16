#pragma once
#include "./Viewer/IFollow.h"

enum class PlayerState
{
	IDLE = 0,
	IDLE_LIE_DOWN,
	NORMAL_RUN,
	FAST_RUN,
	SIT_DOWN,
	TURBO,
	ROLL,
	PUSH
};

class SonicPlayer : public IFollowing
{
private:
	Animation* player;
	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;

	D3DXVECTOR2 bottomVector, topVector,leftVector;
	D3DXVECTOR2 rightVector, rightBottomVector;
	D3DXVECTOR2 lineLeftPoint;
	D3DXVECTOR2 lineRightPoint;

	D3DXVECTOR2 lineLeftPoint_Right;
	D3DXVECTOR2 lineRightPoint_Right;
	D3DXVECTOR2 lineLeftPoint_Left;
	D3DXVECTOR2 lineRightPoint_Left;
	D3DXVECTOR2 lineLeftPoint_Top;
	D3DXVECTOR2 lineRightPoint_Top;

	D3DXVECTOR2 focusOffset;
	D3DXVECTOR2 textureSize;

	PlayerState state;

	float moveSpeed;
	float rollSpeed;

	float accel; //x축 가속도
	float velocity; //y축 가속도
	float gravity;

	bool bGround;
	bool direction; //true : 오른쪽, false : 왼쪽
	bool bLeftCollision, bRightCollision;
	bool bTopCollision, bBottomCollision;

	bool bLineBottomCollision, bLineTopCollision,bLineRightCollision;

	D3DXVECTOR3 degree;
	float slope; //경사
	float slope_Right; //경사
	float slope_Left;
	float slope_Top;
public:
	SonicPlayer(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~SonicPlayer();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;
	Sprite* GetSprite();

public:
	//키 조작 함수
	void MoveLeft();
	void MoveRight();
	void SitDown();

public:
	//get, set
	void Position(D3DXVECTOR2 vec) { position = vec; }
	D3DXVECTOR2 Position() { return position; }

	void Scale(D3DXVECTOR2 vec);
	D3DXVECTOR2 TextureSize() { return textureSize; }

	D3DXVECTOR2 TopVector() { return topVector; }
	D3DXVECTOR2 BottomVector() { return bottomVector; }
	D3DXVECTOR2 RightVector() { return rightVector; }
	D3DXVECTOR2 LeftVector() { return leftVector; }
	D3DXVECTOR2 RBVector() { return rightBottomVector; }

	void LeftCollision(bool val) { bLeftCollision = val; }
	void TopCollision(bool val) { bTopCollision = val; }
	void RightCollision(bool val) { bRightCollision = val; }
	void BottomCollision(bool val) { bBottomCollision = val; }

	void LineBottomCollision(bool val) { bLineBottomCollision = val; }
	void LineTopCollision(bool val) { bLineTopCollision = val; }
	//void LineRightCollision(bool val) { bRightCollision = val; }
	//void LineLeftCollision(bool val) { bLeftCollision = val; }

public:
	//라인 정보 get, set
	void LineLeftPoint(D3DXVECTOR2 val) { lineLeftPoint = val; }
	void LineRightPoint(D3DXVECTOR2 val) { lineRightPoint = val; }

	void LineLeftPoint_Right(D3DXVECTOR2 val) { lineLeftPoint_Right = val; }
	void LineRightPoint_Right(D3DXVECTOR2 val) { lineRightPoint_Right = val; }
	
	void LineLeftPoint_Left(D3DXVECTOR2 val) { lineLeftPoint_Left = val; }
	void LineRightPoint_Left(D3DXVECTOR2 val) { lineRightPoint_Left = val; }

	void LineLeftPoint_Top(D3DXVECTOR2 val) { lineLeftPoint_Top = val; }
	void LineRightPoint_Top(D3DXVECTOR2 val) { lineRightPoint_Top = val; }
};