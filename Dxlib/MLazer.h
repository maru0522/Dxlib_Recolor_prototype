#pragma once
#include "Vector2.h"

class MLazer
{
public:
	MLazer();
	MLazer(Vector2 pos, Vector2 scale, int mode);
	~MLazer();
	void Initialize();
	//void Update();
	void Update(Vector2& pos);
	void Draw();

	void Gravity();

	//private:
	Vector2 pos;
	Vector2 scale;

	int mode;
};