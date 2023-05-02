#pragma once
#include "Piece.h"

class Stage
{
public:
    // 定義
    static constexpr float detectRadius_{ 32.f };

    // 関数
    Stage(void) {}

    void Update(void);
    void Draw(void);

    void AddPiece(Piece* ptr);
private:
    void InternalUpdatePieces(int index); // for文を減らすためMiningOperatorPieceTabs内で実行するUpdate関数

    void MiningOperatorPieceTabs(void); // isOperatorがtrueになってるPieceを探しtabをコピーする関数 ※該当Pieceは単一である前提
    void ExplorateNearTabs(Vector2& recordPos); // 該当Pieceに付属するtabの座標から一定範囲内にある他pieceのtab座標を検索し、条件が合致する場合に該当Pieceの中心座標を、付属tabと他tabが重なる位置に自動調整する関数

    void ConfirmOperatorPiecePos(const Vector2& pos);

    void SelectPieceForOperatorDebug(void);

    // 変数
    std::vector<std::unique_ptr<Piece>> pieceVector_;
    size_t indexOperatorPiece_{};
    size_t indexNoOperatorPiece_{};
    size_t indexInPieceMineTab_{};
    size_t indexInPieceOtherTab_{};

    std::vector<Piece::Tab_t> operatorTabs_;

    bool isPossibleInPiece_{ false };
};

