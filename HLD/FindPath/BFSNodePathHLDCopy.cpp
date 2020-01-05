#include"stdafx.h"
#include"BFSNodePathHLDCopy.h"
#define Inf 99999999
#define costStraight 10 
#define costDiagnoal 15

BFSNodePathHLDCopy::BFSNodePathHLDCopy(D3DXVECTOR2 position,D3DXVECTOR2 rectSize, D3DXVECTOR2 size, D3DXCOLOR color )
	:NodeHLDCopy(position, rectSize,size, color),startX(0), startY(0), bWallCheck(false)
{
	NodeHLDCopy(position, rectSize, size, color);
	monsterPos = position;
	wstring shaderFile = Shaders + L"Rect.fx";
	float positionX;
	float positionY;
	positionX = -480.0f;
	positionY = -431.0f;
	for (UINT y = 0; y < HeightNode; y++)
	{

		//positionX = rect->Position().x;
		positionY = positionY + 1.0f* 34.48f;//*y;
		//positionY = rect->Position().y;
		for (UINT x = 0; x < WidthNode; x++)
		{
			//	float positionXx = x * rectSize.x - Width * 0.5f; //사각형 사이즈 넣어줘야함
			//	float positionYy = y * rectSize.y - Height;


			nodes[y][x].first = D3DXVECTOR2(positionX, positionY);//.push_back(D3DXVECTOR2(positionX, positionY));
			nodes[y][x].second.start = false;
			nodes[y][x].second.goal = false;
			nodes[y][x].second.wall = false;
			nodes[y][x].second.f = Inf;
			nodes[y][x].second.g = Inf;
			nodes[y][x].second.h = Inf;
			nodes[y][x].second.close = false;
			nodes[y][x].second.parent.x = Inf;
			nodes[y][x].second.parent.y = Inf;
			positionX = positionX + 1.0f*64.0f;

		}
		positionX = -480.0f;
	}



	/*
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			float positionX = x * size.Fx - Width * 0.5f;
			float positionY = y * size.y - Height*0.5;

			nodes[y][x].first = new Rect(shaderFile, D3DXVECTOR2(positionX, positionY), size);
			nodes[y][x].second.start = false;
			nodes[y][x].second.goal = false;
			nodes[y][x].second.wall = false;
			nodes[y][x].second.f = Inf;
			nodes[y][x].second.g = Inf;
			nodes[y][x].second.h = Inf;
			nodes[y][x].second.close = false;
			nodes[y][x].second.parent.x = Inf;
			nodes[y][x].second.parent.y = Inf;

		}
	}*/
	SetStart(monsterPos);

}

BFSNodePathHLDCopy::~BFSNodePathHLDCopy()
{
	
}

void BFSNodePathHLDCopy::SetBFSPosition(vector<pair<D3DXVECTOR2, tagNodes>> Pos)
{

	for(int i=0;i<Pos.size();i++){
	   posCheck.push_back(Pos[i].first);
	}
	
}

vector<D3DXVECTOR2> BFSNodePathHLDCopy::GetBFSPosition()
{
	vector<D3DXVECTOR2>tmpPos;

	tmpPos = posCheck;
	for (int i = 0; i < posCheck.size(); i++) {
		posCheck.pop_back();
	}
	posCheck.clear();
	return tmpPos;
}

