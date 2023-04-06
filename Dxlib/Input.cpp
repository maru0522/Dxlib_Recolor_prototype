#include "Input.h"
#include <DxLib.h>
char Input::Keyboard::keys_[256]{};
char Input::Keyboard::keysPre_[256]{};

void Input::Keyboard::Update(void)
{
    std::copy(std::begin(keys_), std::end(keys_), std::begin(keysPre_));

    // 最新のキーボード情報を取得
    GetHitKeyStateAll(keys_);
}


Input::Mouse::IntXY_t Input::Mouse::pos_;
int Input::Mouse::mouseInput_;
char Input::Mouse::buttons_[3];
char Input::Mouse::buttonsPre_[3];

void Input::Mouse::Update(void)
{
    // 1フレーム前の古い情報を記録する
    std::copy(std::begin(buttons_), std::end(buttons_), std::begin(buttonsPre_));

    mouseInput_ = GetMouseInput();

    // 座標を記録
    GetMousePoint(&pos_.mx_, &pos_.my_);

    for (int i = 0; i < (int)std::size(buttons_); i++) {
        // マウスのクリック入力がない場合
        if ((mouseInput_ & 1 << i) == 0) {
            // 1フレーム前に入力があった場合、値を0にする。 ※1フレーム前の古い情報を更新している
            if (buttons_[i] < 0) buttons_[i] = 0;
        }
        // マウスのクリック入力がある場合。
        else
        {
            // 値を1にする。
            buttons_[i]++;
        }
    }
}
