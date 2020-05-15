#pragma once

// 定義
#define PLAYER_V 8			// プレイヤー縦分割数
#define PLAYER_H 12			// プレイヤー横分割数
#define PLAYER_SIZE_Y 48	// プレイヤー縦サイズ
#define PLAYER_SIZE_X 32	// プレイヤー横サイズ
#define PLAYER_SPEED 1		// プレイヤースピード

// プロトタイプ宣言
void PlayerSystemInit(void);	// システム
bool PlayerGameInit(void);		// シーン
void PlayerGameDraw(void);		// 描画
void PlayerControl(void);			// プレイヤーの移動
