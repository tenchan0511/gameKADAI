//#pragma once
									// フェード処理用
extern int fadeIn;
extern int fadeOut;
//extern int bright;

// 一時停止処理
extern bool pauseFlag;		// 一時停止処理(true:	)
extern int testcnt;

void EffectInit(void);				// エフェクト用初期化

// シーン遷移関数
bool FadeInScreen(int fadeStep);	// フェードイン(戻り値：true フェードイン中、false フェードイン終了)
bool FadeOutScreen(int fadeStep);	// フェードアウト(戻り値：true フェードアウト中、falseフェードアウト終了)