void BFSNodePathHLDCopy::BFSNode(D3DXVECTOR2 playerPos, D3DXVECTOR2 monsterPos, int indexX, int indexY)
{



	srand(time(NULL));
	               if(getPos.size()>0){
	             for (int i = 0; i < getPos.size(); i++) {
			            	getPos.pop_back();
			           }
				   }
			//getPos.clear();
				
				getPos.push_back(nodes[indexX + 1][indexY + 1]);//0

				getPos.push_back(nodes[indexX + 1][indexY]);//1
				if(indexY -1>=0){
			       getPos.push_back(nodes[indexX + 1][indexY - 1]);//2
				
				    getPos.push_back(nodes[indexX][indexY - 1]);//3
				}
				if(indexY - 1 >= 0&& indexX - 1 >= 0){
					getPos.push_back(nodes[indexX - 1][indexY - 1]);//4
				}
					if (indexX - 1 >= 0) {
					getPos.push_back(nodes[indexX - 1][indexY]);//5

					getPos.push_back(nodes[indexX - 1][indexY + 1]);//6
				}
				getPos.push_back(nodes[indexX][indexY + 1]);//7

				
	

				//Wall check
				for (int i = 0; i < getPos.size(); i++) {
					if (getPos[i].second.wall == true)
					{
						getPos.erase(getPos.begin() + i);
					}

				}
			
				//간곳인지 check
				/*
				for (int i = 0; i < savePos.size(); i++) {
					for (int j = 0; j < getPos.size(); j++) {
						if (getPos[j].first->Position() == savePos[i].first->Position()) {
							//getPos.erase(getPos.begin() + i);
						}
					}
				}*/
				//갈려고하는장소들 저장
				//for (int i = 0; i < getPos.size(); i++) {

				//	savePos.push_back(getPos[i]);
				//}
				//랜덤
				int rn;
				
				pair<D3DXVECTOR2, tagNodes> tmp;
				for (int i = 0; i < getPos.size(); i++) {
					
					    rn = rand() % (getPos.size() - i) + i;
						tmp =getPos[i];
						getPos[i] = getPos[rn];
						getPos[rn] = tmp;
					
				}
				
				SetBFSPosition(getPos);
				for (int i = 0; i < getPos.size(); i++) {
					posCheck.push_back(getPos[i].first);//.first->Position());

				}

}

void BFSNodePathHLDCopy::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	
	
	if(bWallCheck&&Mouse->Down(0)){
	     SetWall();
	}
	BFSNode(playerPos, monsterPos,startX, startY);
	


}

void BFSNodePathHLDCopy::Render()
{

	NodeHLDCopy::Render();
	/*
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			//시작점 : 노랑
			if (nodes[y][x].second.start == true)
			{
				nodes[y][x].first->Color(1, 1, 0);
			}

			//목적지 : 초록
			else if (nodes[y][x].second.goal == true)
			{
				nodes[y][x].first->Color(0, 1, 0);
			}

			//벽 : 빨강
			else if (nodes[y][x].second.wall == true)
			{
				nodes[y][x].first->Color(1, 0, 0);
			}

			//닫힘 : 파랑
			else if (nodes[y][x].second.close == true)
			{
				nodes[y][x].first->Color(0, 0, 1);
			}
		}
	}

	

	

	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			nodes[y][x].first->Render();
		}
	}
	*/
}

bool BFSNodePathHLDCopy::PtInRect(D3DXVECTOR2 rectPose, D3DXVECTOR2 target)
{
	float xScale = 64.0f*0.5f;//rect->scale.x*0.5f;
	float yScale = 34.8f*0.5f;//rect->scale.y*0.5f;

	float left = rectPose.x - xScale;    // rect->position.x - xScale;
	float right = rectPose.x + xScale; //rect->position.x + xScale;
	float bottom = rectPose.y - yScale; //rect->position.y - yScale;
	float top = rectPose.y + yScale; //rect->position.y + yScale;

	bool bCheck = true;


	bCheck &= target.x > left;
	bCheck &= target.x < right;
	bCheck &= target.y > bottom;
	bCheck &= target.y < top;
	

	return bCheck;
}

void BFSNodePathHLDCopy::SetStart(D3DXVECTOR2 pos)
{
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (PtInRect(nodes[y][x].first, pos))
			{
				nodes[y][x].second.start = true;
				nodes[y][x].second.g = 0;
				startX = x;
				startY = y;
			}
			else
			{
				nodes[y][x].second.start = false;
			}
		}
	}
}

void BFSNodePathHLDCopy::SetGoal()
{
}

void BFSNodePathHLDCopy::SetWall()
{
	//ptMouse = ;
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (PtInRect(nodes[y][x].first, ptMouse))
			{
				nodes[y][x].second.wall = true;
			}
		}
	}

}

void BFSNodePathHLDCopy::FindPath()
{
}

void BFSNodePathHLDCopy::SetRoad()
{


	POINT min;
	int count2 = 0;
	for (UINT y = 0; y < HeightNode; y++)
	{
		for (UINT x = 0; x < WidthNode; x++)
		{
			if (nodes[y][x].second.f &&
				nodes[y][x].second.wall == false &&
				nodes[y][x].second.close == false)
			{
				min.x = x;
				min.y = y;
				break;
			}
			count2++;
		}
	}

}
