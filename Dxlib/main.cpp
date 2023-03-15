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

// �E�B���h�E�̃^�C�g���ɕ\�����镶����
const char TITLE[] = "aaa: Recolor";

// �E�B���h�E����
const int WIN_WIDTH = 960;

// �E�B���h�E�c��
const int WIN_HEIGHT = 540;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine,
                   _In_ int nCmdShow) {
	// �E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);

	// �E�B���h�E�T�C�Y���蓮�ł͕ύX�������A
	// ���E�B���h�E�T�C�Y�ɍ��킹�Ċg��ł��Ȃ��悤�ɂ���
	SetWindowSizeChangeEnableFlag(FALSE, FALSE);

	// �^�C�g����ύX
	SetMainWindowText(TITLE);

	// ��ʃT�C�Y�̍ő�T�C�Y�A�J���[�r�b�g����ݒ�(���j�^�[�̉𑜓x�ɍ��킹��)
	SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);

	// ��ʃT�C�Y��ݒ�(�𑜓x�Ƃ̔䗦�Őݒ�)
	SetWindowSizeExtendRate(1.0);

	// ��ʂ̔w�i�F��ݒ肷��
	SetBackgroundColor(0x00, 0x00, 0x00);

	// DXlib�̏�����
	if (DxLib_Init() == -1) { return -1; }

	// (�_�u���o�b�t�@)�`���O���t�B�b�N�̈�͗��ʂ��w��
	SetDrawScreen(DX_SCREEN_BACK);

	// �摜�Ȃǂ̃��\�[�X�f�[�^�̕ϐ��錾�Ɠǂݍ���

	// �Q�[�����[�v�Ŏg���ϐ��̐錾
    std::unique_ptr<StageManager> stM{ std::make_unique<StageManager>() };
    std::unique_ptr<Stage> stage1{ std::make_unique<Stage>() };

    StageManager::LoadCSV(stage1.get(), "Resources/test.csv");
    StageManager::SetStage(stage1);

    Player player{ {250,50,},{Player::defaultWidth_,Player::defaultHeight_},Color::BLUE };

	// ��������
	YMath::Srand();

	// �p�[�e�B�N��
	std::unique_ptr<ParticleManager> particleMan = std::make_unique<ParticleManager>();
	particleMan->Initialize();
	BeaconDrawer::StaticInitialze(particleMan.get());
	PlayerDrawer::StaticInitialze(particleMan.get());
	FillterDrawer::StaticInitialze(particleMan.get());
	GateDrawer::StaticInitialze(particleMan.get());


	// �ŐV�̃L�[�{�[�h���p
	char keys[256] = {0};

	// 1���[�v(�t���[��)�O�̃L�[�{�[�h���
	char oldkeys[256] = {0};

	// �Q�[�����[�v
	while (true) {
        Input::Keyboard::Update();

		// ��ʃN���A
		ClearDrawScreen();
		//---------  ��������v���O�������L�q  ----------//

		// �X�V����
        player.Update();
        stM->Update();

		// �p�[�e�B�N���X�V
		particleMan->Update();

		// �`�揈��
        player.Draw();
        stM->Draw();

		// �p�[�e�B�N���`��
		particleMan->Draw();

		//---------  �����܂łɃv���O�������L�q  ---------//
		// (�_�u���o�b�t�@)����
		ScreenFlip();

		// 20�~���b�ҋ@(�^��60FPS)
		WaitTimer(20);

		// Windows�V�X�e�����炭�������������
		if (ProcessMessage() == -1) {
			break;
		}

		// ESC�L�[�������ꂽ�烋�[�v���甲����
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
	}
	// Dx���C�u�����I������
	DxLib_End();

	// ����I��
	return 0;
}
