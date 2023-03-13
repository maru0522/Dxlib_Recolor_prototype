#include "Player.h"
#include "DxLib.h"

Player::Player()
{
	this->SetPos(Vector2(0, 0));
	this->SetSize(Vector2(16, 16));
	this->SetColor(Color::RED);
}

Player::Player(const Vector2 pos, const Vector2 size, const Color color)
{
	this->SetPos(pos);
	this->SetSize(size);
	this->SetColor(color);
}

void Player::Update()
{
	Vector2 nowPos = GetPos();

	nowPos.x += 1;

	SetPos(nowPos);
}

void Player::Draw()
{
	int posX = static_cast<int>(GetPos().x);
	int posY = static_cast<int>(GetPos().y);

	int sizeX = static_cast<int>(GetSize().x);
	int sizeY = static_cast<int>(GetSize().y);

	DrawBox(
		posX,
		posY,
		posX + sizeX,
		posY + sizeY,
		0xaa0000,
		true);
}
