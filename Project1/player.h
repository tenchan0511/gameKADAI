//#pragma once

// ��`
#define PLAYER_V 4			// �v���C���[�c������
#define PLAYER_H 3			// �v���C���[��������
#define PLAYER_SIZE_Y 48	// �v���C���[�c�T�C�Y
#define PLAYER_SIZE_X 32	// �v���C���[���T�C�Y
#define PLAYER_SPEED 4		// �v���C���[�X�s�[�h

// �v���g�^�C�v�錾
void PlayerSystemInit(void);	// �V�X�e��
bool PlayerGameInit(void);		// �V�[��
void PlayerGameDraw(void);		// �`��
XY PlayerControl(void);			// �v���C���[�̈ړ�
