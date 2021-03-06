#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "player.h"
#include "enemy.h"
#include "stage.h"
#include "effect.h"

CHARACTER player;
int playerImage[4][3];

void PlayerSystemInit(void)
{
	LoadDivGraph(
		"image/school01.png",
		12,
		PLAYER_H,
		PLAYER_V,
		PLAYER_SIZE_X,
		PLAYER_SIZE_Y,
		&playerImage[0][0]
	);

	player.moveDir = DIR_DOWN;				// キャラの向き
	player.pos.x = 0;						// プレイヤーの初期位置
	player.pos.y = 64;						// プレイヤーの初期位置
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

XY PlayerControl(void)
{
	bool moveFlag = false;			// true:移動
	//XY playerIndex;					// マップ配列の座標
	XY playerPosCopy = player.pos;	// プレイヤーの座標をコピー
	XY playerPosOffset = playerPosCopy;

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

	// プレイヤーの移動処理
	if (moveFlag)
	{
		switch (player.moveDir)
		{
		case DIR_DOWN:
			if (playerPosCopy.y < MAP_Y * CHIP_SIZE_Y - 24)
			{
				playerPosCopy.y += player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x + player.offsetSize.x;
				playerPosOffset.y = playerPosCopy.y + player.offsetSize.y;
				if (IsPass(playerPosOffset))
				{
					// 通れる
					player.pos = playerPosCopy;
				}
			}
			break;
		case DIR_LEFT:
			if (playerPosCopy.x > 0)
			{
				playerPosCopy.x -= player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x;
				playerPosOffset.y = playerPosCopy.y + player.offsetSize.y;
				if (IsPass(playerPosOffset))
				{
					// 通れる
					player.pos = playerPosCopy;
				}
			}
			break;
		case DIR_RIGHT:
			if (playerPosCopy.x < MAP_X * CHIP_SIZE_X - 32)
			{
				playerPosCopy.x += player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x + player.size.x;
				playerPosOffset.y = playerPosCopy.y + player.offsetSize.y;
				if (IsPass(playerPosOffset))
				{
					// 通れる
					player.pos = playerPosCopy;
				}
			}
			break;
		case DIR_UP:
			if (playerPosCopy.y > 0)
			{
				playerPosCopy.y -= player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x + player.offsetSize.x;
				playerPosOffset.y = playerPosCopy.y;
				if (IsPass(playerPosOffset))
				{
					// 通れる
					player.pos = playerPosCopy;
				}
			}
			break;
		}
	}
	// 表示順にデータを格納
	AddCharOrder(CHARACTER_PLAYER, 0, player.pos.y + player.size.y);// プレイヤー足元

	return player.pos;
}

void PlayerGameDraw(void)
{
	player.animCnt++;

	XY index;
	index = PosToIndex(player.pos);

	DrawGraph(
		player.pos.x, 
		player.pos.y, 
		playerImage[player.moveDir][(player.animCnt / 10) % 3], true);
}
