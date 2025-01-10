#include "pch.h"
#include "Mesh.h"

Mesh::Mesh(ComPtr<ID3D11Device> device) 
	: Super(ResourceType::Mesh), _device(device)
{
}

Mesh::~Mesh()
{
}

void Mesh::CreateDefaultRectangle()
{
	_geometry = make_shared<Geometry<VertexTextureData>>();
	GeometryHelper::CreateRectangle(_geometry);
	// 위의 정보들을 토대로 gpu의 vram에 만들어주는 과정.
	_vertexBuffer = make_shared<VertexBuffer>(_device);
	_vertexBuffer->Create(_geometry->GetVertices());
	_indexBuffer = make_shared<IndexBuffer>(_device);
	_indexBuffer->Create(_geometry->GetIndices());
}
