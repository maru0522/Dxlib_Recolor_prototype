#pragma once
#include "Vector2.h"

class MPlayer
{
public:
	MPlayer();
	~MPlayer();
	void Initialize();
	void Update(Vector2 &pos, Vector2 scale);
	void Draw();

	void CheckHitBox(Vector2 pos, Vector2 scale, Vector2 &pos2, Vector2 scale2);
//private:
	Vector2 pos;
	Vector2 scale;
};