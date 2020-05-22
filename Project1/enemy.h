//#pragma once

// 定数
#define ENEMY_MAX 7	// 敵キャラ数
#define ENEMY_SIZE_X 32	// 敵キャラ横サイズ
#define ENEMY_SIZE_Y 48 // 敵キャラ縦サイズ

enum ENEMY_TYPE
{
	ENEMY_TYPE_NORMAL,
	ENEMY_TYPE_FAST,
	ENEMY_TYPE_SEARCH,
	ENEMY_TYPE_MAX
};

// プロトタイプ宣言
void EnemySystemInit(void);
bool EnemyGameInit(void);
void EnemyControl(XY playerPos);
void EnemyDrawInit(int index);

// 敵の移動関数
int MoveEnemyX(CHARACTER* enemy, XY playerpos);
int MoveEnemyY(CHARACTER* enemy, XY playerpos);
int MoveEnemyXY(CHARACTER* enemy, XY playerpos);

extern CHARACTER enemy[ENEMY_MAX];
extern CHARACTER enemyindividual[ENEMY_TYPE_MAX];

bool PlayerHitCheck(XY ePos, int eSize);
