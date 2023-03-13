#pragma once
#include "IEntity.h"
#include "IColor.h"
#include "StageManager.h"

class Player : public IEntity, public IColor
{
public:
	// �萔
	static constexpr uint32_t defaultPlayerSize_{};

	Player();
	Player(const Vector2 pos, const Vector2 size, const Color color);

	void Update() override;
	void Draw() override;

//private:
	// �\���̕ϐ�
	std::list<std::unique_ptr<IBlock>> blocks_;
};

