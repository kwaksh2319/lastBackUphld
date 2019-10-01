#pragma once
class Camera {
private:
	D3DXMATRIX view;

protected:
	D3DXVECTOR2 position;//camera position

public:
	Camera();
	virtual ~Camera();
	D3DXMATRIX View() { return view; }
	D3DXVECTOR2 Position() { return position; }

	virtual void Update();



};