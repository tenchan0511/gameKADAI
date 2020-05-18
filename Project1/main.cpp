#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"

// 変数
int sceneCounter;
SCN_ID scnID;		// シーン管理用
SCN_ID scnIDpre;

// Winmain関数
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	if (!SystemInit())
	{
		return 0;
	}
	// ゲームループ
	while (ProcessMessage() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0)
	{
		keyCheck();

		ClsDrawScreen(); // 画面消去

		if (scnID != scnIDpre)
		{
			sceneCounter = 0;
		}
		scnIDpre = scnID;

		switch (scnID)
		{
		case SCN_ID_INIT:
			InitScene();
			scnID = SCN_ID_TITLE;
			break;
		case SCN_ID_TITLE:
			if (fadeIn)
			{				
				if (!FadeInScreen(5)){} // フェードインが終わった後の処理を書く
			}
			if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{// フェードアウトが終わった後の処理を書く
					fadeIn = true;
					scnID = SCN_ID_GAME;
				}
			}
			TitleScene();
			break;
		case SCN_ID_GAME:
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {} // フェードインが終わった後の処理を書く
			}
			if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{// フェードアウトが終わった後の処理を書く
					fadeIn = true;
					scnID = SCN_ID_GAMEOVER;
				}
			}
			GameMain();
			break;
		case SCN_ID_GAMEOVER:
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {} // フェードインが終わった後の処理を書く
			}
			if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{// フェードアウトが終わった後の処理を書く
					fadeIn = true;
					scnID = SCN_ID_INIT;
				}
			}
			GameOverScene();
			break;
		default:
			AST();
			break;
		}

		// メイン処理

		sceneCounter++;

		ScreenFlip();	 // 裏画面を表画面に瞬間コピー
	}
	DxLib_End();		// DXライブラリの終了処理
	return 0;			// このプログラムの終了

}

// システム初期化
bool SystemInit(void)
{
	// システム処理
	SetWindowText("BaseProject");

	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16); // 640×480ドット65536色モードに設定
	ChangeWindowMode(true);							// true:window false:フルスクリーン
	if (DxLib_Init() == -1) return true;			// DXライブラリ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);					// ひとまずバックバッファに描画

	keyInit();			// キー情報の初期化
	StageSystemInit();	// ステージの初期化
	PlayerSystemInit();	// プレイヤーの情報初期化

	// グラフィックの登録


	// 変数初期化
	sceneCounter = 0;
	scnID = SCN_ID_INIT;

	EffectInit();			// エフェクト用初期化処理
	
	return true;
}

// 初期化シーン
void InitScene(void)
{
	StageInit();
	PlayerGameInit();
}

// タイトルシーン
void TitleScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		/*scnID = SCN_ID_GAME;*/
		fadeOut = true;
	}
	TitleDraw();
}
void TitleDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "TitleCounter = %d", sceneCounter);

	DrawBox(100, 100, 700, 500, GetColor(0, 255, 0), true);
}

// ゲームシーン
void GameMain(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		/*scnID = SCN_ID_GAMEOVER;*/
		fadeOut = true;
	}
	
	if (keyDownTrigger[KEY_ID_PAUSE])
	{
		if (pauseFlag)
		{
			pauseFlag = false;
			SetDrawBright(255, 255, 255);
		}
		else
		{
			pauseFlag = true;
			SetDrawBright(127, 127, 127);
		}
	}
	if (!pauseFlag)
	{
		testcnt++;

		PlayerControl();
	}
	GameDraw();
}

void GameDraw(void)
{
	StageDrawInit();
	PlayerGameDraw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "GameCounter = %d", sceneCounter);
	DrawFormatString(50, 50, GetColor(255, 255, 255), "test = %d", testcnt);

	/*DrawBox(100, 100, 700, 500, GetColor(255, 0, 0), true);*/

	// PAUSE描画
	if (pauseFlag)
	{
		DrawFormatString(375, 285, GetColor(255, 255, 255), "PAUSE");
	}
}

// ゲームオーバーシーン
void GameOverScene(void)
{
	if (keyDownTrigger[KEY_ID_SPACE])
	{
		/*scnID = SCN_ID_TITLE;*/
		fadeOut = true;
	}

	GameOverDraw();
}
void GameOverDraw(void)
{
	DrawFormatString(0, 0, GetColor(255, 255, 255), "GameOverCounter = %d", sceneCounter);

	DrawBox(100, 100, 700, 500, GetColor(0, 0, 255), true);
}

