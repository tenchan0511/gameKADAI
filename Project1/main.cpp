#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"

// �ϐ�
int sceneCounter;
SCN_ID scnID;		// �V�[���Ǘ��p
SCN_ID scnIDpre;

// Winmain�֐�
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if (!SystemInit())
	{
		return 0;
	}
	// �Q�[�����[�v
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		keyCheck();

		ClsDrawScreen(); // ��ʏ���

		if (scnID != scnIDpre)
		{
			sceneCounter = 0;
		}
		scnIDpre = scnID;

		switch (scnID)
		{
		case SCN_ID_INIT:
			InitScene();
			scnID = SCN_ID_TITLE;
			break;
		case SCN_ID_TITLE:
			if (fadeIn)
			{				
				if (!FadeInScreen(5)){} // �t�F�[�h�C�����I�������̏���������
			}
			if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{// �t�F�[�h�A�E�g���I�������̏���������
					fadeIn = true;
					scnID = SCN_ID_GAME;
				}
			}
			TitleScene();
			break;
		case SCN_ID_GAME:
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {} // �t�F�[�h�C�����I�������̏���������
			}
			if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{// �t�F�[�h�A�E�g���I�������̏���������
					fadeIn = true;
					scnID = SCN_ID_GAMEOVER;
				}
			}
			GameMain();
			break;
		case SCN_ID_GAMEOVER:
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {} // �t�F�[�h�C�����I�������̏���������
			}
			if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{// �t�F�[�h�A�E�g���I�������̏���������
					fadeIn = true;
					scnID = SCN_ID_INIT;
				}
			}
			GameOverScene();
			break;
		default:
			AST();
			break;
		}

		// ���C������

		sceneCounter++;

		ScreenFlip();	 // ����ʂ�\��ʂɏu�ԃR�s�[
	}
	DxLib_End();		// DX���C�u�����̏I������
	return 0;			// ���̃v���O�����̏I��

}

// �V�X�e��������
bool SystemInit(void)
{
	// �V�X�e������
	SetWindowText("BaseProject");

	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16); // 640�~480�h�b�g65536�F���[�h�ɐݒ�
	ChangeWindowMode(true);							// true:window false:�t���X�N���[��
	if (DxLib_Init() == -1) return true;			// DX���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK);					// �ЂƂ܂��o�b�N�o�b�t�@�ɕ`��

	keyInit();			// �L�[���̏�����
	StageSystemInit();	// �X�e�[�W�̏�����
	PlayerSystemInit();	// �v���C���[�̏�񏉊���

	// �O���t�B�b�N�̓o�^


	// �ϐ�������
	sceneCounter = 0;
	scnID = SCN_ID_INIT;

	EffectInit();			// �G�t�F�N�g�p����������
	
	return true;
}

// �������V�[��
void InitScene(void)
{
	StageInit();
	PlayerGameInit();
}

// �^�C�g���V�[��
void TitleScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		/*scnID = SCN_ID_GAME;*/
		fadeOut = true;
	}
	TitleDraw();
}
void TitleDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "TitleCounter = %d", sceneCounter);

	DrawBox(100, 100, 700, 500, GetColor(0, 255, 0), true);
}

// �Q�[���V�[��
void GameMain(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		/*scnID = SCN_ID_GAMEOVER;*/
		fadeOut = true;
	}
	
	if (keyDownTrigger[KEY_ID_PAUSE])
	{
		if (pauseFlag)
		{
			pauseFlag = false;
			SetDrawBright(255, 255, 255);
		}
		else
		{
			pauseFlag = true;
			SetDrawBright(127, 127, 127);
		}
	}
	if (!pauseFlag)
	{
		testcnt++;

		PlayerControl();
	}
	GameDraw();
}

void GameDraw(void)
{
	StageDrawInit();
	PlayerGameDraw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "GameCounter = %d", sceneCounter);
	DrawFormatString(50, 50, GetColor(255, 255, 255), "test = %d", testcnt);

	/*DrawBox(100, 100, 700, 500, GetColor(255, 0, 0), true);*/

	// PAUSE�`��
	if (pauseFlag)
	{
		DrawFormatString(375, 285, GetColor(255, 255, 255), "PAUSE");
	}
}

// �Q�[���I�[�o�[�V�[��
void GameOverScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		/*scnID = SCN_ID_TITLE;*/
		fadeOut = true;
	}

	GameOverDraw();
}
void GameOverDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "GameOverCounter = %d", sceneCounter);

	DrawBox(100, 100, 700, 500, GetColor(0, 0, 255), true);
}

