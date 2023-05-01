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
    // ピース総当たり検索
    for (size_t i = 0; i < pieceVector_.size(); i++)
    {
        InternalUpdatePieces(i);

        // 対象のPieceのisOperatorがtrueの時　※isOperatorがtrueになっているPieceは単一想定
        if (pieceVector_[i]->GetOperator()) {
            // tabsをコピー
            operatorTabs_ = pieceVector_[i]->GetTabs();
            indexOperatorPiece_ = i;
        }
    }
}

void Stage::ExplorateNearTabs(Vector2& recordPos)
{
    // 該当pieceに付属するtab全てで検索
    for (size_t i = 0; i < operatorTabs_.size(); i++)
    {
        // 他の全てのpieceを検索
        for (size_t j = 0; j < pieceVector_.size(); j++)
        {
            // 他Pieceのtabをすべて検索
            for (size_t k = 0; k < pieceVector_[j]->GetTabs().size(); k++)
            {
                // 関数呼び出しの回数を抑制
                Vector2 noOpTabPos{ pieceVector_[j]->GetTabs()[k].pos_ };
                // 該当tabから半径detectRadius_以内に、他tabがあるか確認
                if (std::fabs(operatorTabs_[i].pos_.x - noOpTabPos.x) <= detectRadius_ &&
                    std::fabs(operatorTabs_[i].pos_.y - noOpTabPos.y) <= detectRadius_) {
                    // 該当tabと他tabの方向（Piece::Dir）が適正であるか確認
                    if (static_cast<int>(operatorTabs_[i].dir_) + static_cast<int>(pieceVector_[j]->GetTabs()[k].dir_) == 3) {
                        isPossibleInPiece_ = true;
                            recordPos = { noOpTabPos.x + pieceVector_[indexOperatorPiece_]->GetPos().x - operatorTabs_[i].pos_.x, noOpTabPos.y + pieceVector_[indexOperatorPiece_]->GetPos().y - operatorTabs_[i].pos_.y };
                        // 該当tabの方向に基づいて、該当Pieceの中心座標を再計算
                        //switch (operatorTabs_[i].dir_)
                        //{
                        //case Piece::Dir::TOP:
                        //    recordPos = { noOpTabPos.x + pieceVector_[indexOperatorPiece_]->GetPos().x - operatorTabs_[i].pos_.x, noOpTabPos.y + pieceVector_[indexOperatorPiece_]->GetPos().y - operatorTabs_[i].pos_.y };
                        //    break;
                        //case Piece::Dir::RIGHT:
                        //    recordPos = { noOpTabPos.x - pieceVector_[indexOperatorPiece_]->GetRadius().x * IBlock::radiusBase_ * 2 , noOpTabPos.y };
                        //    break;
                        //case Piece::Dir::LEFT:
                        //    recordPos = { noOpTabPos.x + pieceVector_[indexOperatorPiece_]->GetRadius().x * IBlock::radiusBase_ * 2 , noOpTabPos.y };
                        //    break;
                        //case Piece::Dir::BOTTOM:
                        //    recordPos = { noOpTabPos.x + pieceVector_[indexOperatorPiece_]->GetPos().x - operatorTabs_[i].pos_.x, noOpTabPos.y + pieceVector_[indexOperatorPiece_]->GetPos().y - operatorTabs_[i].pos_.y };
                        //    break;
                        //default:
                        //    break;
                        //}
                    }
                    else {
                        //isPossibleInPiece_ = false;
                    }
                }
                else {
                    //isPossibleInPiece_ = false;
                }
            }
        }
    }
}

void Stage::ConfirmOperatorPiecePos(const Vector2& pos)
{
    if (KEY::IsTrigger(KEY_INPUT_RETURN))
        if (isPossibleInPiece_) {
            pieceVector_[indexOperatorPiece_]->SetPos(pos);
            isPossibleInPiece_ = false;
            pieceVector_[indexOperatorPiece_]->Update();
            pieceVector_[indexOperatorPiece_]->SetOperator(false);
            operatorTabs_.clear();
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
