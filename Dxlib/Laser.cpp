#include "Laser.h"

Laser::Laser(const Vector2& pos, const Vector2& offset, const Vector2& radius) :
	IBlock(pos, offset, radius)
{
	SetType(Type::LASER);
}

void Laser::Update(void)
{
	vec = { 0.0f,0.1f };
	SetPos(GetPos() + vec);
	SetRadius(GetRadius() + vec);
}

void Laser::Draw(void)
{
	int posX{ static_cast<int>(GetPos().x) }, posY{ static_cast<int>(GetPos().y) };
	int radiusX{ static_cast<int>(GetRadius().x) }, radiusY{ static_cast<int>(GetRadius().y) };

	DrawBox(
		static_cast<int>(posX - radiusX), static_cast<int>(posY - radiusY),
		static_cast<int>(posX + radiusX), static_cast<int>(posY + radiusY),
		0xff00ff, false
	);
}

void Laser::SetVec(Vector2 vec)
{
	this->vec = vec;
}
