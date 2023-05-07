#include "Stage.h"
#include <cmath>
#include "Input.h"

void Stage::Update(void)
{
    MiningOperatorPieceTabs();

    Vector2 recordpos{};
    ExplorateNearTabs(recordpos);

    ConfirmOperatorPiecePos(recordpos);

    SelectPieceForOperatorDebug();
}

void Stage::Draw(void)
{
    for (size_t i = 0; i < pieceVector_.size(); i++)
    {
        pieceVector_[i]->Draw();
    }

    DrawFormatString(0, 0, 0xffffff, isPossibleInPiece_ ? "ready to InPiece" : "no ready to InPiece");
    DrawFormatString(0, 20, 0xff0000, isReset_ ? "execute reset" : "do not permission to reset");
}

void Stage::AddPiece(Piece* ptr)
{
    pieceVector_.emplace_back(ptr);
}

void Stage::OperatePiece(int index)
{
    if (pieceVector_[index]->GetState() == Piece::State::IMMUTABLE) {
        isReset_ = true;
        return;
    }

    for (size_t i = 0; i < pieceVector_.size(); i++)
    {
        pieceVector_[i]->SetOperator(false);
    }
    pieceVector_[index]->SetOperator(true);
    pieceVector_[index]->SetFixity(false);

    permissionTabsAccess_ = true;
}

void Stage::InternalUpdatePieces(int index)
{
    pieceVector_[index]->Update();
}

void Stage::MiningOperatorPieceTabs(void)
{
    // �s�[�X�������茟��
    for (size_t i = 0; i < pieceVector_.size(); i++)
    {
        InternalUpdatePieces(i);

        // �Ώۂ�Piece��isOperator��true�̎��@��isOperator��true�ɂȂ��Ă���Piece�͒P��z��
        if (pieceVector_[i]->GetOperator()) {
            // tabs���R�s�[
            operatorTabs_ = pieceVector_[i]->GetTabs();
            indexOperatorPiece_ = i;
        }
    }
}

void Stage::ExplorateNearTabs(Vector2& recordPos)
{
    // �Y��piece�ɕt������tab�S�ĂŌ���
    for (size_t i = 0; i < operatorTabs_.size(); i++)
    {
        // ���̑S�Ă�piece������
        for (size_t j = 0; j < pieceVector_.size(); j++)
        {
            if (j == indexOperatorPiece_) continue;

            // ��Piece��tab�����ׂČ���
            for (size_t k = 0; k < pieceVector_[j]->GetTabs().size(); k++)
            {
                // �֐��Ăяo���̉񐔂�}��
                Vector2 noOpTabPos{ pieceVector_[j]->GetTabs()[k].pos_ };
                // �Y��tab���甼�adetectRadius_�ȓ��ɁA��tab�����邩�m�F
                if (std::fabs(operatorTabs_[i].pos_.x - noOpTabPos.x) <= detectRadius_ &&
                    std::fabs(operatorTabs_[i].pos_.y - noOpTabPos.y) <= detectRadius_) {
                    // �Y��tab�Ƒ�tab�̕����iPiece::Dir�j���K���ł��邩�m�F
                    if (static_cast<int>(operatorTabs_[i].dir_) + static_cast<int>(pieceVector_[j]->GetTabs()[k].dir_) == 3) {
                        //isPossibleInPiece_ = true;
                        // �Y��Piece�̒��S���W���Čv�Z
                        recordPos = { noOpTabPos.x + pieceVector_[indexOperatorPiece_]->GetPos().x - operatorTabs_[i].pos_.x, noOpTabPos.y + pieceVector_[indexOperatorPiece_]->GetPos().y - operatorTabs_[i].pos_.y };
                        // �Y��tab��index��ۑ�
                        indexInPieceMineTab_ = i;
                        indexNoOperatorPiece_ = j;
                        indexInPieceOtherTab_ = k;
                    }
                }
            }
        }
    }

    // ����piece���P��ł��邱�Ƃ��l�����āA����piece�����݂��Ȃ��ꍇ�AoperatorTabs�͒��g���Ȃ��̂ŗ�O�X���[����������B
    // �����������邽�߂�bool
    if (permissionTabsAccess_) {
        if (indexOperatorPiece_ != indexNoOperatorPiece_) {
            if (std::fabs(operatorTabs_[indexInPieceMineTab_].pos_.x - pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].pos_.x) <= detectRadius_ &&
                std::fabs(operatorTabs_[indexInPieceMineTab_].pos_.y - pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].pos_.y) <= detectRadius_) {
                isPossibleInPiece_ = true;
            }
            else {
                isPossibleInPiece_ = false;
            }
        }
    }
}

