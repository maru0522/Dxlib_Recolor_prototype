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

void MPlayer::Update(Vector2& pos, Vector2 scale)
{
	int spd = 2;

	this->pos.x += (CheckHitKey(KEY_INPUT_D) - CheckHitKey(KEY_INPUT_A)) * spd;
	this->pos.y += (CheckHitKey(KEY_INPUT_S) - CheckHitKey(KEY_INPUT_W)) * spd;

	Vector2 nowpos = pos;

	CheckHitBox(this->pos, this->scale, nowpos, scale);

	pos = nowpos;
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

void MPlayer::CheckHitBox(Vector2 pos, Vector2 scale, Vector2& pos2, Vector2 scale2)
{
	int Left0 = pos.x - scale.x;
	int Right0 = pos.x + scale.x;
	int Bottom0 = pos.y + scale.y;
	int Top0 = pos.y - scale.y;

	int Left1 = pos2.x - scale2.x;
	int Right1 = pos2.x + scale2.x;
	int Bottom1 = pos2.y + scale2.y;
	int Top1 = pos2.y - scale2.y;

	while (
		Left0 < Right1 &&
		Right0 > Left1 &&
		Top0 < Bottom1 &&
		Bottom0 > Top1)
	{

		pos2.x += (CheckHitKey(KEY_INPUT_D) - CheckHitKey(KEY_INPUT_A));

		pos2.y += (CheckHitKey(KEY_INPUT_S) - CheckHitKey(KEY_INPUT_W));


		Left0 = pos.x - scale.x;
		Right0 = pos.x + scale.x;
		Bottom0 = pos.y + scale.y;
		Top0 = pos.y - scale.y;

		Left1 = pos2.x - scale2.x;
		Right1 = pos2.x + scale2.x;
		Bottom1 = pos2.y + scale2.y;
		Top1 = pos2.y - scale2.y;
	}
}
