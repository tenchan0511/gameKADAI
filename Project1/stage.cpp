#include "DxLib.h"
#include "main.h"
#include "stage.h"
#include "effect.h"

int chipImage[768];
int chipImage2[728];
int chipImage3[400];
int mapPosX;
int mapPosY;
int map[MAP_Y][MAP_X];
int stage1map[MAP_Y][MAP_X] = {
	{64,65,66,67,68,69,44,45,64,65,66,67,68,69,44,45,64,65,66,67,68,69,9,9,9,},
	{72,73,74,75,76,77,52,53,72,73,74,75,76,77,52,53,72,73,74,75,76,77,9,9,9,},
	{80,81,82,83,84,85,60,61,80,81,82,83,84,85,60,61,80,81,82,83,84,85,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
	{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,},
};
XY mapSize;			// マップの縦横サイズ
STAGE_ID stageID;

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
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			map[y][x] = stage1map[y][x];
		}
	}
}

void StageDrawInit(void)
{
	/*for (int y = 0; y < MAP_Y; y++)
	{
		for (int x = 0; x < MAP_X; x++)
		{
			DrawGraph(x * CHIP_SIZE_X, 32 + y * CHIP_SIZE_Y, chipImage[1], true);
		}
	}

	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			DrawGraph(x * CHIP_SIZE_X, 32 + y * CHIP_SIZE_Y, chipImage2[map[y][x]], true);
		}
	}*/

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

}
