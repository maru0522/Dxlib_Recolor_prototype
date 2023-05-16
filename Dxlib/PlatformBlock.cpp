#include "PlatformBlock.h"

PlatformBlock::PlatformBlock(const Vector2& pos, const Vector2& offset, const Vector2& radius) :
	IBlock(pos, offset, radius)
{
	SetType(Type::PLATFORM);
}

void PlatformBlock::Update(void)
{
}

void PlatformBlock::Draw(void)
{
	int posX{ static_cast<int>(GetPos().x) }, posY{ static_cast<int>(GetPos().y) };
	int radiusX{ static_cast<int>(GetRadius().x) }, radiusY{ static_cast<int>(GetRadius().y) };

	DrawBox(
		static_cast<int>(posX - radiusX), static_cast<int>(posY - radiusY),
		static_cast<int>(posX + radiusX), static_cast<int>(posY + radiusY),
		0x0000ff, false
	);
}
