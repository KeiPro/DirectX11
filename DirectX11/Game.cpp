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
	_pipeline = make_shared<Pipeline>(_graphics->GetDeviceContext());

	// Create GameObject
	_gameObject = make_shared<GameObject>(_graphics->GetDevice(), _graphics->GetDeviceContext());
	{
		_gameObject->GetOrAddTransform();
	}
}

void Game::Update()
{
	// Scale Rotation Translation	
	_gameObject->Update();
}

void Game::Render()
{
	_graphics->RenderBegin();

	_gameObject->Render(_pipeline);

	_graphics->RenderEnd();
}