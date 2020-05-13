#include "DxLib.h"
#include "effect.h"

int fadeIn;			// フェードイン
int fadeOut;		// フェードアウト
int bright;

// 一時停止処理
bool pauseFlag;		// 一時停止処理(true:	)
int testcnt;

// エフェクト用初期化処理
void EffectInit(void)
{
	// 一時停止処理用
	pauseFlag = false;

	// フェード処理用
	fadeIn = true;
	fadeOut = false;
	bright = 0;
}

// シーン遷移関数
// フェードイン
bool FadeInScreen(int fadeStep)
{
	if (bright <= 255)
	{
		SetDrawBright(bright, bright, bright);
		bright += fadeStep;
		return true;	// 戻り値
	}
	else
	{
		SetDrawBright(255, 255, 255);
		fadeIn = false;
		bright = 0;
		return false;	// 戻り値
	}
}
// フェードアウト
bool FadeOutScreen(int fadeStep)
{
	if (bright <= 255)
	{
		SetDrawBright(255 - bright, 255 - bright, 255 - bright);
		bright += fadeStep;
		return true;	// 戻り値
	}
	else
	{
		SetDrawBright(0, 0, 0);
		fadeOut = false;
		bright = 0;
		return false;	// 戻り値
	}
}
