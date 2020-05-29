#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "effect.h"
#include "stage.h"
#include "player.h"
#include "enemy.h"

// 定数
#define DRAW_ORDER_MAX			ENEMY_MAX + 1

struct DRAW_ORDER
{
	CHARACTER_TYPE characterType;	// キャラの種類
	int index;					// 各キャラの添え字
	int y;						// キャラの足元Y座標
};

// 変数
//int sceneCounter;
SCN_ID scnID;		// シーン管理用
SCN_ID scnIDpre;
int playerLife;
int playerLifeImage;
bool mutekiFlag;	// 無敵状態フラグ
int mutekiCnt;		// 無敵カウント
int stopCnt;

// 表示ソート用
int drawOrderCnt;							// Listに格納されたデータ数
DRAW_ORDER drawOrderList[DRAW_ORDER_MAX];	// ソート用配列

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
			//sceneCounter = 0;
		}
		scnIDpre = scnID;

		switch (scnID)
		{
		case SCN_ID_INIT:
			InitScene();
			scnID = SCN_ID_TITLE;
			break;
		case SCN_ID_TITLE:
			if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{// フェードアウトが終わった後の処理を書く
					fadeIn = true;
					scnID = SCN_ID_GAME;
				}
			}
			if (fadeIn)
			{				
				if (!FadeInScreen(5)){} // フェードインが終わった後の処理を書く
			}
			TitleScene();
			break;
		case SCN_ID_GAME:
			if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{// フェードアウトが終わった後の処理を書く
					fadeIn = true;
					scnID = SCN_ID_GAMEOVER;
				}
			}
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {} // フェードインが終わった後の処理を書く
			}
			GameMain();
			break;
		case SCN_ID_GAMEOVER:
			if (fadeOut)
			{
				if (!FadeOutScreen(5))
				{// フェードアウトが終わった後の処理を書く
					fadeIn = true;
					scnID = SCN_ID_INIT;
				}
			}
			if (fadeIn)
			{
				if (!FadeInScreen(5)) {} // フェードインが終わった後の処理を書く
			}
			GameOverScene();
			break;
		default:
			AST();
			break;
		}
		//sceneCounter++;

		ScreenFlip();	 // 裏画面を表画面に瞬間コピー
	}
	DxLib_End();		// DXライブラリの終了処理
	return 0;			// このプログラムの終了
}

// システム初期化
bool SystemInit(void)
{
	bool rtnFlag = true;
	// システム処理
	SetWindowText("Project1");

	SetGraphMode(SCREEN_SIZE_X, SCREEN_SIZE_Y, 16); // 640×480ドット65536色モードに設定
	ChangeWindowMode(true);							// true:window false:フルスクリーン
	if (DxLib_Init() == -1) return true;			// DXライブラリ初期化処理
	SetDrawScreen(DX_SCREEN_BACK);					// ひとまずバックバッファに描画

	keyInit();			// キー情報の初期化
	StageSystemInit();	// ステージの初期化
	PlayerSystemInit();	// プレイヤーの情報初期化
	EnemySystemInit();	// 敵の初期化

	// グラフィックの登録
	playerLifeImage = LoadGraph("image/Life.png");

	// 変数初期化
	scnID = SCN_ID_INIT;
	playerLife = 3;
	mutekiFlag = false;
	mutekiCnt = 0;
	stopCnt = 0;

	// 配列の初期化
	drawOrderCnt = 0;
	for (int i = 0; i < DRAW_ORDER_MAX; i++)
	{
		// 配列の初期化
		drawOrderList[i].characterType = CHARACTER_MAX;
		drawOrderList[i].index = 0;
		drawOrderList[i].y = 0;
	}

	EffectInit();			// エフェクト用初期化処理
	
	return true;
}

// 初期化シーン
void InitScene(void)
{
	StageInit();
	PlayerGameInit();
	playerLife = 3;
	EnemyGameInit();
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
	DrawBox(100, 100, 700, 500, GetColor(0, 255, 0), true);
}

// ゲームシーン
void GameMain(void)
{
	XY playerPos;

	if (playerLife == 0)
	{
		mutekiFlag = false;
		fadeOut = true;
	}

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

	if (stopFlag)
	{
		stopCnt++;
		if (stopCnt < 180)
		{
			stopFlag = true;
		}
		else
		{
			stopFlag = false;
			stopCnt = 0;
			StageInit();
			PlayerGameInit();
			EnemyGameInit();
		}
	}

	if (!pauseFlag && !stopFlag)
	{
		// 配列の初期化
		drawOrderCnt = 0;
		for (int i = 0; i < DRAW_ORDER_MAX; i++)
		{
			// 配列の初期化
			drawOrderList[i].characterType = CHARACTER_MAX;
			drawOrderList[i].index = 0;
			drawOrderList[i].y = 0;
		}

		playerPos = PlayerControl();
		EnemyControl(playerPos);

		// プレイヤーとと敵との当たり判定
		if (PlayerHitCheck(playerPos, 12))
		{
			if (!mutekiFlag)
			{
				// 当たり
				playerLife--;
				stopFlag = true;
				mutekiFlag = true;
			}
		}

		// 無敵時間
		if (mutekiFlag)
		{
			mutekiCnt++;
			if (mutekiCnt / 360 % 2 == 0)
			{
				mutekiFlag = true;
				//if (mutekiCnt <= 60)
				//{
				//	randX = 0;
				//	randX = -3 + GetRand(6);//-3から6までの乱数
				//}
			}
			else
			{
				mutekiFlag = false;
				mutekiCnt = 0;
			}
		}
	}
	GameDraw();
}

void GameDraw(void)
{
	StageDrawInit();

	for (int i = 0; i < drawOrderCnt; i++)
	{
		switch (drawOrderList[i].characterType)
		{
		case CHARACTER_ENEMY:		// 敵の描画
			EnemyDrawInit(drawOrderList[i].index);
			break;
		case CHARACTER_PLAYER:
			PlayerGameDraw();		// プレイヤーの描画
			break;
		default:
			break;
		}
	}
	for (int i = 0; i < playerLife; i++)
	{
		DrawGraph(i * 24, 0, playerLifeImage, true);
	}

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
	
	DrawBox(100, 100, 700, 500, GetColor(0, 0, 255), true);
}

void AddCharOrder(CHARACTER_TYPE characterType, int index, int y)
{
	int insertIndex = drawOrderCnt;// 挿入場所の配列の添え字

	// 1.リスト内のデータと引数のY座標を比較して挿入場所を決める
	for (int dol = 0; dol < drawOrderCnt; dol++)	// すべてのリストデータを
	{
		if (y < drawOrderList[dol].y)	//リストのデータと引数のYを比較
		{
			insertIndex = dol;// 挿入場所の配列の添え字
			break;
		}
	}

	// 2.挿入場所が決まったので、挿入場所を空けるためにほかのデータを移動させる
	for (int dol = drawOrderCnt; dol > insertIndex; dol--)
	{
		// データをコピー
		drawOrderList[dol] = drawOrderList[dol - 1];
	}

	// 3.挿入場所にデータを追加(配列に追加)
	drawOrderList[insertIndex].characterType = characterType;
	drawOrderList[insertIndex].index = index;
	drawOrderList[insertIndex].y = y;
	drawOrderCnt++;
}
