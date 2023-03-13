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
}