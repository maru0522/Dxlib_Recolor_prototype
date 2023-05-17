#pragma once
#include "IBlock.h"
class Laser :
	public IBlock
{
public:
	// ä÷êî
	Laser(const Vector2& pos, const Vector2& offset, const Vector2& radius = { 1,1 });
	~Laser(void) {};

	void Update(void) override;
	void Draw(void) override;

	Vector2 vec = { 0,0 };
	void SetVec(Vector2 vec);
};

