#include "MBlock.h"
#include "DxLib.h"

MBlock::MBlock()
{
	pos = Vector2{ 100,100 };
	scale = Vector2{ 30,30 };
	mode = Normal;
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
	mode = Normal;
}

void MBlock::Update()
{
	if (mode == Lazar)
	{
		Lpos.y += 1;
		Lscale.y += 1;
	}

	if (mode == Move)
	{
		Gravity();
	}

	if (mode != Normal)
	{
		int width = 1280;
		int height = 655;

		pos.x = max(pos.x, scale.x);
		pos.x = min(pos.x, width - scale.x);

		pos.y = max(pos.y, scale.y);
		pos.y = min(pos.y, height - scale.y);
	}
}

void MBlock::Update(Vector2& pos)
{
	if (mode == Lazar)
	{
		Lpos.y += 1;
		Lscale.y += 1;

		//Collision();
	}

	if (mode == Move)
	{
		this->pos = pos;
		Gravity();
	}

	int width = 1280;
	int height = 655;

	pos.x = max(pos.x, scale.x);
	pos.x = min(pos.x, width - scale.x);

	pos.y = max(pos.y, scale.y);
	pos.y = min(pos.y, height - scale.y);
}

void MBlock::Draw()
{
	if (mode == Normal)
	{
		DrawBox(
			pos.x - scale.x,
			pos.y - scale.y,
			pos.x + scale.x,
			pos.y + scale.y,
			GetColor(200, 100, 100),
			true);
	}

	if (mode == Move)
	{
		DrawBox(
			pos.x - scale.x,
			pos.y - scale.y,
			pos.x + scale.x,
			pos.y + scale.y,
			GetColor(100, 100, 100),
			true);
	}

	if (mode == Lazar)
	{
		DrawBox(
			Lpos.x - Lscale.x,
			Lpos.y - Lscale.y,
			Lpos.x + Lscale.x,
			Lpos.y + Lscale.y,
			GetColor(100, 100, 150),
			true);

		DrawBox(
			pos.x - scale.x,
			pos.y - scale.y,
			pos.x + scale.x,
			pos.y + scale.y,
			GetColor(100, 100, 200),
			true);
	}
}

void MBlock::Gravity()
{
	float gravity = 1.0f;

	pos.y += gravity;
}

void MBlock::SetLazar(Vector2 pos, Vector2 scale)
{
	Lpos = pos;
	Lscale = scale;
}