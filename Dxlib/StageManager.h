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
    // 定数
    static constexpr int basicBlockSize_{ 32 };
    static constexpr int WHITE{ 0xffffff };
    static constexpr int BLACK{ 0x000000 };
    static constexpr int RED{ 0xff0000 };
    static constexpr int GREEN{ 0x00ff00 };
    static constexpr int YELLOW{ 0xffff00 };
    static constexpr int CYAN{ 0x00ffff };

    // 関数
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

    // 変数
    MOUSE::IntXY_t startPoint_{ 30,100 }; // 左上
    MOUSE::IntXY_t endPoint_{ 960,540 }; // 右下

    MOUSE::IntXY_t debugElemCursor_{ 0,0 }; // 配列のどの部分にカーソルがあるかを伝達
    MOUSE::IntXY_t debugResizeInfo_{ 0,0 }; // mapchipの要素数を記述した値に変更

    bool isResize_{ false };
    MOUSE::IntXY_t resizeVal_{ 0,0 };

    std::vector<std::vector<int>> mapchip_{};
    int targetNumber_{ 0 };

    int holdBlockNumber_{ 1 };

    int countExport_{ 0 };
};