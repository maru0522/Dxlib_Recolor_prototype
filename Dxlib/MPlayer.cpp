#include "MPlayer.h"
#include "DxLib.h"

MPlayer::MPlayer()
{
	pos = Vector2{ 300,300 };
	scale = Vector2{ 30,30 };
}

MPlayer::~MPlayer()
{
}

void MPlayer::Initialize()
{
	pos = Vector2{ 300,300 };
	scale = Vector2{ 30,30 };
}

void MPlayer::Update()
{
	int spd = 2;

	this->pos.x += (CheckHitKey(KEY_INPUT_D) - CheckHitKey(KEY_INPUT_A)) * spd;

	Gravity();

	if (CheckHitKey(KEY_INPUT_W))
	{
		this->pos.y -= 4;
	}
}

void MPlayer::Update(Vector2& pos, Vector2 scale)
{
	int spd = 5;

	this->pos.x += (CheckHitKey(KEY_INPUT_D) - CheckHitKey(KEY_INPUT_A)) * spd;

	Gravity();

	if (CheckHitKey(KEY_INPUT_W))
	{
		this->pos.y -= 4;
	}
}

void MPlayer::Draw()
{
	DrawBox(
		pos.x - scale.x,
		pos.y - scale.y,
		pos.x + scale.x,
		pos.y + scale.y,
		GetColor(100, 200, 100),
		true);
}

void MPlayer::Gravity()
{
	float gravity = 1.5f;

	pos.y += gravity;

	int width = 1280;
	int height = 655;

	pos.x = max(pos.x, scale.x);
	pos.x = min(pos.x, width - scale.x);

	pos.y = max(pos.y, scale.y);
	pos.y = min(pos.y, height - scale.y);
}