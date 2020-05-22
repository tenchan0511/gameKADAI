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
int moveDir;

void EnemySystemInit(void)
{
	// enemy1
	enemyindividual[ENEMY_TYPE_NORMAL].charType = ENEMY_TYPE_NORMAL;
	enemyindividual[ENEMY_TYPE_NORMAL].size.x = ENEMY_SIZE_X;
	enemyindividual[ENEMY_TYPE_NORMAL].size.y = ENEMY_SIZE_Y;
	enemyindividual[ENEMY_TYPE_NORMAL].moveSpeed = 1;
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
	enemyindividual[ENEMY_TYPE_FAST].charType = ENEMY_TYPE_FAST;
	enemyindividual[ENEMY_TYPE_FAST].size.x = ENEMY_SIZE_X;
	enemyindividual[ENEMY_TYPE_FAST].size.y = ENEMY_SIZE_Y;
	enemyindividual[ENEMY_TYPE_FAST].moveSpeed = 4;
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
	enemyindividual[ENEMY_TYPE_SEARCH].charType = ENEMY_TYPE_SEARCH;
	enemyindividual[ENEMY_TYPE_SEARCH].size.x = ENEMY_SIZE_X;
	enemyindividual[ENEMY_TYPE_SEARCH].size.y = ENEMY_SIZE_Y;
	enemyindividual[ENEMY_TYPE_SEARCH].moveSpeed = 2;
	LoadDivGraph(
		"image/enemy02.png",
		12,
		3,
		4,
		ENEMY_SIZE_X,
		ENEMY_SIZE_Y,
		&enemyImage[ENEMY_TYPE_SEARCH][0]
	);

	moveDir = 0;

	for (int y = 0; y < ENEMY_TYPE_MAX; y++)
	{
		enemyindividual[y].moveDir = DIR_DOWN;
		enemyindividual[y].offsetSize.x = enemyindividual[y].size.x / 2;
		enemyindividual[y].offsetSize.y = enemyindividual[y].size.y / 2;
		enemyindividual[y].pos.x = enemyindividual[y].offsetSize.x;
		enemyindividual[y].pos.y = enemyindividual[y].offsetSize.y;
		enemyindividual[y].animCnt = 0;
	}

	enemy[0].charType = enemyindividual[ENEMY_TYPE_NORMAL].charType;
	enemy[1].charType = enemyindividual[ENEMY_TYPE_NORMAL].charType;
	enemy[2].charType = enemyindividual[ENEMY_TYPE_NORMAL].charType;
	enemy[3].charType = enemyindividual[ENEMY_TYPE_FAST].charType;
	enemy[4].charType = enemyindividual[ENEMY_TYPE_FAST].charType;
	enemy[5].charType = enemyindividual[ENEMY_TYPE_SEARCH].charType;
	enemy[6].charType = enemyindividual[ENEMY_TYPE_SEARCH].charType;

	enemy[0].pos.x = 100;
	enemy[0].pos.y = 100;
	enemy[1].pos.x = 200;
	enemy[1].pos.y = 200;
	enemy[2].pos.x = 200;
	enemy[2].pos.y = 100;
	enemy[3].pos.x = 100;
	enemy[3].pos.y = 200;
	enemy[4].pos.x = 300;
	enemy[4].pos.y = 300;
	enemy[5].pos.x = 400;
	enemy[5].pos.y = 400;
	enemy[6].pos.x = 300;
	enemy[6].pos.y = 400;

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		enemy[i].moveDir = enemyindividual[enemy[i].charType].moveDir = DIR_DOWN;
		enemy[i].moveSpeed = enemyindividual[enemy[i].charType].moveSpeed;
		enemy[i].offsetSize.x = enemyindividual[enemy[i].charType].offsetSize.x;
		enemy[i].offsetSize.y = enemyindividual[enemy[i].charType].offsetSize.y;
		enemy[i].size.x = enemyindividual[enemy[i].charType].size.x;
		enemy[i].size.y = enemyindividual[enemy[i].charType].size.y;
	}
	moveCnt = 0;
}

bool EnemyGameInit(void)
{
	bool rtnFlag = true;

	EnemySystemInit();	// ìGÇÃèâä˙âª

	return rtnFlag;
}

