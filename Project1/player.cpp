#include "DxLib.h"
#include "main.h"
#include "keycheck.h"
#include "player.h"
#include "stage.h"
#include "effect.h"

CHARACTER player;
int playerImage[4][3];

void PlayerSystemInit(void)
{
	LoadDivGraph(
		"image/school01.png",
		12,
		PLAYER_H,
		PLAYER_V,
		PLAYER_SIZE_X,
		PLAYER_SIZE_Y,
		&playerImage[0][0]
	);

	player.moveDir = DIR_DOWN;				// �L�����̌���
	player.pos.x = 0;						// �v���C���[�̏����ʒu
	player.pos.y = 64;						// �v���C���[�̏����ʒu
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

XY PlayerControl(void)
{
	bool moveFlag = false;			// true:�ړ�
	XY playerIndex;					// �}�b�v�z��̍��W
	XY playerPosCopy = player.pos;	// �v���C���[�̍��W���R�s�[
	XY playerPosOffset = playerPosCopy;

	// �v���C���[�̌����ݒ�
	if (keyNew[KEY_ID_UP])
	{
		player.moveDir = DIR_UP;
		moveFlag = true;
	}
	if (keyNew[KEY_ID_RIGHT])
	{
		player.moveDir = DIR_RIGHT;
		moveFlag = true;

	}
	if (keyNew[KEY_ID_DOWN])
	{
		player.moveDir = DIR_DOWN;
		moveFlag = true;
	}
	if (keyNew[KEY_ID_LEFT])
	{
		player.moveDir = DIR_LEFT;
		moveFlag = true;
	}

	// �v���C���[�̈ړ�����
	if (moveFlag)
	{
		switch (player.moveDir)
		{
		case DIR_DOWN:
			if (playerPosCopy.y < MAP_Y * CHIP_SIZE_Y - 24)
			{
				playerPosCopy.y += player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x + player.offsetSize.x;
				playerPosOffset.y = playerPosCopy.y + player.offsetSize.y;
				if (IsPass(playerPosOffset))
				{
					// �ʂ��
					player.pos = playerPosCopy;
				}
			}
			break;
		case DIR_LEFT:
			if (playerPosCopy.x > 0)
			{
				playerPosCopy.x -= player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x;
				playerPosOffset.y = playerPosCopy.y + player.offsetSize.y;
				if (IsPass(playerPosOffset))
				{
					// �ʂ��
					player.pos = playerPosCopy;
				}
			}
			break;
		case DIR_RIGHT:
			if (playerPosCopy.x < MAP_X * CHIP_SIZE_X - 32)
			{
				playerPosCopy.x += player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x + player.size.x;
				playerPosOffset.y = playerPosCopy.y + player.offsetSize.y;
				if (IsPass(playerPosOffset))
				{
					// �ʂ��
					player.pos = playerPosCopy;
				}
			}
			break;
		case DIR_UP:
			if (playerPosCopy.y > 0)
			{
				playerPosCopy.y -= player.moveSpeed;
				playerPosOffset.x = playerPosCopy.x + player.offsetSize.x;
				playerPosOffset.y = playerPosCopy.y;
				if (IsPass(playerPosOffset))
				{
					// �ʂ��
					player.pos = playerPosCopy;
				}
			}
			break;
		}
	}
	return player.pos;
}

void PlayerGameDraw(void)
{
	player.animCnt++;

	DrawGraph(player.pos.x, player.pos.y, playerImage[player.moveDir][(player.animCnt / 10) % 3], true);

	DrawFormatString(300, 0, 0xffffff, "anmCnt = %d", player.animCnt);
}
