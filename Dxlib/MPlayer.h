#pragma once
#include "Vector2.h"

class MPlayer
{
public:
	MPlayer();
	~MPlayer();
	void Initialize();
	void Update(Vector2& pos, Vector2 scale);
	void Update();
	void Draw();

	void Gravity();

	//private:
	Vector2 pos;
	Vector2 scale;
};