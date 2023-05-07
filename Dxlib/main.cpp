#include "DxLib.h"
#include <memory>
#include "Input.h"
#include "Piece.h"
#include "Stage.h"
#include "BasicBlock.h"
#include "Player.h"

// ウィンドウのタイトルに表示する文字列
const char TITLE[] = "aaa: タイトル";

// ウィンドウ横幅
const int WIN_WIDTH = 1280;

// ウィンドウ縦幅
const int WIN_HEIGHT = 720;

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
    //Piece piece{ Vector2{300,300}, Vector2{50,50} };
    //piece.RegisterBlock(new IBlock{ Vector2{20,20} });
    //piece.Register(new IBlock{ Vector2{-10,-10} });
    //piece.Register(new IBlock{ Vector2{5,5} });
    //piece.Register(new IBlock{ Vector2{50,50} });

    Stage stage{};

    Piece* piecePtr = new Piece{ {300,300},{5,5} };
    piecePtr->RegisterTab(true, 4, Piece::Dir::TOP);
    piecePtr->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ -12,-110 }, Vector2{ 2,60 });
    stage.AddPiece(piecePtr);

    Piece* piece2Ptr = new Piece{ {500,300},{3,3} };
    piece2Ptr->RegisterTab(true, 10, Piece::Dir::BOTTOM);
    stage.AddPiece(piece2Ptr);

    Piece* piece3Ptr = new Piece{ {780,400},{2,6} };
    piece3Ptr->RegisterTab(true, 15, Piece::Dir::LEFT);
    piece3Ptr->RegisterBlock(new BasicBlock{ Vector2{},Vector2{} }, Vector2{ 20,-15 }, Vector2{ 2,60 });
    stage.AddPiece(piece3Ptr);

    Player player{ &stage };
    player.SetPos(Vector2{ 200,200 });
    player.SetIndexPiece(0);

    // ゲームループで使う変数の宣言


    // ゲームループ
    while (true) {
        Input::Keyboard::Update();

        // 画面クリア
        ClearDrawScreen();
        //---------  ここからプログラムを記述  ----------//

        // 更新処理
        stage.Update();
        player.Update();
        //piece2.Update();

        // 描画処理
        stage.Draw();
        player.Draw();
        //piece2.Draw();

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
