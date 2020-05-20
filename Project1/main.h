//#pragma once
#ifdef _DEBUG
#define AST() {\
    CHAR ast_mes[256];\
    wsprintf(ast_mes, "%s %d�s��\0", __FILE__, __LINE__);\
    MessageBox(0, ast_mes, "���ĕ\��",MB_OK);\
    }
#else
#define AST()
#endif
// ��`
#define SCREEN_SIZE_X 800	// ��ʂ̉��T�C�Y
#define SCREEN_SIZE_Y 672	// ��ʂ̏c�T�C�Y

// �V�[���Ǘ��p
enum SCN_ID 
{
	SCN_ID_INIT,		// �������V�[��
	SCN_ID_TITLE,		// �^�C�g���V�[��
	SCN_ID_GAME,		// �Q�[���V�[��
	SCN_ID_GAMEOVER,	// �Q�[���I�[�o�[�V�[��
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

// �\���\�[�g�p
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
	int charType;		// �L�����̎��
	DIR moveDir;		// �L�����̌���
	XY pos;				// �L�����̍��W
	XY offsetSize;		// �L�����̏����ʒu
	XY size;			// �L�����̃T�C�Y
	int moveSpeed;		// �L�����̃X�s�[�h
	int life;			// �c�@��
	int animCnt;		// �L�����̃A�j���[�V�����J�E���^
};

// �v���g�^�C�v�錾

// �V�X�e���n������
bool SystemInit(void);

// �������V�[��
void InitScene(void);

// �^�C�g���V�[��
void TitleScene(void);
void TitleDraw(void);

// �Q�[���V�[��
void GameMain(void);
void GameDraw(void);

// �Q�[���I�[�o�[�V�[��
void GameOverScene(void);
void GameOverDraw(void);

// Y���W���X�g
void AddCharOrder(CHARACTER_TYPE characterType, int index, int y);
