#ifndef SCENE_H
#define SCENE_H

#include "StandardIncludes.h"
#include "Mesh.h"
#include "Camera.h"
#include "Application.h"

class Scene
{
public:
	Scene();
	Scene(Camera _camera);
	virtual ~Scene();

	virtual void ProcessInput(float _dt);
	void Render();

	void AddMesh(Mesh* _mesh);
	void AddShader(Shader* _shader);

protected:
	std::vector<Mesh*>   m_meshes;
	std::vector<Shader*> m_shaders;
	Camera m_camera;
};

#endif // !SCENE_H

