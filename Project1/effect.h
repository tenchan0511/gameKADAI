//#pragma once
									// �t�F�[�h�����p
extern int fadeIn;
extern int fadeOut;
//extern int bright;

// �ꎞ��~����
extern bool pauseFlag;		// �ꎞ��~����(true:	)
extern int testcnt;

void EffectInit(void);				// �G�t�F�N�g�p������

// �V�[���J�ڊ֐�
bool FadeInScreen(int fadeStep);	// �t�F�[�h�C��(�߂�l�Ftrue �t�F�[�h�C�����Afalse �t�F�[�h�C���I��)
bool FadeOutScreen(int fadeStep);	// �t�F�[�h�A�E�g(�߂�l�Ftrue �t�F�[�h�A�E�g���Afalse�t�F�[�h�A�E�g�I��)
