#include "pch.h"
#include "15. EmissiveDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"
#include "MeshRenderer.h"

void EmissiveDemo::Init()
{	
	RESOURCES->Init();
	_shader = make_shared<Shader>(L"12. Lighting_Emissive.fx");
	
	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetPosition(Vec3(0.0f, 0.0f, -10.0f));

	// Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		_obj->GetMeshRenderer()->SetShader(_shader);
	}
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"Orianna", L"..\\Resources\\Textures\\orianna.jpg");
		_obj->GetMeshRenderer()->SetTexture(texture);
	}

	// Object2
	_obj2 = make_shared<GameObject>();
	_obj2->GetOrAddTransform()->SetPosition(Vec3{0.5, 0.f, 2.f});
	_obj2->AddComponent(make_shared<MeshRenderer>());
	{
		_obj2->GetMeshRenderer()->SetShader(_shader);
	}
	{
		auto mesh = RESOURCES->Get<Mesh>(L"Cube");
		_obj2->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"Orianna", L"..\\Resources\\Textures\\orianna.jpg");
		_obj2->GetMeshRenderer()->SetTexture(texture);
	}

	RENDER->Init(_shader);
}

void EmissiveDemo::Update()
{
	_camera->Update();
	RENDER->Update();

	{
		Vec4 materialEmissive(1.0f, 0.0f, 0.0f, 1.0f);
		_shader->GetVector("MaterialEmissive")->SetFloatVector((float*)&materialEmissive);
		_obj->Update();
	}

	{
		Vec4 materialEmissive(1.0, 0.0f, 0.0f, 1.0f);
		_shader->GetVector("MaterialEmissive")->SetFloatVector((float*)&materialEmissive);
		_obj2->Update();
	}
}

void EmissiveDemo::Render()
{
}
