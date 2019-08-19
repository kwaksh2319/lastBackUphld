#include"stdafx.h"
#include"Device.h"

void BufferCreateFirst(); //ori buffer create
void BufferCreateRandomFirst();//first random location buffer create
void BufferCreateRandomSecond();//second random location buffer create
void Render_Buffer_location(ID3D11Buffer*vertexBuffertmp); //first random location and second random location buffer  render 

static bool bCheckFirst=true;
static bool bCheckSecond=true;

ID3D11Buffer* vertexBuffer;
ID3D11Buffer* vertexBuffer_Random_location_first;
ID3D11Buffer* vertexBuffer_Random_location_second;

ID3D11InputLayout* inputLayout;



D3D11_INPUT_ELEMENT_DESC layoutDesc[] = {
	{
	"POSITION",
	0,
	DXGI_FORMAT_R32G32B32_FLOAT,
	0,
	0,
	D3D11_INPUT_PER_VERTEX_DATA,
	0
	},
     {//Size 
    "COLOR",
	  0,
	   DXGI_FORMAT_R32G32B32_FLOAT,
	   0,
	   12,  
	   D3D11_INPUT_PER_VERTEX_DATA,
	   0

      }
};

struct Vertex {
	D3DXVECTOR3 Position;
	D3DXCOLOR Color;

};
struct BoxCollistion_Boundary_Position {
	D3DXVECTOR3 Position;
};
//AABB Collision function
//bool AABB_Collision(Vertex moveBox, Vertex stopBox, float  randomLocation_size);
bool AABB_Collision_first(Vertex moveBox, Vertex stopBox, float  randomLocation_size,bool bCheck);
bool AABB_Collision_second(Vertex moveBox, Vertex stopBox, float  randomLocation_size,bool bCheck);
bool AABB_Collision_size_first(Vertex* moveBox, Vertex* stopBox,bool bCheck);
bool AABB_Collision_size_second(Vertex* moveBox, Vertex* stopBox,bool bCheck);
//bool AABB_Collision(Vertex* moveBox, Vertex* stopBox);
//bool AABB_Collision(BoxCollistion_Boundary_Position  moveBoxLeftDown, BoxCollistion_Boundary_Position  stopBoxUpRight);
//center point get function
Vertex CaculaotorBoxCenterPosition(Vertex vertexP1, Vertex vertexP2);

//distance calculator function
float Distance_caculator(Vertex moveBox, Vertex stopBox);

//draw origianl box vertices
Vertex vertices[6];

//draw random box vertices
Vertex vertices_random_first[6];
Vertex vertices_random_second[6];

//draw origianl  box vertices center
Vertex vertices_center_move;

//draw random  box vertices center
Vertex vertices_center_stop_firstBox;
Vertex vertices_center_stop_secondBox;


//three box boundary position
BoxCollistion_Boundary_Position origianlBox_Up_Right;
BoxCollistion_Boundary_Position firstRandomBox_Up_Right;
BoxCollistion_Boundary_Position secondRandomBox_Up_Right;
BoxCollistion_Boundary_Position origianlBox_Left_Down;
BoxCollistion_Boundary_Position firstRandomBox_Left_Down;
BoxCollistion_Boundary_Position secondRandomBox_Left_Down;
float randomLocation_first_size;
float randomLocation_second_size;
float randomLocation_first_x;
float randomLocation_first_y;
float randomLocation_second_x;
float randomLocation_second_y;
float first_randomFlag_X ;//vertices flag
float first_randomFlag_Y ;//vertices flag

