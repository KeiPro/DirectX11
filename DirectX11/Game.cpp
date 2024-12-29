#include "pch.h"
#include "Game.h"

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init(HWND hwnd)
{
	_hwnd = hwnd;

	_graphics = make_shared<Graphics>(hwnd);
	_vertexBuffer = make_shared<VertexBuffer>(_graphics->GetDevice());
	_indexBuffer = make_shared<IndexBuffer>(_graphics->GetDevice());
	_inputLayout = make_shared<InputLayout>(_graphics->GetDevice());
	_geometry = make_shared<Geometry<VertexTextureData>>();
	_vertexShader = make_shared<VertexShader>(_graphics->GetDevice());
	_pixelShader = make_shared<PixelShader>(_graphics->GetDevice());
	_constantBuffer = make_shared<ConstantBuffer<TransformData>>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	_texture = make_shared<Texture>(_graphics->GetDevice());
	_rasterizerState = make_shared<RasterizerState>(_graphics->GetDevice());
	_samplerState = make_shared<SamplerState>(_graphics->GetDevice());
	_blendState = make_shared<BlendState>(_graphics->GetDevice());

	// 삼각형의 기하학 도형을 만듦.
	// Vertex Data
	GeometryHelper::CreateRectangle(_geometry);
	_vertexBuffer->Create(_geometry->GetVertices());
	_indexBuffer->Create(_geometry->GetIndices());

	_vertexShader->Create(L"Default.hlsl", "VS", "vs_5_0");
	_inputLayout->Create(VertexTextureData::descs, _vertexShader->GetBlob());
	_pixelShader->Create(L"Default.hlsl", "PS", "ps_5_0");

	_rasterizerState->Create();
	_samplerState->Create();
	_blendState->Create();
	
	_texture->Create(L"character2.png");

	_constantBuffer->Create();
}

void Game::Update()
{
	// Scale Rotation Translation	

	_localPosition.x += 0.001f;

	Matrix matScale = Matrix::CreateScale(_localScale / 3);
	Matrix matRotation = Matrix::CreateRotationX(_localRotation.x);
	matRotation *= Matrix::CreateRotationY(_localRotation.y);
	matRotation *= Matrix::CreateRotationZ(_localRotation.z);
	Matrix matTranslation = Matrix::CreateTranslation(_localPosition);

	Matrix matWorld = matScale * matRotation * matTranslation; // SRT
	_transformData.matWorld = matWorld;

	_constantBuffer->CopyData(_transformData);
}

void Game::Render()
{
	_graphics->RenderBegin();

	// IA - VS - RS - PS - OM
	{
		uint32 stride = sizeof(VertexTextureData);
		uint32 offset = 0;

		auto _deviceContext = _graphics->GetDeviceContext();

		// IA
		_deviceContext->IASetVertexBuffers(0, 1, _vertexBuffer->GetComPtr().GetAddressOf(), &stride, &offset);
		_deviceContext->IASetIndexBuffer(_indexBuffer->GetComPtr().Get(), DXGI_FORMAT_R32_UINT, 0);
		_deviceContext->IASetInputLayout(_inputLayout->GetComPtr().Get());
		_deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// VS
		_deviceContext->VSSetShader(_vertexShader->GetComPtr().Get(), nullptr, 0);
		_deviceContext->VSSetConstantBuffers(0, 1, _constantBuffer->GetComPtr().GetAddressOf());

		// RS
		_deviceContext->RSSetState(_rasterizerState->GetComPtr().Get());

		// PS
		_deviceContext->PSSetShader(_pixelShader->GetComPtr().Get(), nullptr, 0);
		_deviceContext->PSSetShaderResources(0, 1, _texture->GetComPtr().GetAddressOf());
		_deviceContext->PSSetSamplers(0, 1, _samplerState->GetComPtr().GetAddressOf());
		
		// OM
		_deviceContext->OMSetBlendState(_blendState->GetComPtr().Get(), _blendState->GetBlendFactor(), 0xFFFFFFFF);

		//_deviceContext->Draw(_vertices.size(), 0);
		_deviceContext->DrawIndexed(_geometry->GetIndexCount(), 0, 0);
	}

	_graphics->RenderEnd();
}