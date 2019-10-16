#pragma once

#define WidthNode 15
#define HeightNode 12

enum class NodeType { None, Start, Goal, Wall };

struct tagNode
{
	//node type
	bool start;
	bool goal;
	bool wall;

	//비용 계산
	float f;
	float g;
	float h;

	//검사
	bool close;
	D3DXVECTOR2 parent;
};

class Node
{
private:
	NodeType nodeType;
	Rect* rect;

	pair<Rect*, tagNode> nodes[HeightNode][WidthNode];

	D3DXCOLOR color;

	int startX, startY;
	int goalX, goalY;

	vector<POINT> way;

	//마우스
	D3DXVECTOR2 ptMouse;

	//플레이어, 몬스터 위치
	D3DXVECTOR2 startPos;
	D3DXVECTOR2 goalPos;

	//
	bool bReadyToMove;

private:
	void RenderText();

	void SetStart();
	void SetGoal();
	void SetWall();

	void FindPath();

public:
	Node(D3DXVECTOR2 position, D3DXVECTOR2 scale = D3DXVECTOR2(1, 1), D3DXCOLOR color = D3DXCOLOR(0xff555566));
	~Node();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	UINT FindH(int startY, int startX, int goalY, int goalX);
	void Reset();

	void GetMouseCursor(D3DXVECTOR2 ptMouse) { this->ptMouse = ptMouse; }

	void GetStartPos(D3DXVECTOR2 start) { startPos = start; }
	void GetGoalPos(D3DXVECTOR2 goal) { goalPos = goal; }

	void ReadyToStart(bool val) { bReadyToMove = val; }
	bool ReadyToStart() { return bReadyToMove; }

	D3DXVECTOR2 Position();

};