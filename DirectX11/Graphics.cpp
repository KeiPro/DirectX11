#include "pch.h"
#include "Graphics.h"

Graphics::Graphics(HWND hwnd)
{
	_hwnd = hwnd;

	CreateDeviceAndSwapChain();
	CreateRenderTargetView();
	SetViewport();
}

Graphics::~Graphics()
{
}

void Graphics::RenderBegin()
{
	// 최종 결과물을 도화지에 그려줘. OM : 렌더링 파이프라인의 맨 마지막 단계.
	// 후면버퍼에 그려달라고 요청하는 단계.
	_deviceContext->OMSetRenderTargets(1, _renderTargetView.GetAddressOf(), nullptr);
	_deviceContext->ClearRenderTargetView(_renderTargetView.Get(), _clearColor); // 초기값으로 밀어줌.
	_deviceContext->RSSetViewports(1, &_viewport); // 화면의 크기 정보. 
}

void Graphics::RenderEnd()
{
	// Present를 하게 되면 후면 버퍼에 있는 내용을 전면버퍼로 고속 복사가 이루어짐.
	HRESULT hr = _swapChain->Present(1, 0);
	CHECK(hr);
}

void Graphics::CreateDeviceAndSwapChain()
{
	DXGI_SWAP_CHAIN_DESC desc;
	ZeroMemory(&desc, sizeof(desc));
	{
		desc.BufferDesc.Width = GWinSizeX;
		desc.BufferDesc.Height = GWinSizeY;
		desc.BufferDesc.RefreshRate.Numerator = 60; // 화면 주사율
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		desc.SampleDesc.Count = 1; // 멀티 샘플링.
		desc.SampleDesc.Quality = 0;

		// 최종적으로 화면에 그릴 때에 사용하겠다.
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = 1; // 후면 버퍼는 1개만 사용
		desc.OutputWindow = _hwnd;
		desc.Windowed = true;
		desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	}

	HRESULT hr = ::D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&desc,
		_swapChain.GetAddressOf(),
		_device.GetAddressOf(),
		nullptr,
		_deviceContext.GetAddressOf()
	);

	CHECK(hr);
}


// 위에서 D3D11CreateDeviceAndSwapChain을 할때 후면 버퍼를 만들어 졌다는 것은 알고 있는 상태.
// 후면 버퍼는 _swapChain가 알고 있음.
// 후면 버퍼에 그림을 그려달라고 요청을 해야 함.
// 후면 버퍼를 묘사하는 _renderTargetView라는 곳에 그려달라.
void Graphics::CreateRenderTargetView()
{
	HRESULT hr;

	ComPtr<ID3D11Texture2D> backBuffer = nullptr;
	hr = _swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)backBuffer.GetAddressOf());
	CHECK(hr);

	_device->CreateRenderTargetView(backBuffer.Get(), nullptr, _renderTargetView.GetAddressOf());
	CHECK(hr);
}

void Graphics::SetViewport()
{
	_viewport.TopLeftX = 0.f;
	_viewport.TopLeftY = 0.f;
	_viewport.Width = static_cast<float>(GWinSizeX);
	_viewport.Height = static_cast<float>(GWinSizeY);
	_viewport.MinDepth = 0.f;
	_viewport.MaxDepth = 1.f;
}
