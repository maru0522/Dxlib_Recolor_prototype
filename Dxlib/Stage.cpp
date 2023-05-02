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
}

void Stage::AddPiece(Piece* ptr)
{
    pieceVector_.emplace_back(ptr);
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
                        isPossibleInPiece_ = true;
                        // �Y��Piece�̒��S���W���Čv�Z
                        recordPos = { noOpTabPos.x + pieceVector_[indexOperatorPiece_]->GetPos().x - operatorTabs_[i].pos_.x, noOpTabPos.y + pieceVector_[indexOperatorPiece_]->GetPos().y - operatorTabs_[i].pos_.y };
                        // �Y��tab��index��ۑ�
                        indexInPieceMineTab_ = i;
                        indexNoOperatorPiece_ = j;
                        indexInPieceOtherTab_ = k;
                    }
                    else {
                        //isPossibleInPiece_ = false;
                    }
                }
                else {
                    isPossibleInPiece_ = false;
                }
            }
        }
    }
}

void Stage::ConfirmOperatorPiecePos(const Vector2& pos)
{
    if (KEY::IsTrigger(KEY_INPUT_RETURN))
        if (isPossibleInPiece_) {
            // �Y��Piece�̒��S�_��ExplorateNearTabs()�Ŏ擾�����l�ɕύX�B
            pieceVector_[indexOperatorPiece_]->SetPos(pos);
            // �Y��Piece�̐ڑ�tab��isEntranceOpen��true�ɕύX
            pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(operatorTabs_[indexInPieceMineTab_].indexBlockVector_)->SetEntranceOpen(true);
            // ��Piece�̐ڑ�tab��isEntranceOpen��true�ɕύX
            size_t elem{ pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].indexBlockVector_ };
            pieceVector_[indexNoOperatorPiece_]->GetBlocksPtr()->at(elem)->SetEntranceOpen(true);
            // �Y��Piece�̒��S�_����ύX�����̂ŁAUpdate()�����s
            pieceVector_[indexOperatorPiece_]->Update();
            // �Y��Piece�̑��쌠�����
            pieceVector_[indexOperatorPiece_]->SetOperator(false);
            // �Y��Piece��tabs�R�s�[��j��
            operatorTabs_.clear();
            // �Y��Piece�͂ߍ��݉\���m�点��t���O��false�ɕύX�B
            isPossibleInPiece_ = false;
        }
}

void Stage::SelectPieceForOperatorDebug(void)
{
    if (KEY::IsDown(KEY_INPUT_LSHIFT)) {
        if (KEY::IsTrigger(KEY_INPUT_0)) pieceVector_[0]->SetOperator(true);
        if (KEY::IsTrigger(KEY_INPUT_1)) pieceVector_[1]->SetOperator(true);
        if (KEY::IsTrigger(KEY_INPUT_2)) pieceVector_[2]->SetOperator(true);
        if (KEY::IsTrigger(KEY_INPUT_3)) pieceVector_[3]->SetOperator(true);
        if (KEY::IsTrigger(KEY_INPUT_4)) pieceVector_[4]->SetOperator(true);
        if (KEY::IsTrigger(KEY_INPUT_5)) pieceVector_[5]->SetOperator(true);
        if (KEY::IsTrigger(KEY_INPUT_6)) pieceVector_[6]->SetOperator(true);
        if (KEY::IsTrigger(KEY_INPUT_7)) pieceVector_[7]->SetOperator(true);
        if (KEY::IsTrigger(KEY_INPUT_8)) pieceVector_[8]->SetOperator(true);
        if (KEY::IsTrigger(KEY_INPUT_9)) pieceVector_[9]->SetOperator(true);
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

    if (KEY::IsTrigger(KEY_INPUT_R)) {
        pieceVector_[0]->SetOperator(false);
        pieceVector_[1]->SetOperator(false);
        pieceVector_[2]->SetOperator(false);
        pieceVector_[3]->SetOperator(false);
        pieceVector_[4]->SetOperator(false);
        pieceVector_[5]->SetOperator(false);
        pieceVector_[6]->SetOperator(false);
        pieceVector_[7]->SetOperator(false);
        pieceVector_[8]->SetOperator(false);
        pieceVector_[9]->SetOperator(false);
    }
}
