#include "Input.h"
#include <DxLib.h>
char Input::Keyboard::keys_[256]{};
char Input::Keyboard::keysPre_[256]{};

void Input::Keyboard::Update(void)
{
    std::copy(std::begin(keys_), std::end(keys_), std::begin(keysPre_));

    // �ŐV�̃L�[�{�[�h�����擾
    GetHitKeyStateAll(keys_);
}