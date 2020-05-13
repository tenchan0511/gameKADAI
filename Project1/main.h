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
#define SCREEN_SIZE_Y 600	// ��ʂ̏c�T�C�Y

// �V�[���Ǘ��p
enum SCN_ID 
{
	SCN_ID_INIT,		// �������V�[��
	SCN_ID_TITLE,		// �^�C�g���V�[��
	SCN_ID_GAME,		// �Q�[���V�[��
	SCN_ID_GAMEOVER,	// �Q�[���I�[�o�[�V�[��
	SCN_ID_MAX
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


