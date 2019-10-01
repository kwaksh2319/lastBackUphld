#pragma once

class Sprite
{
private:
	Shader* shader;
	Shader* boundShader;
	ID3D11Buffer* vertexBuffer; //buffer
	ID3D11Buffer* BoundvertexBuffer;//box buffer

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;
	D3DXVECTOR2 textureSize;

	wstring textureFile; //씌울 이미지 파일
	ID3D11ShaderResourceView* srv;

	D3DXMATRIX world;

	bool bDrawBound;
	bool bDrawCollision;



private:
	struct Vertex
	{
		D3DXVECTOR3 Position;
		D3DXVECTOR2 Uv;
	};

	struct BoundVertex //box
	{
		D3DXVECTOR3 Position;
	};


private:
	static float lA[4];
	static float lB[4];
	static float l[4];
	static bool lCheck[4];

	static float dr1;
	static float dr2;

private:
	
	void Initialize(wstring spriteFile, wstring shaderFile, float startX, float startY, float endX, float endY);
	void CreateBound();

public:
	Sprite(wstring textureFile, wstring shaderFile);
	Sprite(wstring textureFile, wstring shaderFile, float endX, float endY);
	Sprite(wstring textureFile, wstring shaderFile, float startX, float startY, float endX, float endY);
	virtual ~Sprite();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	void DrawBound(bool val) { bDrawBound = val; }
	void DrawCollision(bool val) { bDrawCollision = val; }
	bool Aabb(D3DXVECTOR2 position); //자신의 aabb
	bool Aabb(Sprite*b);
	bool Obb(Sprite* b);



	static bool Aabb(Sprite* sprite, D3DXVECTOR2 position);
	static bool Aabb(Sprite*a, Sprite*b);
	static bool Obb(Sprite* a ,Sprite*b);
private:
	
	struct ObbDesc {
		D3DXVECTOR2 Position;
		D3DXVECTOR2 Direction[2];//[0] 수평 [1]수직
		float Length[2];// 물체 내 충돌 허용길이
	};
	//충돌체크 시작할 위치 world 회전 length 충돌 허용범위 
	static void CreateObb(OUT ObbDesc* out, D3DXVECTOR2 position, D3DXMATRIX& world, D3DXVECTOR2& length);
	static float SeperateAxis(D3DXVECTOR2& seperate, D3DXVECTOR2& e1, D3DXVECTOR2& e2);
	static bool CheckObb(ObbDesc &obbA, ObbDesc &obbB);
	


public:
	void Position(float x, float y);
	void Position(D3DXVECTOR2& vec);
	D3DXVECTOR2 Position() { return position; }

	void Scale(float x, float y);
	void Scale(D3DXVECTOR2& vec);
	D3DXVECTOR2 Scale() { return scale; }

	void Rotation(float x, float y, float z);
	void Rotation(D3DXVECTOR3& vec);
	D3DXVECTOR3 Rotation() { return rotation; }

	void RotationDegree(float x, float y, float z);
	void RotationDegree(D3DXVECTOR3& vec);
	D3DXVECTOR3 RotationDegree();

	D3DXVECTOR2 TextureSize() { return textureSize; }

};


///////////////////////////////////////////////////////////////////////////////

class Sprites
{
private:
	friend class Sprite;

private:
	static ID3D11ShaderResourceView* Load(wstring file);
	static void Remove(wstring file);

private:
	struct SpriteDesc
	{
		UINT RefCount = 0;
		ID3D11ShaderResourceView* SRV = NULL;
	};

	static map<wstring, SpriteDesc> spriteMap;
	static int a;
};