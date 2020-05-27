#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"

// �萔
#define DRAW_ORDER_MAX			ENEMY_MAX + 1

struct DRAW_ORDER
{
	CHARACTER_TYPE characterType;	// �L�����̎��
	int index;					// �e�L�����̓Y����
	int y;						// �L�����̑���Y���W
};

// �ϐ�
int sceneCounter;
SCN_ID scnID;		// �V�[���Ǘ��p
SCN_ID scnIDpre;

// �\���\�[�g�p
int drawOrderCnt;							// List�Ɋi�[���ꂽ�f�[�^��
DRAW_ORDER drawOrderList[DRAW_ORDER_MAX];	// �\�[�g�p�z��

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
	SetWindowText("Project1");

	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16); // 640�~480�h�b�g65536�F���[�h�ɐݒ�
	ChangeWindowMode(true);							// true:window false:�t���X�N���[��
	if (DxLib_Init() == -1) return true;			// DX���C�u��������������
	SetDrawScreen(DX_SCREEN_BACK);					// �ЂƂ܂��o�b�N�o�b�t�@�ɕ`��

	keyInit();			// �L�[���̏�����
	StageSystemInit();	// �X�e�[�W�̏�����
	PlayerSystemInit();	// �v���C���[�̏�񏉊���
	EnemySystemInit();	// �G�̏�����

	// �O���t�B�b�N�̓o�^


	// �ϐ�������
	sceneCounter = 0;
	scnID = SCN_ID_INIT;

	// �z��̏�����
	drawOrderCnt = 0;
	for (int i = 0; i < DRAW_ORDER_MAX; i++)
	{
		// �z��̏�����
		drawOrderList[i].characterType = CHARACTER_MAX;
		drawOrderList[i].index = 0;
		drawOrderList[i].y = 0;
	}

	EffectInit();			// �G�t�F�N�g�p����������
	
	return true;
}

// �������V�[��
void InitScene(void)
{
	StageInit();
	PlayerGameInit();
	EnemyGameInit();
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
	XY playerPos;
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
		// �z��̏�����
		drawOrderCnt = 0;
		for (int i = 0; i < DRAW_ORDER_MAX; i++)
		{
			// �z��̏�����
			drawOrderList[i].characterType = CHARACTER_MAX;
			drawOrderList[i].index = 0;
			drawOrderList[i].y = 0;
		}

		playerPos = PlayerControl();
		EnemyControl(playerPos);

		// �v���C���[�ƂƓG�Ƃ̓����蔻��
		if (PlayerHitCheck(playerPos, 12))
		{
			if (!mutekiFlag)
			{
				// ������
				playerLife--;
				mutekiFlag = true;
			}
		}
	}
	GameDraw();
}

void GameDraw(void)
{
	StageDrawInit();

	for (int i = 0; i < drawOrderCnt; i++)
	{
		switch (drawOrderList[i].characterType)
		{
		case CHARACTER_ENEMY:		// �G�̕`��
			EnemyDrawInit(drawOrderList[i].index);
			break;
		case CHARACTER_PLAYER:
			PlayerGameDraw();		// �v���C���[�̕`��
			break;
		default:
			break;
		}
	}
	/*PlayerGameDraw();
	EnemyDrawInit();*/

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

void AddCharOrder(CHARACTER_TYPE characterType, int index, int y)
{
	int insertIndex = drawOrderCnt;// �}���ꏊ�̔z��̓Y����

	// 1.���X�g���̃f�[�^�ƈ�����Y���W���r���đ}���ꏊ�����߂�
	for (int dol = 0; dol < drawOrderCnt; dol++)	// ���ׂẴ��X�g�f�[�^��
	{
		if (y < drawOrderList[dol].y)	//���X�g�̃f�[�^�ƈ�����Y���r
		{
			insertIndex = dol;// �}���ꏊ�̔z��̓Y����
			break;
		}
	}

	// 2.�}���ꏊ�����܂����̂ŁA�}���ꏊ���󂯂邽�߂ɂق��̃f�[�^���ړ�������
	for (int dol = drawOrderCnt; dol > insertIndex; dol--)
	{
		// �f�[�^���R�s�[
		drawOrderList[dol] = drawOrderList[dol - 1];
	}

	// 3.�}���ꏊ�Ƀf�[�^��ǉ�(�z��ɒǉ�)
	drawOrderList[insertIndex].characterType = characterType;
	drawOrderList[insertIndex].index = index;
	drawOrderList[insertIndex].y = y;
	drawOrderCnt++;
}
