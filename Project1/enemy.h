//#pragma once

// �萔
#define ENEMY_MAX 10	// �G�L������
#define ENEMY_SIZE_X 32	// �G�L�������T�C�Y
#define ENEMY_SIZE_Y 48 // �G�L�����c�T�C�Y

//enum ENEMY_TYPE
//{
//	ENEMY_TYPE_NORMAL,
//	ENEMY_TYPE_FAST,
//	ENEMY_TYPE_SEARCH,
//	ENEMY_TYPE_MAX
//};

// �v���g�^�C�v�錾
void EnemySystemInit(void);
bool EnemyGameInit(void);
void EnemyControl(XY playerPos);
void EnemyDrawInit(void);

// �G�̈ړ��֐�
