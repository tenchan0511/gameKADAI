//#pragma once

// �萔
#define ENEMY_MAX 7	// �G�L������
#define ENEMY_SIZE_X 32	// �G�L�������T�C�Y
#define ENEMY_SIZE_Y 48 // �G�L�����c�T�C�Y

enum ENEMY_TYPE
{
	ENEMY_TYPE_NORMAL,
	ENEMY_TYPE_FAST,
	ENEMY_TYPE_SEARCH,
	ENEMY_TYPE_MAX
};

// �v���g�^�C�v�錾
void EnemySystemInit(void);
bool EnemyGameInit(void);
void EnemyControl(XY playerPos);
void EnemyDrawInit(int index);

// �G�̈ړ��֐�
int MoveEnemyX(CHARACTER* enemy, XY playerpos);
int MoveEnemyY(CHARACTER* enemy, XY playerpos);
int MoveEnemyXY(CHARACTER* enemy, XY playerpos);

extern CHARACTER enemy[ENEMY_MAX];
extern CHARACTER enemyindividual[ENEMY_TYPE_MAX];

bool PlayerHitCheck(XY ePos, int eSize);
