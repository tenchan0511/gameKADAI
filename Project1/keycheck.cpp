#include "DxLib.h"
#include "keycheck.h"

// �ϐ�
// �L�[����p
bool keyOld[KEY_ID_MAX];			// 1�t���[���O�̃L�[���
bool keyNew[KEY_ID_MAX];			// ���݂̃L�[���
bool keyDownTrigger[KEY_ID_MAX];	// �L�[�������̃g���K�[
bool keyUpTrigger[KEY_ID_MAX];		// �L�[�A�b�v���̃g���K�[

// �L�[����z��̏�����
void keyInit(void)
{
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyOld[keyID] = false;
		keyNew[keyID] = false;
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;
	}
}
// �L�[���擾
void keyCheck(void)
{
	// 1�t���[���O�̃L�[�����R�s�[
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyOld[keyID] = keyNew[keyID];
	}

	// ���݂̃L�[�����擾����
	keyNew[KEY_ID_SPACE] = CheckHitKey(KEY_INPUT_SPACE);
	// �V�����̂͂����ɒǉ�
	keyNew[KEY_ID_PAUSE] = CheckHitKey(KEY_INPUT_P);
	keyNew[KEY_ID_UP] = CheckHitKey(KEY_INPUT_W);
	keyNew[KEY_ID_RIGHT] = CheckHitKey(KEY_INPUT_D);
	keyNew[KEY_ID_DOWN] = CheckHitKey(KEY_INPUT_S);
	keyNew[KEY_ID_LEFT] = CheckHitKey(KEY_INPUT_A);

	//�g���K�[���̎擾
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		// �g���K�[���̏�����
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;

		// �g���K�[���̎擾
		if (!keyOld[keyID] && keyNew[keyID])
		{
			keyDownTrigger[keyID] = true;
		}

		if (keyOld[keyID] && !keyNew[keyID])
		{
			keyUpTrigger[keyID] = true;
		}
	}
}
