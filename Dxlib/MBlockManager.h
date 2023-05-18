#pragma once
#include "MBlock.h"
#include <vector>
#include <cmath>

class MBlockManager
{
private:
	std::vector<MBlock*> mBlock;

public:
	MBlockManager();
	~MBlockManager();

	void Initialize();
	void Update();
	void Update(Vector2& pos, Vector2 scale);
	void Draw();
	void Finalize();
	void CreateBlock();
	void CreateBlock(Vector2 pos_, Vector2 scale_, int mode_);

	void CheckHitBox(Vector2 pos, Vector2 scale, Vector2& pos2, Vector2 scale2,bool vec);
	void AutoCheckHitBox(Vector2 pos, Vector2 scale, Vector2& pos2, Vector2& scale2);
};