void EnemyControl(XY playerPos)
{
	moveCnt++;
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		switch (enemy[i].charType)
		{
		case ENEMY_TYPE_NORMAL:
			if ((moveCnt / 60) % 2 == 0)
			{
				/*if (MoveEnemyX(&enemy[i], playerPos) == 0)
				{
					MoveEnemyY(&enemy[i], playerPos);
				}*/
				MoveEnemyXY(&enemy[i], playerPos);
			}
			break;
		case ENEMY_TYPE_FAST:
			
			if (moveCnt % 30 == 0)
			{
				moveDir = GetRand(DIR_MAX - 1);
			}
			if ((moveCnt / 30) % 2 == 0)
			{
				MoveEnemyRandom(&enemy[i], moveDir);
				/*if (MoveEnemyY(&enemy[i], playerPos) == 0)
				{
					MoveEnemyX(&enemy[i], playerPos);
				}*/
			}
			break;
		case ENEMY_TYPE_SEARCH:
			if ((moveCnt / 45) % 2 == 0)
			{
				MoveEnemyXY(&enemy[i], playerPos);
			}
			break;
		default:
			break;
		}
		// ï\é¶èáÇ…ÉfÅ[É^Çäiî[
		AddCharOrder(CHARACTER_ENEMY, i, enemy[i].pos.y + enemy[i].size.y);
	}
}

void EnemyDrawInit(int index)
{
	
	enemy[index].animCnt++;

	DrawGraph(
		enemy[index].pos.x,
		enemy[index].pos.y,
		enemyImage[enemy[index].charType][(enemy[index].moveDir * 3) + ((enemy[index].animCnt / 10) % 3)],
		true);
	
}

int MoveEnemyX(CHARACTER* enemy, XY playerpos)
{
	int speed = (*enemy).moveSpeed;

	int diff = playerpos.x - (*enemy).pos.x;
	if (diff >= 0)
	{
		speed = (diff < speed) ? diff : speed;

		// à⁄ìÆ
		(*enemy).pos.x += speed;
		(*enemy).moveDir = DIR_RIGHT;
	}
	else
	{
		speed = (-diff < speed) ? -diff : speed;

		(*enemy).pos.x -= speed;
		(*enemy).moveDir = DIR_LEFT;
	}
	return speed;
}

int MoveEnemyY(CHARACTER* enemy, XY playerpos)
{
	int speed = (*enemy).moveSpeed;
	int diff = playerpos.y - (*enemy).pos.y;//()Ç≈óDêÊèáà ÇéwíË
	if (diff >= 0)
	{
		// speedÇïœÇ¶ÇÈÇ©
		speed = (diff < speed) ? diff : speed;

		// à⁄ìÆ
		(*enemy).pos.y += speed;
		(*enemy).moveDir = DIR_DOWN;
	}
	else
	{
		speed = (-diff < speed) ? -diff : speed;

		(*enemy).pos.y -= speed;
		(*enemy).moveDir = DIR_UP;
	}
	return speed;
}

int MoveEnemyXY(CHARACTER* enemy, XY playerpos)
{
	int speed = (*enemy).moveSpeed;
	int diffX = playerpos.x - (*enemy).pos.x;
	int diffY = playerpos.y - (*enemy).pos.y;

	// ãóó£ÇîªífÇµÇƒà⁄ìÆï˚å¸ÇåàÇﬂÇÈ
	if (abs(diffX) > abs(diffY))
	{
		speed = MoveEnemyX(enemy, playerpos);
	}
	else
	{
		speed = MoveEnemyY(enemy, playerpos);
	}

	return speed;
}

bool PlayerHitCheck(XY ePos, int eSize)
{
	for (int en = 0; en < ENEMY_MAX; en++)
	{
		// ìGÇ∆ÇÃîªíË
		if ((enemy[en].pos.x - enemy[en].size.x / 2 < ePos.x + eSize)
			&& (enemy[en].pos.x + enemy[en].size.x / 2 > ePos.x)
			&& (enemy[en].pos.y + enemy[en].size.y / 2 > ePos.y + eSize)
			&& (enemy[en].pos.y + enemy[en].size.y / 2 > ePos.y))
		{
			// ìñÇΩÇË
			return true;
		}
	}
	return false;
}

int MoveEnemyRandom(CHARACTER* enemy, int moveDir)
{
	int speed = (*enemy).moveSpeed;
	
	switch (moveDir)
	{
	case DIR_DOWN:
		// à⁄ìÆ
		(*enemy).pos.y += speed;
		(*enemy).moveDir = DIR_DOWN;
		break;
	case DIR_LEFT:
		// à⁄ìÆ
		(*enemy).pos.x -= speed;
		(*enemy).moveDir = DIR_LEFT;
		break;
	case DIR_RIGHT:
		// à⁄ìÆ
		(*enemy).pos.x += speed;
		(*enemy).moveDir = DIR_RIGHT;
		break;
	case DIR_UP:
		// à⁄ìÆ
		(*enemy).pos.y -= speed;
		(*enemy).moveDir = DIR_UP;
		break;
	default:
		break;
	}
	return speed;
}
