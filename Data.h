//��Data�n�̃w�b�_�t�@�C��
#pragma once

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########

//�Q�[���̃��C���w�b�_�t�@�C��
#include	"game.h"

//########## �}�N����` ##########

//�G���[���b�Z�[�W
#define CSV_LOAD_ERR_TITLE		TEXT("CSV�ǂݍ��݃G���[")
#define CSV_DATANUM_ERR_TITLE	TEXT("CSV�f�[�^���G���[")

//�L�����f�[�^�̃p�X
#define CSV_PATH_ENEMY		TEXT(".\\Data\\enemy.csv")	//ANSI�̕����R�[�h�Ńt�@�C���ۑ�

//�f�[�^�̏����w��q
//�L�����N�^�̏����w��q�i%[^,]�͕�����j
#define CSV_CHARA_FORMAT	TEXT("%d,%[^,],%d,%d,%d,%d,%d,%d")

//�G�f�[�^
#define ENEMY_MAX	5

//�G���[���b�Z�[�W
#define SCORE_CREATE_ERR_TITLE	TEXT("�X�R�A�f�[�^�쐬�G���[")
#define SCORE_LOAD_ERR_TITLE	TEXT("�X�R�A�f�[�^�Ǎ��G���[")
#define SCORE_CREATE_TITLE		TEXT("�X�R�A�f�[�^�쐬OK!!")
#define SCORE_SAVE_TITLE		TEXT("�X�R�A�f�[�^�ۑ�OK!!")
#define SCORE_DELETE_TITLE		TEXT("�X�R�A�f�[�^�폜OK!!")
#define SCORE_DELETE_ERR_TITLE	TEXT("�X�R�A�f�[�^�폜�G���[")

//�X�R�A�f�[�^�̃p�X�i�����Ċg���q���w���Ȃ̂ɂ��邱�ƂŁA�X�R�A�f�[�^�Ǝv���ɂ����I�H�j
#define SCORE_DATA_PATH		TEXT(".\\Data\\score.a")	//ANSI�̕����R�[�h�Ńt�@�C���ۑ�

//�f�[�^�̏����w��q
#define SCORE_DATA_FORMAT	TEXT("%[^,],%d,%[^,],%d,%[^,],%d")	//�X�R�A�f�[�^�̏����w��q�i%[^,]�͕�����j

//�}�b�v�`�b�v�̉摜�̃t�@�C���p�X
#define IMG_PATH_MAP1				TEXT(".\\Map\\mapchip.png")

//�}�b�v�f�[�^�̃t�@�C���p�X
#define CSV_PATH_MAP1_SHITA			TEXT(".\\Map\\map_shita.csv")		//�����C���[
#define CSV_PATH_MAP1_NAKA			TEXT(".\\Map\\map_naka.csv")		//�����C���[
#define CSV_PATH_MAP1_NAKA_ATARI	TEXT(".\\Map\\map_naka_atari.csv")	//���i�����蔻��j���C���[
#define CSV_PATH_MAP1_UE			TEXT(".\\Map\\map_ue.csv")			//�ヌ�C���[

//�}�b�v�̏����w��q
#define CSV_MAP_FORMAT		TEXT("%d,")

#define MAP1_YOKO_MAX	20		//�}�b�v�̉��T�C�Y
#define MAP1_TATE_MAX	20		//�}�b�v�̏c�T�C�Y

#define MAP1_YOKO_DIV	60		//�}�b�v�̉�������
#define MAP1_TATE_DIV	60		//�}�b�v�̏c������

#define MAP_MOVE_ID		56		//�ʂ��}�b�vID
#define MAP_STOP_ID		57		//�ʂ�Ȃ��}�b�vID
#define MAP_NONE_ID		58		//�����Ȃ��}�b�vID

//�L�����f�[�^�\����(�����܂ŃT���v��)
struct CHARA_DATA
{
	int No;					//No
	char Name[STR_MAX];		//���O

	//���ۂɎg���l
	int HP;					//HP
	int ATK;				//�U����
	int DEF;				//�h���

	//�ő�l
	int MAX_HP;				//HP
	int MAX_ATK;			//�U����
	int MAX_DEF;			//�h���
};

//�X�R�A�f�[�^�\����(�����܂ŃT���v��)
struct SCORE_DATA
{
	char path[PATH_MAX];	//�p�X
	char Name1[STR_MAX];	//���O�P
	int Score1;				//�X�R�A�P
	char Name2[STR_MAX];	//���O�Q
	int Score2;				//�X�R�A�Q
	char Name3[STR_MAX];	//���O�R
	int Score3;				//�X�R�A�R
};

//�}�b�v�f�[�^�\���́i�����܂ŃT���v���j
struct MAP_DATA
{
	//CSV�f�[�^�i�����摜��ID������j
	int CSV_shita[MAP1_TATE_MAX][MAP1_YOKO_MAX];
	int CSV_naka[MAP1_TATE_MAX][MAP1_YOKO_MAX];
	int CSV_naka_atari[MAP1_TATE_MAX][MAP1_YOKO_MAX];
	int CSV_ue[MAP1_TATE_MAX][MAP1_YOKO_MAX];

	//�}�b�v�̃n���h��
	int handle[MAP1_TATE_DIV * MAP1_YOKO_DIV];

	//�}�b�v�̏ꏊ
	int x[MAP1_TATE_MAX][MAP1_YOKO_MAX];
	int y[MAP1_TATE_MAX][MAP1_YOKO_MAX];

	int width;
	int height;

	int DivMax;

	BOOL IsDraw = FALSE;	//�`�悷�邩�H

	//�����蔻��
	RECT coll[MAP1_TATE_MAX][MAP1_YOKO_MAX];
};

//########## �O���̃O���[�o���ϐ� ##########
extern CHARA_DATA enemy[ENEMY_MAX];		//�G�f�[�^
extern SCORE_DATA score_data;			//�X�R�A�f�[�^
extern SCORE_DATA score_dataInit;		//�X�R�A�f�[�^(�������p)

//########## �v���g�^�C�v�錾 ##########
//��extern �́A�O���Ɋ֐�������܂���I�Ƃ����ڈ�ł��Ă��܂��B

extern BOOL LoadCSVChara(const char* path, CHARA_DATA* chara, int DataMax, BOOL IsHeader);
extern BOOL LoadScoreData(const char* path, SCORE_DATA* score, BOOL IsHeader);

extern BOOL LoadCSVMap(
	const char* ImgPath,
	const char* ShitaPath,
	const char* NamaPath,
	const char* NakaAtariPath,
	const char* UePath,
	MAP_DATA* map,
	int divYoko,
	int divTate);

extern BOOL CreateScoreData(VOID);
extern BOOL SaveScoreData(VOID);
extern BOOL DeleteScoreData(VOID);
extern const char* GetScoreDataPath(VOID);
extern VOID SetScoreDataPath(const char* path);

extern BOOL CollMap(RECT rect, MAP_DATA map);
extern VOID DrawMap(MAP_DATA map);
extern MAP_DATA map1;