void Stage::ConfirmOperatorPiecePos(const Vector2& pos)
{
    if (KEY::IsTrigger(KEY_INPUT_RETURN)) {
        if (isPossibleInPiece_ && pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].isConnected_ == false) {
            permissionTabsAccess_ = false;

            // 1�Q
            // �Y��Piece�̒��S�_��ExplorateNearTabs()�Ŏ擾�����l�ɕύX�B
            pieceVector_[indexOperatorPiece_]->SetPos(pos);
            //// �Y��Piece�̐ڑ�tab��isEntranceOpen��true�ɕύX ��3�Q�Ɉړ�
            //pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(operatorTabs_[indexInPieceMineTab_].indexBlockVector_)->SetEntranceOpen(true);
            // �Y��Piece��Tabs����ڑ���Ԃ̗L����ύX
            pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].isConnected_ = true;
            // �Y��Piece��Tabs����ڑ��҂���ڑ��҂��̗L����ύX
            pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].isConnectExecuter_ = true;
            // �Y��Piece���͂ߍ��񂾂̂ŌŒ�
            pieceVector_[indexOperatorPiece_]->SetFixity(true);

            // 2�Q
            // ��Piece�̐ڑ�tab��isEntranceOpen��true�ɕύX
            size_t elem{ pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].indexBlockVector_ };
            pieceVector_[indexNoOperatorPiece_]->GetBlocksPtr()->at(elem)->SetEntranceOpen(true);
            // ��Piece��Tabs����ڑ���Ԃ̗L����ύX
            pieceVector_[indexNoOperatorPiece_]->GetTabsRef()[indexInPieceOtherTab_].isConnected_ = true;
            // ��Piece��Tabs����ڑ��҂���ڑ��҂��̗L����ύX
            pieceVector_[indexNoOperatorPiece_]->GetTabsRef()[indexInPieceOtherTab_].isConnectExecuter_ = false;

            // 3�Q
            // ��Piece���͂ߍ��񂾂��Ƃɂ���
            pieceVector_[indexNoOperatorPiece_]->SetFixity(true);
            // �Y��Piece�̒��S�_����ύX�����̂ŁAUpdate()�����s
            pieceVector_[indexOperatorPiece_]->Update();
            // �Y��Piece�̐ڑ�tab��isEntranceOpen��true�ɕύX Update()����Entrance��false�ɂ��Ă��܂��֐����܂܂�Ă��邽�߂��̈ʒu
            pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(operatorTabs_[indexInPieceMineTab_].indexBlockVector_)->SetEntranceOpen(true);
            // �Y��Piece�̑��쌠�����
            pieceVector_[indexOperatorPiece_]->SetOperator(false);
            // �Y��Piece��tabs�R�s�[��j��
            operatorTabs_.clear();
            // �Y��Piece�͂ߍ��݉\���m�点��t���O��false�ɕύX�B
            isPossibleInPiece_ = false;
        }
    }
}

void Stage::SelectPieceForOperatorDebug(void)
{
    if (KEY::IsDown(KEY_INPUT_LSHIFT)) {
        if (KEY::IsTrigger(KEY_INPUT_0)) OperatePiece(0);
        if (KEY::IsTrigger(KEY_INPUT_1)) OperatePiece(1);
        if (KEY::IsTrigger(KEY_INPUT_2)) OperatePiece(2);
        if (KEY::IsTrigger(KEY_INPUT_3)) OperatePiece(3);
        if (KEY::IsTrigger(KEY_INPUT_4)) OperatePiece(4);
        if (KEY::IsTrigger(KEY_INPUT_5)) OperatePiece(5);
        if (KEY::IsTrigger(KEY_INPUT_6)) OperatePiece(6);
        if (KEY::IsTrigger(KEY_INPUT_7)) OperatePiece(7);
        if (KEY::IsTrigger(KEY_INPUT_8)) OperatePiece(8);
        if (KEY::IsTrigger(KEY_INPUT_9)) OperatePiece(9);
    }
    else {
        if (KEY::IsTrigger(KEY_INPUT_0)) pieceVector_[0]->SetOperator(false);
        if (KEY::IsTrigger(KEY_INPUT_1)) pieceVector_[1]->SetOperator(false);
        if (KEY::IsTrigger(KEY_INPUT_2)) pieceVector_[2]->SetOperator(false);
        if (KEY::IsTrigger(KEY_INPUT_3)) pieceVector_[3]->SetOperator(false);
        if (KEY::IsTrigger(KEY_INPUT_4)) pieceVector_[4]->SetOperator(false);
        if (KEY::IsTrigger(KEY_INPUT_5)) pieceVector_[5]->SetOperator(false);
        if (KEY::IsTrigger(KEY_INPUT_6)) pieceVector_[6]->SetOperator(false);
        if (KEY::IsTrigger(KEY_INPUT_7)) pieceVector_[7]->SetOperator(false);
        if (KEY::IsTrigger(KEY_INPUT_8)) pieceVector_[8]->SetOperator(false);
        if (KEY::IsTrigger(KEY_INPUT_9)) pieceVector_[9]->SetOperator(false);
    }
}
