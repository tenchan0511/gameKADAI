#include "DxLib.h"
#include "effect.h"

int fadeIn;			// �t�F�[�h�C��
int fadeOut;		// �t�F�[�h�A�E�g
int bright;

// �ꎞ��~����
bool pauseFlag;		// �ꎞ��~����(true:	)
int testcnt;

// �G�t�F�N�g�p����������
void EffectInit(void)
{
	// �ꎞ��~�����p
	pauseFlag = false;

	// �t�F�[�h�����p
	fadeIn = true;
	fadeOut = false;
	bright = 0;
}

// �V�[���J�ڊ֐�
// �t�F�[�h�C��
bool FadeInScreen(int fadeStep)
{
	if (bright <= 255)
	{
		SetDrawBright(bright, bright, bright);
		bright += fadeStep;
		return true;	// �߂�l
	}
	else
	{
		SetDrawBright(255, 255, 255);
		fadeIn = false;
		bright = 0;
		return false;	// �߂�l
	}
}
// �t�F�[�h�A�E�g
bool FadeOutScreen(int fadeStep)
{
	if (bright <= 255)
	{
		SetDrawBright(255 - bright, 255 - bright, 255 - bright);
		bright += fadeStep;
		return true;	// �߂�l
	}
	else
	{
		SetDrawBright(0, 0, 0);
		fadeOut = false;
		bright = 0;
		return false;	// �߂�l
	}
}
