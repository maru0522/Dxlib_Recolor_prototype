#pragma once
#include "Vector2.h"

enum mode
{
	normal,
	dontMove,
};

class MBlock
{
public:
	MBlock();
	MBlock(Vector2 pos, Vector2 scale, int mode);
	~MBlock();
	void Initialize();
	void Update();
	void Draw();

//private:
	Vector2 pos;
	Vector2 scale;

	int mode;
};