float second_randomFlag_X;//vertices flag
float second_randomFlag_Y ;//vertices flag
void InitScene() {
	//Vertex position setting
	
	
	//Vertex vertices[6];
	//original first vertices
	
	first_randomFlag_X = rand() % 2;//vertices flag
	first_randomFlag_Y = rand() % 2;//vertices flag

	 second_randomFlag_X = rand() % 2;//vertices flag
	 second_randomFlag_Y = rand() % 2;//vertices flag

	if (first_randomFlag_X == 1) {
		first_randomFlag_X = 1.0f;
	}
	else if (first_randomFlag_X == 0) {
		first_randomFlag_X = -1.0f;
	}

	
	if (first_randomFlag_Y == 1) {
		first_randomFlag_Y = 1.0f;
	}
	else if (first_randomFlag_Y == 0) {
		first_randomFlag_Y = -1.0f;
	}


	if (second_randomFlag_X == 1) {
		second_randomFlag_X = 1.0f;
	}
	else if (second_randomFlag_X == 0) {
		second_randomFlag_X = -1.0f;
	}


	if (second_randomFlag_Y == 1) {
		second_randomFlag_Y = 1.0f;
	}
	else if (second_randomFlag_Y == 0) {
		second_randomFlag_Y = -1.0f;
	}
	
	randomLocation_first_x = (rand() % 10 + 10)*0.03*first_randomFlag_X; //first vertice X random
	randomLocation_first_y =( rand() % 10 + 10 )* 0.03*first_randomFlag_Y; //first vertice Y random
	randomLocation_first_size = (rand() % 10 +1) * 0.05;//first vertice size to vertices
	
	randomLocation_second_x = (rand() % 10 + 30) * 0.01*second_randomFlag_X;//second vertice X random
	randomLocation_second_y = (rand() % 10 +30)* 0.01*second_randomFlag_Y;//second vertice Y random
    randomLocation_second_size= (rand() % 10 +1)* 0.03;//second vertice size to vertices
	
	





	vertices[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertices[1].Position = D3DXVECTOR3(0.0f, +0.1f, 0.0f);
	vertices[2].Position = D3DXVECTOR3(+0.1f, 0.0f, 0.0f);

	vertices[3].Position = D3DXVECTOR3(+0.1f, 0.0f, 0.0f);
	vertices[4].Position = D3DXVECTOR3(0.0f, +0.1f, 0.0f);
	vertices[5].Position = D3DXVECTOR3(+0.1f, +0.1f, 0.0f);

	//random location first vertices
	vertices_random_first[0].Position = D3DXVECTOR3(randomLocation_first_x, randomLocation_first_y, 0.0f);
	vertices_random_first[1].Position = D3DXVECTOR3(randomLocation_first_x, randomLocation_first_y+ randomLocation_first_size, 0.0f);
	vertices_random_first[2].Position = D3DXVECTOR3(randomLocation_first_x+ randomLocation_first_size, randomLocation_first_y, 0.0f);

	vertices_random_first[3].Position = D3DXVECTOR3(randomLocation_first_x + randomLocation_first_size, randomLocation_first_y, 0.0f);
	vertices_random_first[4].Position = D3DXVECTOR3(randomLocation_first_x, randomLocation_first_y + randomLocation_first_size, 0.0f);
	vertices_random_first[5].Position = D3DXVECTOR3(randomLocation_first_x + randomLocation_first_size, randomLocation_first_y + randomLocation_first_size, 0.0f);


	//random location second vertices
	vertices_random_second[0].Position = D3DXVECTOR3(randomLocation_second_x, randomLocation_second_y, 0.0f);
	vertices_random_second[1].Position = D3DXVECTOR3(randomLocation_second_x, randomLocation_second_y + randomLocation_second_size, 0.0f);
	vertices_random_second[2].Position = D3DXVECTOR3(randomLocation_second_x + randomLocation_second_size, randomLocation_second_y, 0.0f);

	vertices_random_second[3].Position = D3DXVECTOR3(randomLocation_second_x + randomLocation_second_size, randomLocation_second_y, 0.0f);
	vertices_random_second[4].Position = D3DXVECTOR3(randomLocation_second_x, randomLocation_second_y + randomLocation_second_size, 0.0f);
	vertices_random_second[5].Position = D3DXVECTOR3(randomLocation_second_x + randomLocation_second_size, randomLocation_second_y + randomLocation_second_size, 0.0f);
	
	//cube draw verices
	//Vertex vertices[17];
	
	//color setting star
	vertices[0].Color = D3DXCOLOR(1, 0, 0, 1);
	vertices[1].Color = D3DXCOLOR(0, 1, 0, 1);
	vertices[2].Color = D3DXCOLOR(1, 0, 0, 1);

	vertices[3].Color = D3DXCOLOR(0, 0, 1, 1);
	vertices[4].Color = D3DXCOLOR(0, 1, 0, 1);
	vertices[5].Color = D3DXCOLOR(1, 0, 0, 1);


	vertices_random_first[0].Color = D3DXCOLOR(1, 0, 0, 1);
	vertices_random_first[1].Color = D3DXCOLOR(0, 1, 0, 1);
	vertices_random_first[2].Color = D3DXCOLOR(1, 0, 0, 1);

	vertices_random_first[3].Color = D3DXCOLOR(0, 0, 1, 1);
	vertices_random_first[4].Color = D3DXCOLOR(0, 1, 0, 1);
	vertices_random_first[5].Color = D3DXCOLOR(1, 0, 0, 1);



	vertices_random_second[0].Color = D3DXCOLOR(1, 0, 0, 1);
	vertices_random_second[1].Color = D3DXCOLOR(0, 1, 0, 1);
	vertices_random_second[2].Color = D3DXCOLOR(1, 0, 0, 1);

	vertices_random_second[3].Color = D3DXCOLOR(0, 0, 1, 1);
	vertices_random_second[4].Color = D3DXCOLOR(0, 1, 0, 1);
	vertices_random_second[5].Color = D3DXCOLOR(1, 0, 0, 1);
	
	{


		//center

		vertices_center_move=CaculaotorBoxCenterPosition(vertices[1], vertices[2]);
		vertices_center_stop_firstBox = CaculaotorBoxCenterPosition(vertices_random_first[1], vertices_random_first[2]);
		vertices_center_stop_secondBox = CaculaotorBoxCenterPosition(vertices_random_second[1], vertices_random_second[2]);


	}

	{//calculator 
		
		origianlBox_Up_Right.Position.x = vertices_center_move.Position.x+ 0.05f;
		origianlBox_Up_Right.Position.y = vertices_center_move.Position.y+ 0.05f;

		firstRandomBox_Up_Right.Position.x = vertices_center_stop_firstBox.Position.x+ randomLocation_first_size/2;
		firstRandomBox_Up_Right.Position.y = vertices_center_stop_firstBox.Position.y+ randomLocation_first_size/2;

		secondRandomBox_Up_Right.Position.x = vertices_center_stop_secondBox.Position.x + randomLocation_second_size/2;
		secondRandomBox_Up_Right.Position.y = vertices_center_stop_secondBox.Position.y+ randomLocation_second_size/2;

		origianlBox_Left_Down.Position.x = vertices_center_move.Position.x - 0.05f;
		origianlBox_Left_Down.Position.y = vertices_center_move.Position.y- 0.05f;

		firstRandomBox_Left_Down.Position.x = vertices_center_stop_firstBox.Position.x- randomLocation_first_size/2;
		firstRandomBox_Left_Down.Position.y = vertices_center_stop_firstBox.Position.y- randomLocation_first_size/2;

		secondRandomBox_Left_Down.Position.x = vertices_center_stop_secondBox.Position.x- randomLocation_second_size/2;
		secondRandomBox_Left_Down.Position.y = vertices_center_stop_secondBox.Position.y- randomLocation_second_size/2;
	}

	
	
	//create vertexBuffer
	{   //buffer size
		//D3D11_BUFFER_DESC desc;
		//ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
		//desc.Usage = D3D11_USAGE_DEFAULT;
		//
		//desc.ByteWidth = sizeof(Vertex) * 6;//draw star
		//desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//용도
		//
  //     //data vertices 
		//
		//D3D11_SUBRESOURCE_DATA data;
		//ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
		//data.pSysMem = vertices;
		//
		//HRESULT hr =Device->CreateBuffer(&desc, &data, &vertexBuffer);
		//assert(SUCCEEDED(hr));
		BufferCreateFirst();
		BufferCreateRandomFirst();
		BufferCreateRandomSecond();
	
	}

	//create layout
	{
		HRESULT hr = Device->CreateInputLayout(
			layoutDesc,
			ARRAYSIZE(layoutDesc),
			VsBlob->GetBufferPointer(),
			VsBlob->GetBufferSize(),
			&inputLayout
		);

		assert(SUCCEEDED(hr));
		

	}

}

void DestoryScene() {
	inputLayout->Release();
	vertexBuffer->Release();
	//random location buffer release
	vertexBuffer_Random_location_first->Release();
	vertexBuffer_Random_location_second->Release();

	
}

void Update() {
	if (key->Press('A') == true){
		vertices[0].Position.x -= 0.0001f;
	    vertices[1].Position.x -= 0.0001f;
		vertices[2].Position.x -= 0.0001f;

		vertices[3].Position.x -= 0.0001f;
		vertices[4].Position.x -= 0.0001f;
		vertices[5].Position.x -= 0.0001f;

	}
	else if (key->Press('D') == true){
		vertices[0].Position.x += 0.0001f;
		vertices[1].Position.x += 0.0001f;
		vertices[2].Position.x += 0.0001f;

		vertices[3].Position.x += 0.0001f;
		vertices[4].Position.x += 0.0001f;
		vertices[5].Position.x += 0.0001f;

	}
	else if (key->Press('W') == true){
		vertices[0].Position.y += 0.0001f;
		vertices[1].Position.y += 0.0001f;
		vertices[2].Position.y += 0.0001f;

		vertices[3].Position.y += 0.0001f;
		vertices[4].Position.y += 0.0001f;
		vertices[5].Position.y += 0.0001f;


	}
	else if (key->Press('S') == true){
		vertices[0].Position.y -= 0.0001f;
		vertices[1].Position.y -= 0.0001f;
		vertices[2].Position.y -= 0.0001f;

		vertices[3].Position.y -= 0.0001f;
		vertices[4].Position.y -= 0.0001f;
		vertices[5].Position.y -= 0.0001f;

	
		

	}
	
	vertices_center_move = CaculaotorBoxCenterPosition(vertices[1], vertices[2]);
	vertices_center_stop_firstBox = CaculaotorBoxCenterPosition(vertices_random_first[1], vertices_random_first[2]);
	vertices_center_stop_secondBox = CaculaotorBoxCenterPosition(vertices_random_second[1], vertices_random_second[2]);

	//bCheckSecond = AABB_Collision_size_second(vertices, vertices_random_second, bCheckSecond);
	//bCheckFirst = AABB_Collision_size_first(vertices, vertices_random_first,bCheckFirst);

	bCheckSecond = AABB_Collision_second(vertices_center_move, vertices_center_stop_secondBox, randomLocation_second_size, bCheckSecond);
	bCheckFirst = AABB_Collision_first(vertices_center_move, vertices_center_stop_firstBox, randomLocation_first_size,bCheckFirst);
	
	

	if(bCheckFirst==false && bCheckSecond == false){
	


		randomLocation_first_x = (rand() % 10 + 10)*0.03*first_randomFlag_X; //first vertice X random
		randomLocation_first_y = (rand() % 10 + 10)* 0.03*first_randomFlag_Y; //first vertice Y random
		randomLocation_first_size = (rand() % 10 + 1) * 0.05;//first vertice size to vertices

		randomLocation_second_x = (rand() % 10 + 30) * 0.01*second_randomFlag_X;//second vertice X random
		randomLocation_second_y = (rand() % 10 + 30)* 0.01*second_randomFlag_Y;//second vertice Y random
		randomLocation_second_size = (rand() % 10 + 1)* 0.03;//second vertice size to vertices







		vertices[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		vertices[1].Position = D3DXVECTOR3(0.0f, +0.1f, 0.0f);
		vertices[2].Position = D3DXVECTOR3(+0.1f, 0.0f, 0.0f);

		vertices[3].Position = D3DXVECTOR3(+0.1f, 0.0f, 0.0f);
		vertices[4].Position = D3DXVECTOR3(0.0f, +0.1f, 0.0f);
		vertices[5].Position = D3DXVECTOR3(+0.1f, +0.1f, 0.0f);

		//random location first vertices
		vertices_random_first[0].Position = D3DXVECTOR3(randomLocation_first_x, randomLocation_first_y, 0.0f);
		vertices_random_first[1].Position = D3DXVECTOR3(randomLocation_first_x, randomLocation_first_y + randomLocation_first_size, 0.0f);
		vertices_random_first[2].Position = D3DXVECTOR3(randomLocation_first_x + randomLocation_first_size, randomLocation_first_y, 0.0f);

		vertices_random_first[3].Position = D3DXVECTOR3(randomLocation_first_x + randomLocation_first_size, randomLocation_first_y, 0.0f);
		vertices_random_first[4].Position = D3DXVECTOR3(randomLocation_first_x, randomLocation_first_y + randomLocation_first_size, 0.0f);
		vertices_random_first[5].Position = D3DXVECTOR3(randomLocation_first_x + randomLocation_first_size, randomLocation_first_y + randomLocation_first_size, 0.0f);


		//random location second vertices
		vertices_random_second[0].Position = D3DXVECTOR3(randomLocation_second_x, randomLocation_second_y, 0.0f);
		vertices_random_second[1].Position = D3DXVECTOR3(randomLocation_second_x, randomLocation_second_y + randomLocation_second_size, 0.0f);
		vertices_random_second[2].Position = D3DXVECTOR3(randomLocation_second_x + randomLocation_second_size, randomLocation_second_y, 0.0f);

		vertices_random_second[3].Position = D3DXVECTOR3(randomLocation_second_x + randomLocation_second_size, randomLocation_second_y, 0.0f);
		vertices_random_second[4].Position = D3DXVECTOR3(randomLocation_second_x, randomLocation_second_y + randomLocation_second_size, 0.0f);
		vertices_random_second[5].Position = D3DXVECTOR3(randomLocation_second_x + randomLocation_second_size, randomLocation_second_y + randomLocation_second_size, 0.0f);


	   bCheckSecond = true;
	   bCheckFirst = true;
	
	}
	

	

	DeviceContext->UpdateSubresource(
	   vertexBuffer,0,NULL,vertices,sizeof(Vertex)*6,0
	);

	DeviceContext->UpdateSubresource(
		vertexBuffer_Random_location_first, 0, NULL, vertices_random_first, sizeof(Vertex) * 6, 0
	);
	
	DeviceContext->UpdateSubresource(
		vertexBuffer_Random_location_second, 0, NULL, vertices_random_second, sizeof(Vertex) * 6, 0
	);
}

void Render() {

	D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	//function 
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{//draw 

		UINT stride = sizeof(Vertex);//
		UINT offset = 0;
		DeviceContext->IASetVertexBuffers(0,1,&vertexBuffer,&stride,&offset);
		//DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);//정점 연결을 어떻게 그릴래
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DeviceContext->IASetInputLayout(inputLayout);
		//DeviceContext->Draw(17, 0);//갯수 draw cube
		//aabb
		//bool bCheck = AABB_Collision(vertices, vertices_random_first);
		
		//bool bCheck = AABB_Collision(origianlBox_Left_Down, firstRandomBox_Up_Right);
		DeviceContext->Draw(6, 0);//갯수 draw star
		
		if (bCheckFirst == true) {

			Render_Buffer_location(vertexBuffer_Random_location_first);
		}

		if (bCheckSecond == true) {
			Render_Buffer_location(vertexBuffer_Random_location_second);
		}
		
		
	}
	SwapChain->Present(0, 0);

}

void BufferCreateFirst(){

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;

	desc.ByteWidth = sizeof(Vertex) * 6;//draw star
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//용도

   //data vertices 

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices; //buffer input to vertices

	HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
	assert(SUCCEEDED(hr));
}

void BufferCreateRandomFirst() {

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;

	desc.ByteWidth = sizeof(Vertex) * 6;//draw star
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//용도

   //data vertices 

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices_random_first; //buffer input to vertices

	HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer_Random_location_first);
	assert(SUCCEEDED(hr));
}

void BufferCreateRandomSecond() {

	D3D11_BUFFER_DESC desc;
	ZeroMemory(&desc, sizeof(D3D11_BUFFER_DESC));
	desc.Usage = D3D11_USAGE_DEFAULT;

	desc.ByteWidth = sizeof(Vertex) * 6;//draw star
	desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;//용도

   //data vertices 

	D3D11_SUBRESOURCE_DATA data;
	ZeroMemory(&data, sizeof(D3D11_SUBRESOURCE_DATA));
	data.pSysMem = vertices_random_second; //buffer input to vertices

	HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer_Random_location_second);
	assert(SUCCEEDED(hr));
}
void Render_Buffer_location(ID3D11Buffer* vertexBuffertmp) { //random loaction buffer draw function 

	//D3DXCOLOR bgColor = D3DXCOLOR(0, 0, 0, 1);
	//function 
	//DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{//draw 

		UINT stride = sizeof(Vertex);//
		UINT offset = 0;
		DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffertmp, &stride, &offset);
		//DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);//정점 연결을 어떻게 그릴래
		DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		DeviceContext->IASetInputLayout(inputLayout);
		//DeviceContext->Draw(17, 0);//갯수 draw cube

		DeviceContext->Draw(6, 0);//갯수 draw star

	}
	//SwapChain->Present(0, 0);


}
Vertex CaculaotorBoxCenterPosition(Vertex vertexP1, Vertex vertexP2)
{
	Vertex returnVertex;

	returnVertex.Position.x = (vertexP1.Position.x + vertexP2.Position.x) / 2;
	returnVertex.Position.y = (vertexP1.Position.y + vertexP2.Position.y) / 2;

	return returnVertex;
}

