#include "DxLib.h"
#include "MBlockManager.h"

MBlockManager::MBlockManager()
{
}

MBlockManager::~MBlockManager()
{
}

void MBlockManager::Initialize()
{
}

void MBlockManager::Update()
{
	/*for (int i = 0; i < mBlock.size(); i++)
	{
		mBlock[i]->Update();
	}*/
}

void MBlockManager::Update(Vector2& pos, Vector2 scale)
{
	for (int i = 0; i < mBlock.size(); i++)
	{
		mBlock[i]->Update();

		if (mBlock[i]->mode == Normal)
		{
			CheckHitBox(mBlock[i]->pos, mBlock[i]->scale, pos, scale, true);
		}

		if (mBlock[i]->mode == Move)
		{
			CheckHitBox(pos, scale, mBlock[i]->pos, mBlock[i]->scale, false);
		}

		if (mBlock[i]->mode == Lazar)
		{
			CheckHitBox(mBlock[i]->Lpos, mBlock[i]->Lscale, pos, scale, true);

			for (int j = 0; j < mBlock.size(); j++)
			{
				if (mBlock[j]->mode != Lazar)
				{
					AutoCheckHitBox(mBlock[j]->pos, mBlock[j]->scale, mBlock[i]->Lpos, mBlock[i]->Lscale);
				}
			}
		}

		if (i == 11)
		{
			if (CheckHitKey(KEY_INPUT_P))
			{
				mBlock[i]->pos.y = 500;

				mBlock[i]->pos.x = 560;
			}

			if (CheckHitKey(KEY_INPUT_O))
			{
				mBlock[i]->pos.y = 680;

				mBlock[i]->pos.x = 550;
			}
		}
	}
}

void MBlockManager::Draw()
{
	for (int i = 0; i < mBlock.size(); i++)
	{
		mBlock[i]->Draw();
	}
}

void MBlockManager::Finalize()
{
}

void MBlockManager::CreateBlock()
{
	//‰¼‰«‚Ì’†g‚ðì‚é
	MBlock* newBlock = new MBlock();

	//Init‚ðŒÄ‚Ô
	newBlock->Initialize();

	//Ši”[
	mBlock.push_back(newBlock);
}

void MBlockManager::CreateBlock(Vector2 pos_, Vector2 scale_, int mode_)
{
	//‰¼‰«‚Ì’†g‚ðì‚é
	MBlock* newBlock = new MBlock(pos_, scale_, mode_);

	if (newBlock->mode == Lazar)
	{
		Vector2 Lpos = pos_;
		Vector2 Lscale = scale_ /2;

		newBlock->SetLazar(Lpos, Lscale);
	}

	//Ši”[
	mBlock.push_back(newBlock);
}

void MBlockManager::CheckHitBox(Vector2 pos, Vector2 scale, Vector2& pos2, Vector2 scale2, bool vec)
{
	/*float width = 1280;
	float height = 630;

	pos.x = max(pos.x, scale.x);
	pos.x = min(pos.x, width - scale.x);

	pos.y = max(pos.y, scale.y);
	pos.y = min(pos.y, height - scale.y);

	pos2.x = max(pos2.x, scale2.x);
	pos2.x = min(pos2.x, width - scale2.x);

	pos2.y = max(pos2.y, scale2.y);
	pos2.y = min(pos2.y, height - scale2.y);*/

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
		if (Left0 < Right1 &&
			Right0 > Left1)
		{
			if (vec)
				pos2.x -= (CheckHitKey(KEY_INPUT_D) - CheckHitKey(KEY_INPUT_A));

			if (!vec)
				pos2.x += (CheckHitKey(KEY_INPUT_D) - CheckHitKey(KEY_INPUT_A));
		}

		if (Top0 < Bottom1 &&
			Bottom0 > Top1)
		{
			if (vec)
				pos2.y += vec;
		}

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

void MBlockManager::AutoCheckHitBox(Vector2 pos, Vector2 scale, Vector2& pos2, Vector2& scale2)
{
	int Left0 = pos.x - scale.x;
	int Right0 = pos.x + scale.x;
	int Bottom0 = pos.y + scale.y;
	int Top0 = pos.y - scale.y;

	int Left1 = pos2.x - scale2.x;
	int Right1 = pos2.x + scale2.x;
	int Bottom1 = pos2.y + scale2.y;
	int Top1 = pos2.y - scale2.y;

	int vec = 0;

	if (pos.y > pos2.y)
	{
		vec = -1;
	}
	else
	{
		vec = 1;
	}

	while (
		Left0 < Right1 &&
		Right0 > Left1 &&
		Top0 < Bottom1 &&
		Bottom0 > Top1)
	{
		pos2.y += vec;
		scale2.y += vec;

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