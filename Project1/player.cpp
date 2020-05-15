#include "DxLib.h"
#include "main.h"
#include "player.h"
#include "effect.h"

CHARACTER player;
int playerImage[4][3];

void PlayerSystemInit(void)
{
	LoadDivGraph(
		"image/school01.png",
		12,
		PLAYER_V,
		PLAYER_H,
		PLAYER_SIZE_X,
		PLAYER_SIZE_Y,
		&playerImage[0][0]
	);

	player.moveDir = DIR_DOWN;				// �L�����̌���
	player.pos.x = 0;						// �v���C���[�̏����ʒu
	player.pos.y = 0;						// �v���C���[�̏����ʒu
	player.size.x = PLAYER_SIZE_X;			// �v���C���[�̉��T�C�Y
	player.size.y = PLAYER_SIZE_Y;			// �v���C���[�̏c�T�C�Y
	player.offsetSize.x = player.size.x / 2;// �v���C���[�̍��W
	player.offsetSize.y = player.size.y / 2;// �v���C���[�̍��W
	player.moveSpeed = PLAYER_SPEED;		// �v���C���[�̃X�s�[�h
	player.life = 3;						// �v���C���[�̎c�@
	player.animCnt = 0;						// �L�����̃A�j���[�V�����J�E���^

}

bool PlayerGameInit(void)
{
	bool rtnFlag = true;

	PlayerSystemInit();	// �v���C���[���̏�����

	return rtnFlag;
}

void PlayerGameDraw(void)
{

}
