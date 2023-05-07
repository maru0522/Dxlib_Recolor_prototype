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
            if (j == indexOperatorPiece_) continue;

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
                        //isPossibleInPiece_ = true;
                        // 該当Pieceの中心座標を再計算
                        recordPos = { noOpTabPos.x + pieceVector_[indexOperatorPiece_]->GetPos().x - operatorTabs_[i].pos_.x, noOpTabPos.y + pieceVector_[indexOperatorPiece_]->GetPos().y - operatorTabs_[i].pos_.y };
                        // 該当tabのindexを保存
                        indexInPieceMineTab_ = i;
                        indexNoOperatorPiece_ = j;
                        indexInPieceOtherTab_ = k;
                    }
                }
            }
        }
    }

    // 操作pieceが単一であることを考慮して、操作pieceが存在しない場合、operatorTabsは中身がないので例外スローが発生する。
    // しれを回避するためのbool
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

            // 1群
            // 該当Pieceの中心点をExplorateNearTabs()で取得した値に変更。
            pieceVector_[indexOperatorPiece_]->SetPos(pos);
            //// 該当Pieceの接続tabのisEntranceOpenをtrueに変更 ※3群に移動
            //pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(operatorTabs_[indexInPieceMineTab_].indexBlockVector_)->SetEntranceOpen(true);
            // 該当PieceのTabsから接続状態の有無を変更
            pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].isConnected_ = true;
            // 該当PieceのTabsから接続者か被接続者かの有無を変更
            pieceVector_[indexOperatorPiece_]->GetTabsRef()[indexInPieceMineTab_].isConnectExecuter_ = true;
            // 該当Pieceをはめ込んだので固定
            pieceVector_[indexOperatorPiece_]->SetFixity(true);

            // 2群
            // 他Pieceの接続tabのisEntranceOpenをtrueに変更
            size_t elem{ pieceVector_[indexNoOperatorPiece_]->GetTabs()[indexInPieceOtherTab_].indexBlockVector_ };
            pieceVector_[indexNoOperatorPiece_]->GetBlocksPtr()->at(elem)->SetEntranceOpen(true);
            // 他PieceのTabsから接続状態の有無を変更
            pieceVector_[indexNoOperatorPiece_]->GetTabsRef()[indexInPieceOtherTab_].isConnected_ = true;
            // 他PieceのTabsから接続者か被接続者かの有無を変更
            pieceVector_[indexNoOperatorPiece_]->GetTabsRef()[indexInPieceOtherTab_].isConnectExecuter_ = false;

            // 3群
            // 他Pieceもはめ込んだことにする
            pieceVector_[indexNoOperatorPiece_]->SetFixity(true);
            // 該当Pieceの中心点等を変更したので、Update()を実行
            pieceVector_[indexOperatorPiece_]->Update();
            // 該当Pieceの接続tabのisEntranceOpenをtrueに変更 Update()内にEntranceをfalseにしてしまう関数が含まれているためこの位置
            pieceVector_[indexOperatorPiece_]->GetBlocksPtr()->at(operatorTabs_[indexInPieceMineTab_].indexBlockVector_)->SetEntranceOpen(true);
            // 該当Pieceの操作権を放棄
            pieceVector_[indexOperatorPiece_]->SetOperator(false);
            // 該当Pieceのtabsコピーを破棄
            operatorTabs_.clear();
            // 該当Pieceはめ込み可能か知らせるフラグをfalseに変更。
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
