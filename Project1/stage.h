#pragma once

// 定義
#define CHIP_SIZE_X 32 // マップチップ分割後の横サイズ	
#define CHIP_SIZE_Y 32 // マップチップ分割後の縦サイズ	
#define CHIP_X 8	   // 横の画像分割数
#define CHIP_Y 96	   // 縦の画像分割数
#define MAP_X 25	   // ステージの横サイズ（チップ数）
#define MAP_Y 20	   // ステージの縦サイズ（チップ数）

// プロトタイプ宣言
bool StageSystemInit(void);
void StageInit(void);
void StageDrawInit(void);
