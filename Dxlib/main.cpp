#include "DxLib.h"
#include <memory>
#include "StageManager.h"
#include "staging/ParticleManager.h"
#include "staging/MathUtillity.h"
#include "staging/PlayerDrawer.h"
#include "staging/FillterDrawer.h"
#include "staging/GateDrawer.h"
#include "Input.h"
#include "Player.h"
#include "Filter.h"
#include "User.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "aaa: Recolor";

// ウィンドウ横幅
const int WIN_WIDTH = 960;

// ウィンドウ縦幅
const int WIN_HEIGHT = 540;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
    _In_ int nCmdShow) {
    // ウィンドウモードに設定
    ChangeWindowMode(TRUE);

    // ウィンドウサイズを手動では変更させず、
    // かつウィンドウサイズに合わせて拡大できないようにする
    SetWindowSizeChangeEnableFlag(FALSE, FALSE);

    // タイトルを変更
    SetMainWindowText(TITLE);

    // 画面サイズの最大サイズ、カラービット数を設定(モニターの解像度に合わせる)
    SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

    // 画面サイズを設定(解像度との比率で設定)
    SetWindowSizeExtendRate(1.0);

    // 画面の背景色を設定する
    SetBackgroundColor(0x00, 0x00, 0x00);

    // DXlibの初期化
    if (DxLib_Init() == -1) { return -1; }

    // (ダブルバッファ)描画先グラフィック領域は裏面を指定
    SetDrawScreen(DX_SCREEN_BACK);

    // 画像などのリソースデータの変数宣言と読み込み

    // ゲームループで使う変数の宣言
    std::unique_ptr<StageManager> stM{ std::make_unique<StageManager>() };
    std::unique_ptr<Stage> stage1{ std::make_unique<Stage>() };

    StageManager::LoadCSV(stage1.get(), "Resources/Stages/test.csv");
    StageManager::SetStage(stage1);

    User user{ "Resources/UserSettings/user1.csv" };

    // 乱数生成
    YMath::Srand();

    // パーティクル
    std::unique_ptr<ParticleManager> particleMan = std::make_unique<ParticleManager>();
    particleMan->Initialize();
    BeaconDrawer::StaticInitialze(particleMan.get());
    PlayerDrawer::StaticInitialze(particleMan.get());
    FillterDrawer::StaticInitialze(particleMan.get());
    GateDrawer::StaticInitialze(particleMan.get());

    // ゲームループ
    while (true) {
        Input::Keyboard::Update();

        // 画面クリア
        ClearDrawScreen();
        //---------  ここからプログラムを記述  ----------//

        // 更新処理
        user.Update();
        stM->Update();

        // パーティクル更新
        particleMan->Update();

        // 描画処理
        user.Draw();
        stM->Draw();

        // パーティクル描画
        particleMan->Draw();

        //---------  ここまでにプログラムを記述  ---------//
        // (ダブルバッファ)裏面
        ScreenFlip();

        // 20ミリ秒待機(疑似60FPS)
        WaitTimer(20);

        // Windowsシステムからくる情報を処理する
        if (ProcessMessage() == -1) {
            break;
        }

        // ESCキーが押されたらループから抜ける
        if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
            break;
        }
    }
    // Dxライブラリ終了処理
    DxLib_End();

    // 正常終了
    return 0;
}
