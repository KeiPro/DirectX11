#include "pch.h"
#include "CameraScript.h"
#include "Transform.h"

void CameraScript::Start()
{
}

void CameraScript::Update()
{
	float dt = TIME->GetDeltaTime();

	Vec3 pos = GetTransform()->GetPosition();

	if (INPUT->GetButton(KEY_TYPE::W))
	{
		pos += GetTransform()->GetLook() * _speed * dt;
	}

	if (INPUT->GetButton(KEY_TYPE::S))
	{
		pos -= GetTransform()->GetLook() * _speed * dt;
	}

	if (INPUT->GetButton(KEY_TYPE::A))
	{
		pos -= GetTransform()->GetRight() * _speed * dt;
	}

	if (INPUT->GetButton(KEY_TYPE::D))
	{
		pos += GetTransform()->GetRight() * _speed * dt;
	}

	GetTransform()->SetPosition(pos);
}
