#pragma once
class Game
{
public:
	Game();
	~Game();

public:
	void Init(HWND hwnd);
	void Update();
	void Render();

private:

	// Shader Resource View
	void CreateRasterizerState();
	void CreateSamplerState();
	void CreateBlendState();
	void CreateSRV();

private:
	HWND _hwnd;
	shared_ptr<Graphics> _graphics;

private:
	
	// RTV ( Render Target View )
	// 후면버퍼에 그려달라고 요청할 때 사용하는 변수.
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	// Misc 
	// 화면의 크기를 묘사.
	D3D11_VIEWPORT _viewport = { 0 };
	float _clearColor[4] = { 0.f, 0.f, 0.f, 0.f };

private:

	// Geometry
	shared_ptr<Geometry<VertexTextureData>> _geometry;
	shared_ptr<VertexBuffer> _vertexBuffer;
	shared_ptr<IndexBuffer> _indexBuffer;
	shared_ptr<InputLayout> _inputLayout;

	// VS
	shared_ptr<VertexShader> _vertexShader;

	// RS
	ComPtr<ID3D11RasterizerState> _rasterizerState = nullptr;

	// PS
	shared_ptr<PixelShader> _pixelShader;

	// SRV
	shared_ptr<Texture> _texture;

	ComPtr<ID3D11SamplerState> _samplerState = nullptr;
	ComPtr<ID3D11BlendState> _blendState = nullptr;

private:

	//SRT
	TransformData _transformData;
	shared_ptr<ConstantBuffer<TransformData>> _constantBuffer;

	Vec3 _localPosition = { 0.f, 0.f, 0.f };
	Vec3 _localRotation = { 0.f, 0.f, 0.f };
	Vec3 _localScale = { 1.f, 1.f, 1.f };
 };

