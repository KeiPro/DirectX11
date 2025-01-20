#include "pch.h"
#include "10. GlobalTestDemo.h"
#include "GeometryHelper.h"
#include "Camera.h"
#include "CameraScript.h"
#include "MeshRenderer.h"

void GlobalTestDemo::Init()
{	
	auto shader = make_shared<Shader>(L"08. GlobalTest.fx");

	// Camera
	_camera = make_shared<GameObject>();
	_camera->GetOrAddTransform();
	_camera->AddComponent(make_shared<Camera>());
	_camera->AddComponent(make_shared<CameraScript>());
	_camera->GetTransform()->SetPosition(Vec3(0.0f, 5.0f, 0.0f));
	_camera->GetTransform()->SetRotation(Vec3(25.0f, 0.0f, 0.0f));


	// Object
	_obj = make_shared<GameObject>();
	_obj->GetOrAddTransform();
	_obj->AddComponent(make_shared<MeshRenderer>());
	{
		_obj->GetMeshRenderer()->SetShader(shader);
	}
	{
		RESOURCES->Init();
		auto mesh = RESOURCES->Get<Mesh>(L"Sphere");
		_obj->GetMeshRenderer()->SetMesh(mesh);
	}
	{
		auto texture = RESOURCES->Load<Texture>(L"Orianna", L"..\\Resources\\Textures\\orianna.jpg");
		_obj->GetMeshRenderer()->SetTexture(texture);
	}
}

void GlobalTestDemo::Update()
{
	_camera->Update();
	_obj->Update();
}

void GlobalTestDemo::Render()
{
}
