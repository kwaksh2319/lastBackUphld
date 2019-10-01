#pragma once
#include"stdafx.h"
#include"./Viewer/Camera.h"
struct SceneValues {
	class Camera* MainCamera;
	D3DXMATRIX Projection;


};
class Scene {

protected:
	SceneValues *values;
public:
	Scene(SceneValues* values) { this->values = values; }
	~Scene(){}

	virtual void Update() = 0;
	virtual void Render() = 0;

};