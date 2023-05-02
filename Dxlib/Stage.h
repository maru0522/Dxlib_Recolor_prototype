#pragma once
#include "Piece.h"

class Stage
{
public:
    // ��`
    static constexpr float detectRadius_{ 32.f };

    // �֐�
    Stage(void) {}

    void Update(void);
    void Draw(void);

    void AddPiece(Piece* ptr);
private:
    void InternalUpdatePieces(int index); // for�������炷����MiningOperatorPieceTabs���Ŏ��s����Update�֐�

    void MiningOperatorPieceTabs(void); // isOperator��true�ɂȂ��Ă�Piece��T��tab���R�s�[����֐� ���Y��Piece�͒P��ł���O��
    void ExplorateNearTabs(Vector2& recordPos); // �Y��Piece�ɕt������tab�̍��W������͈͓��ɂ��鑼piece��tab���W���������A���������v����ꍇ�ɊY��Piece�̒��S���W���A�t��tab�Ƒ�tab���d�Ȃ�ʒu�Ɏ�����������֐�

    void ConfirmOperatorPiecePos(const Vector2& pos);

    void SelectPieceForOperatorDebug(void);

    // �ϐ�
    std::vector<std::unique_ptr<Piece>> pieceVector_;
    size_t indexOperatorPiece_{};
    size_t indexNoOperatorPiece_{};
    size_t indexInPieceMineTab_{};
    size_t indexInPieceOtherTab_{};

    std::vector<Piece::Tab_t> operatorTabs_;

    bool isPossibleInPiece_{ false };
};

