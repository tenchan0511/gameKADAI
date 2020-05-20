//#pragma once
#ifdef _DEBUG
#define AST() {\
    CHAR ast_mes[256];\
    wsprintf(ast_mes, "%s %d行目\0", __FILE__, __LINE__);\
    MessageBox(0, ast_mes, "ｱｻｰﾄ表示",MB_OK);\
    }
#else
#define AST()
#endif
// 定義
#define SCREEN_SIZE_X 800	// 画面の横サイズ
#define SCREEN_SIZE_Y 672	// 画面の縦サイズ

// シーン管理用
enum SCN_ID 
{
	SCN_ID_INIT,		// 初期化シーン
	SCN_ID_TITLE,		// タイトルシーン
	SCN_ID_GAME,		// ゲームシーン
	SCN_ID_GAMEOVER,	// ゲームオーバーシーン
	SCN_ID_MAX
};

enum DIR
{
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
	DIR_UP,
	DIR_MAX
};

// 表示ソート用
enum CHARACTER_TYPE
{
	CHARACTER_PLAYER,
	CHARACTER_ENEMY,
	CHARACTER_MAX
};

struct XY
{
	int x;
	int y;
};

struct CHARACTER
{
	int charType;		// キャラの種類
	DIR moveDir;		// キャラの向き
	XY pos;				// キャラの座標
	XY offsetSize;		// キャラの初期位置
	XY size;			// キャラのサイズ
	int moveSpeed;		// キャラのスピード
	int life;			// 残機数
	int animCnt;		// キャラのアニメーションカウンタ
};

// プロトタイプ宣言

// システム系初期化
bool SystemInit(void);

// 初期化シーン
void InitScene(void);

// タイトルシーン
void TitleScene(void);
void TitleDraw(void);

// ゲームシーン
void GameMain(void);
void GameDraw(void);

// ゲームオーバーシーン
void GameOverScene(void);
void GameOverDraw(void);

// Y座標リスト
void AddCharOrder(CHARACTER_TYPE characterType, int index, int y);
