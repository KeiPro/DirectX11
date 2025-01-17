#pragma once
#include "Geometry.h"

class GeometryHelper
{
public:
	static void CreateQuad(shared_ptr<Geometry<VertexColorData>> geometry, Color color);

	static void CreateQuad(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateCube(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateSphere(shared_ptr<Geometry<VertexTextureData>> geometry);
	static void CreateGrid(shared_ptr<Geometry<VertexTextureData>> geometry, int32 sizeX, int32 sizeZ);
};

