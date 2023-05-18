#pragma once
#include "MBlockManager.h"
#include "MPlayer.h"

class MGame
{
public:
	MGame();
	~MGame();

	void Initialize();
	void Update();
	void Draw();
	void Finalize();
private:

	MPlayer* mPlayer = new MPlayer();
	MBlockManager* mBlockManager = new MBlockManager();
};