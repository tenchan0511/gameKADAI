#include "DxLib.h"
#include "keycheck.h"

// 変数
// キー制御用
bool keyOld[KEY_ID_MAX];			// 1フレーム前のキー状態
bool keyNew[KEY_ID_MAX];			// 現在のキー状態
bool keyDownTrigger[KEY_ID_MAX];	// キー押下時のトリガー
bool keyUpTrigger[KEY_ID_MAX];		// キーアップ時のトリガー

// キー制御配列の初期化
void keyInit(void)
{
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyOld[keyID] = false;
		keyNew[keyID] = false;
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;
	}
}
// キー情報取得
void keyCheck(void)
{
	// 1フレーム前のキー情報をコピー
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		keyOld[keyID] = keyNew[keyID];
	}

	// 現在のキー情報を取得する
	keyNew[KEY_ID_SPACE] = CheckHitKey(KEY_INPUT_SPACE);
	// 新しいのはここに追加
	keyNew[KEY_ID_PAUSE] = CheckHitKey(KEY_INPUT_P);
	keyNew[KEY_ID_UP] = CheckHitKey(KEY_INPUT_W);
	keyNew[KEY_ID_RIGHT] = CheckHitKey(KEY_INPUT_D);
	keyNew[KEY_ID_DOWN] = CheckHitKey(KEY_INPUT_S);
	keyNew[KEY_ID_LEFT] = CheckHitKey(KEY_INPUT_A);

	//トリガー情報の取得
	for (int keyID = 0; keyID < KEY_ID_MAX; keyID++)
	{
		// トリガー情報の初期化
		keyDownTrigger[keyID] = false;
		keyUpTrigger[keyID] = false;

		// トリガー情報の取得
		if (!keyOld[keyID] && keyNew[keyID])
		{
			keyDownTrigger[keyID] = true;
		}

		if (keyOld[keyID] && !keyNew[keyID])
		{
			keyUpTrigger[keyID] = true;
		}
	}
}
