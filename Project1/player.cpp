#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "player.h"
#include "effect.h"

CHARACTER player;
int playerImage[4][3];

void PlayerSystemInit(void)
{
	LoadDivGraph(
		"image/school01.png",
		12,
		PLAYER_V,
		PLAYER_H,
		PLAYER_SIZE_X,
		PLAYER_SIZE_Y,
		&playerImage[0][0]
	);

	player.moveDir = DIR_DOWN;				// キャラの向き
	player.pos.x = 300;						// プレイヤーの初期位置
	player.pos.y = 500;						// プレイヤーの初期位置
	player.size.x = PLAYER_SIZE_X;			// プレイヤーの横サイズ
	player.size.y = PLAYER_SIZE_Y;			// プレイヤーの縦サイズ
	player.offsetSize.x = player.size.x / 2;// プレイヤーの座標
	player.offsetSize.y = player.size.y / 2;// プレイヤーの座標
	player.moveSpeed = PLAYER_SPEED;		// プレイヤーのスピード
	player.life = 3;						// プレイヤーの残機
	player.animCnt = 0;						// キャラのアニメーションカウンタ

}

bool PlayerGameInit(void)
{
	bool rtnFlag = true;

	PlayerSystemInit();	// プレイヤー情報の初期化

	return rtnFlag;
}

void PlayerControl(void)
{
	bool moveFlag = false;	// true:移動

	// プレイヤーの向き設定
	if (keyNew[KEY_ID_UP])
	{
		player.moveDir = DIR_UP;
		moveFlag = true;
	}
	if (keyNew[KEY_ID_RIGHT])
	{
		player.moveDir = DIR_RIGHT;
		moveFlag = true;

	}
	if (keyNew[KEY_ID_DOWN])
	{
		player.moveDir = DIR_DOWN;
		moveFlag = true;
	}
	if (keyNew[KEY_ID_LEFT])
	{
		player.moveDir = DIR_LEFT;
		moveFlag = true;
	}
}

void PlayerGameDraw(void)
{
	PlayerControl();
	player.animCnt++;

	DrawGraph(player.pos.x, player.pos.y, playerImage[player.moveDir][(player.animCnt / 10) % 3], true);

	DrawFormatString(300, 0, 0xffffff, "anmCnt = %d", player.animCnt);
}
