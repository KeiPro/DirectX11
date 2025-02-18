#pragma once

using VertexType = VertexTextureNormalTangentBlendData;

struct asBone
{
	string name;
	int32 index = -1;
	int32 parent = -1;
	Matrix transform;
};

struct asMesh
{
	string name;
	aiMesh* mesh;
	vector<VertexType> vertices;
	vector<uint32> indices;

	int32 boneIndex;
	string materialName;
};

struct asMaterial
{
	string name;
	Color ambient;
	Color diffuse;
	Color specular;
	Color emissive;
	string diffuseFile;
	string specularFile;
	string normalFile;
};

// Animation
struct asBlendWeight
{
	// index는 별 내용 없음. 그냥 0번 1번 2번 3번에 넣어주기 위한 temp변수.
	void Set(uint32 index, uint32 boneIndex, float weight)
	{
		float i = (float)boneIndex;
		float w = weight;

		switch (index)
		{
		case 0: indices.x = i; weights.x = w; break;
		case 1: indices.y = i; weights.y = w; break;
		case 2: indices.z = i; weights.z = w; break;
		case 3: indices.w = i; weights.w = w; break;
		}
	}

	// 어떠한 정점들에 영향을 받는지, 1번 2번 3번 4번에 영향을 받는다면
	// Vec4(1, 2, 3, 4) 이런 식으로 들어가게 된다.
	Vec4 indices = Vec4(0, 0, 0, 0);
	Vec4 weights = Vec4(0, 0, 0, 0); // 몇 번째 본에 몇 퍼센트 영향을 받을 것인지에 대한 변수.

};

struct asBoneWeights
{
	void AddWeights(uint32 boneIndex, float weight)
	{
		if (weight <= 0.0f)
			return;

		auto findIt = std::find_if(boneWeights.begin(), boneWeights.end(),
			[weight](const Pair& p) { return weight > p.second; });

		boneWeights.insert(findIt, Pair(boneIndex, weight));
	}

	asBlendWeight GetBlendWeights()
	{
		asBlendWeight blendWeight;

		for (uint32 i = 0; i < boneWeights.size(); i++)
		{
			if (i >= 4)
				break;

			blendWeight.Set(i, boneWeights[i].first, boneWeights[i].second);
		}

		return blendWeight;
	}

	void Normalize()
	{
		if (boneWeights.size() >= 4)
			boneWeights.resize(4);

		float totalWeight = 0.f;
		for (const auto& item : boneWeights)
		{
			totalWeight += item.second;
		}

		for (auto& item : boneWeights)
		{
			item.second /= totalWeight;
		}
	}

	using Pair = pair<int32, float>;
	vector<Pair> boneWeights;
};