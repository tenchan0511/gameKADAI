#pragma once

// 定義
#define CHIP_SIZE_X 32 // マップチップ分割後の横サイズ	
#define CHIP_SIZE_Y 32 // マップチップ分割後の縦サイズ	
#define CHIP_X 8	   // 横の画像分割数
#define CHIP_Y 96	   // 縦の画像分割数
#define MAP_X 25	   // ステージの横サイズ（チップ数）
#define MAP_Y 20	   // ステージの縦サイズ（チップ数）

// ステージ
enum STAGE_ID {
	STAGE_ID_1,
	STAGE_ID_2,
	STAGE_ID_MAX,
};

// プロトタイプ宣言
bool StageSystemInit(void);
void StageInit(void);
void StageDrawInit(void);

XY PosToIndex(XY pos);	// マップ上のプレイヤーの座標を求める関数

bool IsPass(XY pos);	// 通ってよいか判断する

void SetMapData(STAGE_ID stage_ID);
