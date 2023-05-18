#include "MGame.h"
#include "DxLib.h"

MGame::MGame()
{
}

MGame::~MGame()
{
}

void MGame::Initialize()
{
	mPlayer->Initialize();
	mBlockManager->Initialize();

	int newBlockCount = 24;

	//è∞(normal)ê∂ê¨
	for (int i = 0; i < newBlockCount; i++)
	{
		mBlockManager->CreateBlock(Vector2{ i * 50.0f,680.0f }, Vector2{ 25.0f,25.0f }, Normal);
	}

	//ìÆÇ≠è∞ê∂ê¨
	mBlockManager->CreateBlock(Vector2{ 50.0f,680.0f }, Vector2{ 50.0f,50.0f }, Move);

	//ÉåÅ[ÉUÅ[ê∂ê¨
	mBlockManager->CreateBlock(Vector2{ 550.0f,200.0f }, Vector2{ 50.0f,50.0f }, Lazar);
}

void MGame::Update()
{
	mPlayer->Update();

	mBlockManager->Update(mPlayer->pos, mPlayer->scale);
}

void MGame::Draw()
{
	mPlayer->Draw();
	mBlockManager->Draw();
}

void MGame::Finalize()
{
	delete mPlayer;
}
