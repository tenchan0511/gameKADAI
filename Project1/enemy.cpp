#include "DxLib.h"
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "stage.h"

// ïœêî
CHARACTER enemy[ENEMY_MAX];
CHARACTER enemyindividual[ENEMY_TYPE_MAX];
int enemyImage[ENEMY_TYPE_MAX][12];
int moveCnt;

void EnemySystemInit(void)
{
	// enemy1
	enemyindividual[ENEMY_TYPE_NORMAL].size.x = ENEMY_SIZE_X;
	enemyindividual[ENEMY_TYPE_NORMAL].size.y = ENEMY_SIZE_Y;
	enemyindividual[ENEMY_TYPE_NORMAL].moveSpeed = 2;
	LoadDivGraph(
		"image/enemy01.png",
		12,
		3,
		4,
		ENEMY_SIZE_X,
		ENEMY_SIZE_Y,
		&enemyImage[ENEMY_TYPE_NORMAL][0]
	);

	// enemy2
	enemyindividual[ENEMY_TYPE_FAST].size.x = ENEMY_SIZE_X;
	enemyindividual[ENEMY_TYPE_FAST].size.y = ENEMY_SIZE_Y;
	enemyindividual[ENEMY_TYPE_FAST].moveSpeed = 5;
	LoadDivGraph(
		"image/enemy03.png",
		12,
		3,
		4,
		ENEMY_SIZE_X,
		ENEMY_SIZE_Y,
		&enemyImage[ENEMY_TYPE_FAST][0]
	);

	// enemy3
	enemyindividual[ENEMY_TYPE_SEARCH].size.x = ENEMY_SIZE_X;
	enemyindividual[ENEMY_TYPE_SEARCH].size.y = ENEMY_SIZE_Y;
	enemyindividual[ENEMY_TYPE_SEARCH].moveSpeed = 3;
	LoadDivGraph(
		"image/enemy02.png",
		12,
		3,
		4,
		ENEMY_SIZE_X,
		ENEMY_SIZE_Y,
		&enemyImage[ENEMY_TYPE_SEARCH][0]
	);

	for (int y = 0; y < ENEMY_TYPE_MAX; y++)
	{
		enemyindividual[y].moveDir = DIR_DOWN;
		enemyindividual[y].offsetSize.x = enemyindividual[y].size.x / 2;
		enemyindividual[y].offsetSize.y = enemyindividual[y].size.y / 2;

	}
}

bool EnemyGameInit(void)
{
	bool rtnFlag = true;

	EnemySystemInit();	// ìGÇÃèâä˙âª

	return rtnFlag;
}

void EnemyControl(XY playerPos)
{

}

void EnemyDrawInit(void)
{
	DrawGraph(
		enemyindividual[ENEMY_TYPE_NORMAL].pos.x, 
		enemyindividual[ENEMY_TYPE_NORMAL].pos.y,
		enemyImage[ENEMY_TYPE_NORMAL][0],
		true);
}