bool AABB_Collision_first(Vertex moveBox, Vertex stopBox,float  randomLocation_size, bool bCheck) {
	//bool bChecksub = true;
	float distance_center_to_center;
	distance_center_to_center = Distance_caculator(moveBox, stopBox);//calculator center to center distance

	if (distance_center_to_center <= 0.05 + randomLocation_size/2) {
		bCheck= false;
	}
	
	
	
	//bCheck &= distance_center_to_center <= r2.left;
	//bCheck &= distance_center_to_center >= r2.bottom;
	//bCheck &= distance_center_to_center >= r2.top;




	return  bCheck;
}
bool AABB_Collision_second(Vertex moveBox, Vertex stopBox, float  randomLocation_size,bool bCheck) {
	//static bool bCheck = true;
	
	float distance_center_to_center;
	distance_center_to_center = Distance_caculator(moveBox, stopBox);//calculator center to center distance

	if (distance_center_to_center <= 0.05 + randomLocation_size / 2) {
		bCheck = false;
	}
	


	//bCheck &= distance_center_to_center <= r2.left;
	//bCheck &= distance_center_to_center >= r2.bottom;
	//bCheck &= distance_center_to_center >= r2.top;




	return  bCheck;
}
/*
bool AABB_Collision_size_first(Vertex* moveBox, Vertex* stopBox,bool bCheck)
{   
	

	bCheck &= moveBox[5].Position.x >= stopBox[0].Position.x && moveBox[5].Position.x <= stopBox[2].Position.x;
	bCheck &= moveBox[5].Position.y >= stopBox[0].Position.y && moveBox[5].Position.y <= stopBox[2].Position.y;

	bCheck &= moveBox[0].Position.x <= stopBox[0].Position.x && moveBox[5].Position.x >= stopBox[0].Position.x;
	bCheck &= moveBox[0].Position.y <= stopBox[0].Position.y && moveBox[5].Position.y <= stopBox[2].Position.y;
	return bCheck;
}

bool AABB_Collision_size_second(Vertex* moveBox, Vertex* stopBox, bool bCheck)
{
	bCheck &= moveBox[5].Position.x >= stopBox[0].Position.x && moveBox[5].Position.x <= stopBox[2].Position.x;
	bCheck &= moveBox[5].Position.y >= stopBox[0].Position.y && moveBox[5].Position.y <= stopBox[2].Position.y;

	bCheck &= moveBox[0].Position.x <= stopBox[0].Position.x && moveBox[5].Position.x >= stopBox[0].Position.x;
	bCheck &= moveBox[0].Position.y <= stopBox[0].Position.y && moveBox[5].Position.y <= stopBox[2].Position.y;
	
	return bCheck;
}
*/
float Distance_caculator(Vertex moveBox, Vertex stopBox) {

	float distance_center_to_center;

	distance_center_to_center = sqrt(powf(moveBox.Position.x - stopBox.Position.x, 2) + powf(moveBox.Position.y - stopBox.Position.y, 2));
	
	return distance_center_to_center;
}
/*
bool AABB_Collision(Vertex* moveBox, Vertex* stopBox) {
	bool bCheck = true;
	
	


	return  bCheck;
}*/
/*
bool AABB_Collision(BoxCollistion_Boundary_Position  moveBoxLeftDown, BoxCollistion_Boundary_Position   stopBoxUpRight) {
	bool bCheck = true;



	bCheck &= moveBoxLeftDown.Position.x <= stopBoxUpRight.Position.x&&moveBoxLeftDown.Position.y <= stopBoxUpRight.Position.y;









	return  bCheck;
}*/