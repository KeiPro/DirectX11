#pragma once
class Graphics
{
public:
	Graphics(HWND hwnd);
	~Graphics();

	void RenderBegin();
	void RenderEnd();

	ComPtr<ID3D11Device> GetDevice() { return _device; }
	ComPtr<ID3D11DeviceContext> GetDeviceContext() { return _deviceContext; }

private:
	void CreateDeviceAndSwapChain();
	void CreateRenderTargetView();
	void SetViewport();

private:
	HWND _hwnd;
	uint32 _width = 0;
	uint32 _height = 0;

private:
	// Device & SwapChain
	ComPtr<ID3D11Device> _device;
	ComPtr<ID3D11DeviceContext> _deviceContext; // 리소스와 렌더링 파이프라인을 묶어주는 역할.
	ComPtr<IDXGISwapChain> _swapChain; // 더블 버퍼링과 관련된 변수. // 전면 버퍼와 후면버퍼.

	// RTV ( Render Target View )
	// 후면버퍼에 그려달라고 요청할 때 사용하는 변수.
	ComPtr<ID3D11RenderTargetView> _renderTargetView;

	// Misc 
	// 화면의 크기를 묘사.
	D3D11_VIEWPORT _viewport = { 0 };
	float _clearColor[4] = { 0.f, 0.f, 0.f, 0.f };
};

