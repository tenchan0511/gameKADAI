//#pragma once

// キー制御用
enum KEY_ID
{
	KEY_ID_SPACE,
	KEY_ID_PAUSE,
	KEY_ID_UP,
	KEY_ID_RIGHT,
	KEY_ID_DOWN,
	KEY_ID_LEFT,
	KEY_ID_MAX,
};

// プロトタイプ宣言
// キー
void keyInit(void);		// キー制御配列の初期化
void keyCheck(void);	// キー情報取得

// 変数
// キー制御用
extern bool keyOld[KEY_ID_MAX];			// 1フレーム前のキー状態
extern bool keyNew[KEY_ID_MAX];			// 現在のキー状態
extern bool keyDownTrigger[KEY_ID_MAX];	// キー押下時のトリガー
extern bool keyUpTrigger[KEY_ID_MAX];	// キーアップ時のトリガー
