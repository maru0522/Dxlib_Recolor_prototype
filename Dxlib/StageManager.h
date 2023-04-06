#pragma once
#include <array>
#include <vector>
#include <list>
#include <string>
#include <memory>
#include "Input.h"

class StageManager
{
public:
    // �萔
    static constexpr int basicBlockSize_{ 32 };
    static constexpr int WHITE{ 0xffffff };
    static constexpr int BLACK{ 0x000000 };
    static constexpr int RED{ 0xff0000 };
    static constexpr int GREEN{ 0x00ff00 };
    static constexpr int YELLOW{ 0xffff00 };
    static constexpr int CYAN{ 0x00ffff };

    // �֐�
    void Initialize(int width, int height);
    void Update(void);
    void Draw(void);

private:
    void DrawLattice(void);
    void DrawDebug(void);
    void DrawMapchip(void);

    void ClearMapchip(void);
    void Resize(void);
    void Export(void);

    void ControllBlockNumber(void);

    // �ϐ�
    MOUSE::IntXY_t startPoint_{ 30,100 }; // ����
    MOUSE::IntXY_t endPoint_{ 960,540 }; // �E��

    MOUSE::IntXY_t debugElemCursor_{ 0,0 }; // �z��̂ǂ̕����ɃJ�[�\�������邩��`�B
    MOUSE::IntXY_t debugResizeInfo_{ 0,0 }; // mapchip�̗v�f�����L�q�����l�ɕύX

    bool isResize_{ false };
    MOUSE::IntXY_t resizeVal_{ 0,0 };

    std::vector<std::vector<int>> mapchip_{};
    int targetNumber_{ 0 };

    int holdBlockNumber_{ 1 };

    int countExport_{ 0 };
};