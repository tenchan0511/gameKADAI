#include "DxLib.h"
#include "main.h"
#include "stage.h"
#include "effect.h"

int chipImage[768];
int mapPosX;
int mapPosY;
int map[MAP_Y][MAP_X];
int stage1[MAP_Y][MAP_X] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,}
};
XY mapSize;			// マップの縦横サイズ

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

	mapSize.x = MAP_X;
	mapSize.y = MAP_Y;

	return true;
}

void StageInit(void)
{
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			map[y][x] = stage1[y][x];
		}
	}
}

void StageDrawInit(void)
{
	for (int y = 0; y < mapSize.y; y++)
	{
		for (int x = 0; x < mapSize.x; x++)
		{
			DrawGraph(x * CHIP_SIZE_X, 32 + y * CHIP_SIZE_Y, chipImage[map[y][x]], true);
		}
	}
}

