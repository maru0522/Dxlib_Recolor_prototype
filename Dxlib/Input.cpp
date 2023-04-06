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


Input::Mouse::IntXY_t Input::Mouse::pos_;
int Input::Mouse::mouseInput_;
char Input::Mouse::buttons_[3];
char Input::Mouse::buttonsPre_[3];

void Input::Mouse::Update(void)
{
    // 1�t���[���O�̌Â������L�^����
    std::copy(std::begin(buttons_), std::end(buttons_), std::begin(buttonsPre_));

    mouseInput_ = GetMouseInput();

    // ���W���L�^
    GetMousePoint(&pos_.mx_, &pos_.my_);

    for (int i = 0; i < (int)std::size(buttons_); i++) {
        // �}�E�X�̃N���b�N���͂��Ȃ��ꍇ
        if ((mouseInput_ & 1 << i) == 0) {
            // 1�t���[���O�ɓ��͂��������ꍇ�A�l��0�ɂ���B ��1�t���[���O�̌Â������X�V���Ă���
            if (buttons_[i] < 0) buttons_[i] = 0;
        }
        // �}�E�X�̃N���b�N���͂�����ꍇ�B
        else
        {
            // �l��1�ɂ���B
            buttons_[i]++;
        }
    }
}
