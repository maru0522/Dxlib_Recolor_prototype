#include "Player.h"
#include <cmath>
#include "Input.h"
#include <DxLib.h>

Player::Player(Stage* stagePtr) :
	stagePtr_(stagePtr), radius_(defaultWidth_, defaultHeight_)
{
}

void Player::Update(void)
{
	Move();

	//if (pos_.y > 600)pos_.y = 0;
}

void Player::Draw(void)
{
	DrawBox(GetPos().x - GetRadius().x, GetPos().y - GetRadius().y, GetPos().x + GetRadius().x, GetPos().y + GetRadius().y, 0xffffff, true);
	DrawCircle(GetPos().x, GetPos().y, 5, 0xff0000, 1, 1);
}

void Player::Move(void)
{
	// �ړ���
	Vector2 vel{};

	// x��
	// ���E���͂̔���ƈړ��ʉ��Z
	vel.x += (KEY::IsDown(KEY_INPUT_D) - KEY::IsDown(KEY_INPUT_A)) * moveSpeed_;
	//vel.y += (KEY::IsDown(KEY_INPUT_S) - KEY::IsDown(KEY_INPUT_W)) * moveSpeed_;

    static float jumpValue{ 0.f };
	// y��
	// �W�����v����
	Jump(vel,jumpValue);

	//�΂ˏ���
	Spring(vel, nowSpringRot);

	// �d��
	vel.y += gravity_;

	//vel = vel.normalize();

	// �ړ��ʕ␳
	Collision(vel,jumpValue);

	// �␳�ς̈ړ��ʂ�pos�ɉ��Z
	Vector2 pos{ GetPos() + vel };
	SetPos(pos);
}

//�΂ˏ���
void Player::Spring(Vector2& vel, int rot)
{
	//true����Ȃ���Δ�����
	if (!isSpring_ && nowVel.x == 0 && nowVel.y == 0)
	{
		nowSpringRot = 0;
		return;
	}

	//�W�����v�h�~
	isJump_ = true;

	//��]�p
	int rot_ = rot;

	if (isSpring_)
	{
		//90�x���Ƃ�
		switch (rot_ / 90)
		{
		case 0:
			nowVel.y = -springPower_;
			break;
		case 1:
			nowVel.x = springPower_ / 2;
			break;
		case 2:
			nowVel.y = springPower_;
			break;
		case 3:
			nowVel.x = -springPower_ / 2;
			break;
		}

		isSpring_ = false;
	}
	else
	{
		//90�x���Ƃ�
		switch (rot_ / 90)
		{
		case 0:
			nowVel.y += fallValue_;

			if (nowVel.y > 0)
			{
				nowVel.y = 0;
			}
			break;
		case 1:
			nowVel.x -= fallValue_;

			if (nowVel.x < 0)
			{
				nowVel.x = 0;
			}
			break;
		case 2:
			nowVel.y -= fallValue_;

			if (nowVel.y < 0)
			{
				nowVel.y = 0;
			}
			break;
		case 3:
			nowVel.x += fallValue_;

			if (nowVel.x > 0)
			{
				nowVel.x = 0;
			}
			break;
		}
	}

	vel += nowVel;
}

void Player::Jump(Vector2& vel, float& jumpValue)
{
	// �g���K�[�ŃW�����v
	if (KEY::IsTrigger(KEY_INPUT_SPACE) && isJump_ == false) {
		isJump_ = true;
		jumpValue += jumpPower_;
	}

	// vel�ɃW�����v��(y���ړ���)�����Z
	vel.y -= jumpValue;
	if (jumpValue > 0.f) {
		jumpValue -= fallValue_;
	}
	else if (jumpValue <= 0.f) {
		isJump_ = false;
	}

	// 0�����̒l�ɂȂ�Ȃ��B
	jumpValue = (std::max)(jumpValue, 0.f);
}

