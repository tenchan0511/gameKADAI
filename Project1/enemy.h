//#pragma once

// 定数
#define ENEMY_MAX 10	// 敵キャラ数
#define ENEMY_SIZE_X 32	// 敵キャラ横サイズ
#define ENEMY_SIZE_Y 48 // 敵キャラ縦サイズ

//enum ENEMY_TYPE
//{
//	ENEMY_TYPE_NORMAL,
//	ENEMY_TYPE_FAST,
//	ENEMY_TYPE_SEARCH,
//	ENEMY_TYPE_MAX
//};

// プロトタイプ宣言
void EnemySystemInit(void);
bool EnemyGameInit(void);
void EnemyControl(XY playerPos);
void EnemyDrawInit(void);

// 敵の移動関数
