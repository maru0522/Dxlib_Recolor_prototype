#pragma once
#include <array>

namespace Input {
    class Keyboard
    {
    public: 
        // �֐�
        static void Update(void);

        // �������u��
        static bool IsTrigger(char key) { return !keysPre_[key] && keys_[key]; }

        // ������Ă���Ƃ�
        static bool IsDown(char key) { return keys_[key]; }

        // �����ꂽ�u��
        static bool IsReleased(char key) { return keysPre_[key] && !keys_[key]; }

    private:
        // �ϐ�
        static char keys_[256];
        static char keysPre_[256];
    };

    class Mouse
    {
    public:
        // ��`
        enum class Click
        {
            LEFT,
            RIGHT,
            CENTER,
        };

        struct IntXY_t
        {
            int mx_{};
            int my_{};
        };

        // �֐�
        static void Update(void);

        // �������u��
        static bool IsTrigger(const Click& clickSide) { return !buttonsPre_[static_cast<int>(clickSide)] && buttons_[static_cast<int>(clickSide)]; }

        // ������Ă���Ƃ�
        static bool IsDown(const Click& clickSide) { return buttons_[static_cast<int>(clickSide)]; }

        // �����ꂽ�u��
        static bool IsReleased(const Click& clickSide) { return buttonsPre_[static_cast<int>(clickSide)] && !buttons_[static_cast<int>(clickSide)]; }

        // �J�[�\���̍��W�擾
        static inline const IntXY_t& GetPos(void) { return pos_; }

    private:
        // �ϐ�
        static IntXY_t pos_;
        static int mouseInput_;
        static char buttons_[3];
        static char buttonsPre_[3];
    };
}

using KEY = Input::Keyboard;
using MOUSE = Input::Mouse;