void Player::Collision(Vector2& vel,float& jumpValue)
{
	for (size_t i = 0; i < stagePtr_->GetPieceVectorPtr()->size(); i++) {
		// �Y��Piece�����삳��Ă���ꍇ�X�L�b�v
		if (stagePtr_->GetPieceVectorPtr()->at(i)->GetOperator()) continue;
		// �Y��Piece
		if (stagePtr_->GetPieceVectorPtr()->at(i)->GetFixity() == false) continue;

		for (size_t j = 0; j < stagePtr_->GetPieceVectorPtr()->at(i)->GetBlocksPtr()->size(); j++)
		{
			// �|�C���^���m�ۂ���getter�֐��Ăяo���}��
			IBlock* tempBlockPtr{ stagePtr_->GetPieceVectorPtr()->at(i)->GetBlocksPtr()->at(j).get() };

			// X��,Y����3�u���b�N�͈͓��ł͂Ȃ��ꍇ�A�X�L�b�v
			if (std::abs(tempBlockPtr->GetPos().x - GetPos().x) > IBlock::radiusBase_ * 6) continue;
			if (std::abs(tempBlockPtr->GetPos().y - GetPos().y) > IBlock::radiusBase_ * 6) continue;

			// �u���b�N�̎�ނ� PIECEENTRANCEBLOCK �ł���ꍇ
			if (tempBlockPtr->GetType() == IBlock::Type::PIECEENTRANCE) {
				// �v���C���[���u���b�N�̒����ɐG��邩
				if (CheckHit(GetPos().x, GetRadius().x, 0, tempBlockPtr->GetPos().x, 8) &&
					CheckHit(GetPos().y, GetRadius().y, 0, tempBlockPtr->GetPos().y, 8)) {
					if (stagePtr_->GetPieceVectorPtr()->at(i)->GetState() == Piece::State::MOVABLE) stagePtr_->GetPieceVectorPtr()->at(i)->SetState(Piece::State::IMMUTABLE);
				}

				if (tempBlockPtr->GetEntranceOpen())
					continue;
			}

			//�΂˃u���b�N����
			if (tempBlockPtr->GetType() == IBlock::Type::SPRING) {
				if (CheckHit(GetPos().x, GetRadius().x, 0, tempBlockPtr->GetPos().x, 9) &&
					CheckHit(GetPos().y, GetRadius().y, 0, tempBlockPtr->GetPos().y, 9)) {

					nowSpringRot = tempBlockPtr->GetRotate();

					isSpring_ = true;
				}
			}

			// �u���b�N�ɂ߂荞�񂾃s�N�Z���l
			float surplus{};

			// y������
			if (CheckHit(GetPos().x, GetRadius().x, 0, tempBlockPtr->GetPos().x, tempBlockPtr->GetRadius().x)) {
				if (CheckHit(GetPos().y, GetRadius().y, vel.y, tempBlockPtr->GetPos().y, tempBlockPtr->GetRadius().y, surplus)) {
					//�V��ɓ�����������
					if (GetPos().y - GetRadius().y + vel.y > tempBlockPtr->GetPos().y - tempBlockPtr->GetRadius().y) {
						//���̒��ŃW�����v�ʂ�0�ɂ���ƓV��ɂԂ������u�ԗ�����
                        jumpValue = 0.f;
					}

					vel.y > 0 ? vel.y += surplus : vel.y -= surplus;
				}
			}

			// x������
			if (CheckHit(GetPos().y, GetRadius().y, 0, tempBlockPtr->GetPos().y, tempBlockPtr->GetRadius().y)) {
				if (CheckHit(GetPos().x, GetRadius().x, vel.x, tempBlockPtr->GetPos().x, tempBlockPtr->GetRadius().x, surplus)) {
					vel.x > 0 ? vel.x += surplus : vel.x -= surplus;
				}
			}
		}
	}
}

bool Player::CheckHit(float pos, float radius, float vel, float blockpos, float blockradius)
{
	// �l��0�����Ȃ�߂荞��ł�B
	return std::abs(pos - blockpos + vel) - (radius + blockradius) < 0;
}

bool Player::CheckHit(float pos, float radius, float vel, float blockpos, float blockradius, float& surplus)
{
	surplus = std::abs(pos - blockpos + vel) - (radius + blockradius);

	// �l��0�����Ȃ�߂荞��ł�B
	return surplus < 0;
}
