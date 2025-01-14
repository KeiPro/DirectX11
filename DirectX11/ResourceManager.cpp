#include "pch.h"
#include "ResourceManager.h"
#include "Texture.h"
#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Animation.h"
#include "InputLayout.h"
#include "ShaderBase.h"

ResourceManager::ResourceManager(ComPtr<ID3D11Device> device) : _device(device)
{
}

void ResourceManager::Init()
{
	CreateDefaultTexture();
	CreateDefaultMesh();
	CreateDefaultShader();
	CreateDefaultMaterial();
	CreateDefaultAnimation();
}

void ResourceManager::CreateDefaultTexture()
{
	{
		auto texture = make_shared<Texture>(_device);
		texture->SetName(L"character2");
		texture->Create(L"character2.png");
		Add(texture->GetName(), texture);
	}

	{
		auto texture = make_shared<Texture>(_device);
		texture->SetName(L"Snake");
		texture->Create(L"Snake.bmp");
		Add(texture->GetName(), texture);
	}

	//Get<Texture>(L"character2");
}

void ResourceManager::CreateDefaultMesh()
{
	shared_ptr<Mesh> mesh = make_shared<Mesh>(_device);
	mesh->SetName(L"Rectangle");
	mesh->CreateDefaultRectangle();
	Add(mesh->GetName(), mesh);
}

void ResourceManager::CreateDefaultShader()
{
	shared_ptr<VertexShader> vertexShader = make_shared<VertexShader>(_device);
	vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");
	// 위에서 만들어준 vertex shader에 넘기는 데이터가 어떻게 구성되어 있는지를 설정하는 부분.
	shared_ptr<InputLayout> inputLayout = make_shared<InputLayout>(_device);
	inputLayout->Create(VertexTextureData::descs, vertexShader->GetBlob());
	shared_ptr<PixelShader> pixelShader = make_shared<PixelShader>(_device);
	pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	shared_ptr<Shader> shader = make_shared<Shader>();
	shader->SetName(L"Default");
	shader->_vertexShader = vertexShader;
	shader->_inputLayout = inputLayout;
	shader->_pixelShader = pixelShader;
	Add(shader->GetName(), shader);
}

void ResourceManager::CreateDefaultMaterial()
{
	shared_ptr<Material> material = make_shared<Material>();
	material->SetName(L"Default");
	material->SetShader(Get<Shader>(L"Default"));
	material->SetTexture(Get<Texture>(L"character2"));
	Add(material->GetName(), material);
}

void ResourceManager::CreateDefaultAnimation()
{
	shared_ptr<Animation> animation = make_shared<Animation>();
	animation->SetName(L"SnakeAnim");
	animation->SetTexture(Get<Texture>(L"Snake"));
	animation->SetLoop(true);

	animation->AddKeyframe(Keyframe{ Vec2{0.0f, 0.0f}, Vec2{100.0f, 100.0f}, 0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{100.0f, 0.0f}, Vec2{100.0f, 100.0f}, 0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{200.0f, 0.0f}, Vec2{100.0f, 100.0f}, 0.1f });
	animation->AddKeyframe(Keyframe{ Vec2{300.0f, 0.0f}, Vec2{100.0f, 100.0f}, 0.1f });

	Add(animation->GetName(), animation);

	animation->Save(L"TestAnim.xml");

	shared_ptr<Animation> anim2 = make_shared<Animation>();

	anim2->Load(L"TestAnim.xml");
}
