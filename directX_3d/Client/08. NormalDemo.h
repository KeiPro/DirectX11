#pragma once
#include "IExecute.h"
#include "Geometry.h"

class NormalDemo : public IExecute
{
public:
	void Init() override;
	void Update() override;
	void Render() override;


	shared_ptr<Shader> _shader;

	shared_ptr<Geometry<VertexTextureNormalData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	Matrix _world = Matrix::Identity;

	shared_ptr<Texture> _texture;

	// Camera
	shared_ptr<GameObject> _camera;

	Vec3 _lightDir = Vec3(0.f, 0.f, 1.f);
};
