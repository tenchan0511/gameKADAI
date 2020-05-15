#pragma once

// ��`
#define PLAYER_V 8			// �v���C���[�c������
#define PLAYER_H 12			// �v���C���[��������
#define PLAYER_SIZE_Y 48	// �v���C���[�c�T�C�Y
#define PLAYER_SIZE_X 32	// �v���C���[���T�C�Y
#define PLAYER_SPEED 1		// �v���C���[�X�s�[�h

// �v���g�^�C�v�錾
void PlayerSystemInit(void);	// �V�X�e��
bool PlayerGameInit(void);		// �V�[��
void PlayerGameDraw(void);		// �`��
void PlayerControl(void);			// �v���C���[�̈ړ�
