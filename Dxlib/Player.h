#pragma once
#include "Vector2.h"
#include "Stage.h"

class Player
{
public:
	// 定数
	static constexpr uint32_t defaultWidth_{ 4 };
	static constexpr uint32_t defaultHeight_{ 8 };
	static constexpr float moveSpeed_{ 3.f };       // 移動速度
	static constexpr float jumpPower_{ 10.f };       // ジャンプ力
	static constexpr float springPower_{ 12.f };       // ジャンプ力
	static constexpr float fallValue_{ 0.2f };      // ジャンプ力の減衰
	static constexpr float gravity_{ 3.5f };        // 重力

	// 関数
	Player(Stage* stagePtr);
	void Update(void);
	void Draw(void);

private:
	void Move(void);
	void Jump(Vector2& vel,float& jumpValue);
	void Spring(Vector2& vel, int rot);

	void Collision(Vector2& vel,float& jumpValue);
	bool CheckHit(float pos, float radius, float vel, float blockpos, float blockradius);
	bool CheckHit(float pos, float radius, float vel, float blockpos, float blockradius, float& surplus);

	// 変数
	Vector2 pos_{};
	Vector2 radius_{};
	Vector2 offsetForPieceCenter_{};

	bool isJump_{ true };
	bool isSpring_{ false };

	Stage* stagePtr_;

	//ばねに触れた時の角度を入れる変数
	int nowSpringRot = 0;
	//代入変数
	Vector2 nowVel = { 0, 0 };
public:
	// setter・getter
	inline void SetPos(const Vector2& pos) { pos_ = pos; };
	inline void SetRadius(const Vector2& radius) { radius_ = radius; };
	inline void SetOffset(const Vector2& offset) { offsetForPieceCenter_ = offset; }

	inline const Vector2& GetPos(void) { return pos_; }
	inline const Vector2& GetRadius(void) { return radius_; }
	inline Vector2* GetPosPtr(void) { return &pos_; }
	inline const Vector2& GetOffset(void) { return offsetForPieceCenter_; }

};

