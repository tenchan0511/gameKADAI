#include "DxLib.h"
#include "main.h"
#include "stage.h"
#include "effect.h"

// 変数
int chipImage[768];		// マップチップ読み込み用1
int chipImage2[728];	// マップチップ読み込み用2
int chipImage3[400];	// マップチップ読み込み用3
int mapPosX;			// 
int mapPosY;			// 
int map[MAP_Y][MAP_X];	// 
int stage1map[MAP_Y][MAP_X] = {
	{74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,74,703,718,719,},
	{80,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,81,725,726,727,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,303,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,24,25,26,27,28,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,32,33,34,35,36,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,40,41,42,43,44,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,48,49,50,51,52,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{534,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{542,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{550,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{76,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,77,78,9,},
	{84,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,85,86,17,},
};
int stage2map[MAP_Y][MAP_X] = {
	{64,65,66,67,68,69,44,45,64,65,66,67,68,69,44,45,64,65,66,67,68,69,40,41,42,},
	{72,73,74,75,76,77,52,53,72,73,74,75,76,77,52,53,72,73,74,75,76,77,48,49,50,},
	{80,81,82,83,84,85,60,61,80,81,82,83,84,85,60,61,80,81,82,83,84,85,56,57,58,},
	{136,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{144,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,0,0,0,},
	{144,284,259,284,259,284,259,284,259,284,259,284,259,284,259,284,259,284,259,284,259,0,0,0,191,},
	{144,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,199,},
	{144,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,0,0,207,},
	{144,284,259,284,259,284,259,284,259,284,259,284,259,284,259,284,259,284,259,284,259,0,0,0,207,},
	{144,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,207,},
	{144,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,0,0,207,},
	{144,284,259,284,259,284,259,284,259,284,259,284,259,284,259,284,259,284,259,284,259,0,0,0,207,},
	{144,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,207,},
	{144,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,251,0,0,0,215,},
	{144,284,259,284,259,284,259,284,259,284,259,284,259,284,259,284,259,284,259,284,259,0,0,0,223,},
	{144,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},
	{64,65,66,67,68,69,44,45,64,65,66,67,68,69,44,45,64,65,66,67,68,69,40,70,71,},
	{72,73,74,75,76,77,52,53,72,73,74,75,76,77,52,53,72,73,74,75,76,77,48,78,79,},
	{80,81,82,83,84,85,60,61,80,81,82,83,84,85,60,61,80,81,82,83,84,85,56,86,87,},
	{4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,},
};
XY mapSize;			// マップの縦横サイズ
STAGE_ID stageID;	// ステージ番号

bool StageSystemInit(void)
{

	LoadDivGraph(
		"image/senroheikou.png",
		CHIP_X * CHIP_Y,
		CHIP_X,
		CHIP_Y,
		CHIP_SIZE_X,
		CHIP_SIZE_Y,
		chipImage
	);

	LoadDivGraph(
		"image/shops00.png",
		CHIP_X * 91,
		CHIP_X,
		91,
		CHIP_SIZE_X,
		CHIP_SIZE_Y,
		chipImage2
	);

	LoadDivGraph(
		"image/image.png",
		CHIP_X * 50,
		CHIP_X,
		50,
		CHIP_SIZE_X,
		CHIP_SIZE_Y,
		chipImage3
	);

	SetMapData(STAGE_ID_1);
	
	return true;
}

void StageInit(void)
{
	
}

void StageDrawInit(void)
{
	if (stageID == STAGE_ID_1)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				DrawGraph(x * CHIP_SIZE_X, 32 + y * CHIP_SIZE_Y, chipImage2[9], true);
			}
		}

		for (int y = 0; y < mapSize.y; y++)
		{
			for (int x = 0; x < mapSize.x; x++)
			{
				DrawGraph(x * CHIP_SIZE_X, 32 + y * CHIP_SIZE_Y, chipImage2[map[y][x]], true);
			}
		}
	}

	if (stageID == STAGE_ID_2)
	{
		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				DrawGraph(x * CHIP_SIZE_X, 32 + y * CHIP_SIZE_Y, chipImage3[0], true);
			}
		}

		for (int y = 0; y < mapSize.y; y++)
		{
			for (int x = 0; x < mapSize.x; x++)
			{
				DrawGraph(x * CHIP_SIZE_X, 32 + y * CHIP_SIZE_Y, chipImage3[map[y][x]], true);
			}
		}
	}
}

XY PosToIndex(XY pos)
{
	XY index;

	//posをIndexに変換する
	index.x = pos.x / CHIP_SIZE_X;
	index.y = pos.y / CHIP_SIZE_Y;

	// 戻り値
	return index;
}

// プレイヤーが通ってよいか判断する関数
bool IsPass(XY pos)
{
	XY index;
	index = PosToIndex(pos);

	//if (map[index.y][index.x] == 34
	//	|| map[index.y][index.x] == 42
	//	|| map[index.y][index.x] == 80
	//	|| map[index.y][index.x] == 81
	//	|| map[index.y][index.x] == 83
	//	|| map[index.y][index.x] == 76
	//	|| map[index.y][index.x] == 77
	//	|| map[index.y][index.x] == 78)
	//	{
	//		 //通れない
	//		return false;
	//	}
	//	else
	//	{
	//		 //通れる
	//		return true;
	//	}

	switch (map[index.y][index.x])
	{
		if (stageID == STAGE_ID_1)
		{
	case 34:
	case 42:
	case 80:
	case 81:
	case 83:
	case 76:
	case 77:
	case 78:
	case 86:
	case 303:
	case 542:
	case 725:
	case 726:
	case 727:
		return false;
		break;
		}
		if (stageID == STAGE_ID_2)
		{
		return false;
		break;
		}
	default:
		break;
	}
	{
		// 通れる
		return true;
	}
}

void SetMapData(STAGE_ID stageID)
{
	for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			map[y][x] = 0;
		}
	}

	if (stageID == STAGE_ID_1)
	{
		mapSize.x = MAP_X;
		mapSize.y = MAP_Y;

		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				map[y][x] = stage1map[y][x];
			}
		}
		stageID = STAGE_ID_1;
	}

	if (stageID == STAGE_ID_2)
	{
		mapSize.x = MAP_X;
		mapSize.y = MAP_Y;

		for (int y = 0; y < MAP_Y; y++)
		{
			for (int x = 0; x < MAP_X; x++)
			{
				map[y][x] = stage2map[y][x];
			}
		}
		stageID = STAGE_ID_2;
	}
}

// 指定された座標にイベント
EVENT_ID GetEvent(XY pos)
{
	XY index;
	index = PosToIndex(pos);
	switch (map[index.y][index.x])
	{
	case 15:
		return EVENT_ID_KAIDAN;
		break;
	case 24:
	case 25:
	case 26:
	case 33:
	case 34:
	case 35:
	case 42:
	case 41:
	case 40:
		return EVENT_ID_SPEEDDOWN;
	case 13:
		return EVENT_ID_IDO;
	case 7:
		return EVENT_ID_RETURN;
	default:
		return EVENT_ID_NON;
		break;
	}
}
