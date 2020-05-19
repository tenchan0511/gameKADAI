#include "DxLib.h"
#include "main.h"
#include "enemy.h"
#include "player.h"
#include "stage.h"

// •Ï”
CHARACTER enemy1;
int enemy1Image[4][3];
int moveCnt;

void EnemySystemInit(void)
{
	
}

bool EnemyGameInit(void)
{
	bool rtnFlag = true;

	EnemySystemInit();	// “G‚Ì‰Šú‰»

	return rtnFlag;
}

void EnemyControl(XY playerPos)
{

}

void EnemyDrawInit(void)
{
	DrawGraph(enemy1.pos.x, enemy1.pos.y, enemy1Image[1][0], true);
}
