#pragma once

// ��`
#define CHIP_SIZE_X 32 // �}�b�v�`�b�v������̉��T�C�Y	
#define CHIP_SIZE_Y 32 // �}�b�v�`�b�v������̏c�T�C�Y	
#define CHIP_X 8	   // ���̉摜������
#define CHIP_Y 96	   // �c�̉摜������
#define MAP_X 25	   // �X�e�[�W�̉��T�C�Y�i�`�b�v���j
#define MAP_Y 20	   // �X�e�[�W�̏c�T�C�Y�i�`�b�v���j

// �v���g�^�C�v�錾
bool StageSystemInit(void);
void StageInit(void);
void StageDrawInit(void);
