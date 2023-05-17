#include "MBlock.h"
#include "DxLib.h"

MBlock::MBlock()
{
	pos = Vector2{ 100,100 };
	scale = Vector2{ 30,30 };
	mode = normal;
}

MBlock::MBlock(Vector2 pos, Vector2 scale, int mode)
{
	this->pos = pos;
	this->mode = mode;
	this->scale = scale;
}

MBlock::~MBlock()
{
}

void MBlock::Initialize()
{
	pos = Vector2{ 100,100 };
	scale = Vector2{ 30,30 };
	mode = normal;
}

void MBlock::Update()
{


}

void MBlock::Draw()
{
	if (mode == normal)
	{
		DrawBox(
			pos.x - scale.x,
			pos.y - scale.y,
			pos.x + scale.x,
			pos.y + scale.y,
			GetColor(200, 100, 100),
			true);
	}

	if (mode == dontMove)
	{
		DrawBox(
			pos.x - scale.x,
			pos.y - scale.y,
			pos.x + scale.x,
			pos.y + scale.y,
			GetColor(100, 100, 100),
			false);
	}
}
