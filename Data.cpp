//��Data�n�̃\�[�X�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "Data.h"
#include "shape.h"		//�}�`�̏���

//########## �O���[�o���ϐ� ##########
CHARA_DATA enemy[ENEMY_MAX];	//�G�f�[�^

SCORE_DATA score_data;			//�X�R�A�f�[�^
SCORE_DATA score_dataInit = { SCORE_DATA_PATH,"NAME1",-1,"NAME2",-1, "NAME3",-1 };	//�X�R�A�f�[�^(�������p)

MAP_DATA map1;					//�}�b�v�P

//########## �֐� ##########

/// <summary>
/// CSV�t�@�C����ǂݍ��ށiCHARA_DATA�j
/// </summary>
/// <param name="path">CSV�t�@�C���̃p�X</param>
/// <param name="chara">�L�����f�[�^�\���̂̐擪�A�h���X</param>
/// <param name="DataMax">CSV�t�@�C���̍ő吔</param>
/// <param name="IsHeader">CSV�t�@�C���̂P�s�ڂ��w�b�_�Ȃ�TRUE</param>
/// <returns>TRUE�͓ǂݍ��߂�/FALSE�͎��s����</returns>
BOOL LoadCSVChara(const char* path, CHARA_DATA* chara, int DataMax, BOOL IsHeader = FALSE)
{
	FILE* fp;				//�t�@�C���|�C���^
	char GetChar = '\0';	//�擾���镶��
	int LoopCnt = 0;		//���[�v�J�E���^
	errno_t FileErr = NULL;	//�t�@�C���ǂݍ��݃G���[���m�F
	int IsEOF = NULL;		//�t�@�C���̏I��肩�`�F�b�N

	FileErr = fopen_s(&fp, path, "r");	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	if (FileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), path, CSV_LOAD_ERR_TITLE, MB_OK);	//�ǂݍ��݃G���[
		return FALSE;
	}

	//�������琳��ɓǂݍ��߂��Ƃ��̏���****************************************

	//CSV��1�s�ڂ��w�b�_�̂Ƃ�
	if (IsHeader == TRUE)
	{
		//�P���������o���A���s���q���g�ɂP�s�ڂ�ǂݔ�΂�
		while (GetChar != '\n')
		{
			GetChar = fgetc(fp);
		}
	}

	//���ۂɃf�[�^���i�[����
	while (IsEOF != EOF)	//End Of File�i�t�@�C���̍Ō�j�ł͂Ȃ��Ƃ��J��Ԃ�
	{
		//CSV�̃f�[�^�̂P�s����ǂݎ��
		IsEOF = fscanf_s(
			fp,
			CSV_CHARA_FORMAT,	//�f�[�^���u��s=���R�[�h�v�ŏ�����Ă���̂��|�C���g�I
			&(chara + LoopCnt)->No,
			&(chara + LoopCnt)->Name[0], STR_MAX,	//�������ǂݍ��ނƂ��́A���̈����ŕ�����ő吔���w�肷��
			&(chara + LoopCnt)->HP,
			&(chara + LoopCnt)->ATK,
			&(chara + LoopCnt)->DEF,
			&(chara + LoopCnt)->MAX_HP,
			&(chara + LoopCnt)->MAX_ATK,
			&(chara + LoopCnt)->MAX_DEF
		);

		//���̃f�[�^��
		LoopCnt++;
	}

	//�f�[�^�̐����Ⴄ�Ƃ�
	if (LoopCnt - 1 != DataMax)
	{
		MessageBox(GetMainWindowHandle(), path, CSV_DATANUM_ERR_TITLE, MB_OK);	//�ǂݍ��݃G���[
		return FALSE;
	}

	fclose(fp);	//�t�@�C�������

	return TRUE;
}

/// <summary>
/// �X�R�A�f�[�^��ǂݍ��ށiSCORE_DATA�j
/// </summary>
/// <param name="path">�X�R�A�f�[�^�̃p�X</param>
/// <param name="chara">�X�R�A�f�[�^�\���̂̐擪�A�h���X</param>
/// <param name="IsHeader">CSV�t�@�C���̂P�s�ڂ��w�b�_�Ȃ�TRUE</param>
/// <returns>TRUE�͓ǂݍ��߂�/FALSE�͎��s����</returns>
BOOL LoadScoreData(const char* path, SCORE_DATA* score, BOOL IsHeader = FALSE)
{
	FILE* fp;				//�t�@�C���|�C���^
	char GetChar = '\0';	//�擾���镶��
	errno_t FileErr = NULL;	//�t�@�C���ǂݍ��݃G���[���m�F
	int IsEOF = NULL;		//�t�@�C���̏I��肩�`�F�b�N

	//�p�X�̃R�s�[
	SetScoreDataPath(path);

	FileErr = fopen_s(&fp, path, "r");	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
	if (FileErr != NULL)
	{
		//�X�R�A�f�[�^�쐬
		if (CreateScoreData() == FALSE) { return FALSE; }

		//�R�R�܂ł̏����ŁA�X�R�A�f�[�^�͍��ꂽ�n�Y�I

		FileErr = fopen_s(&fp, path, "r");	//�t�@�C����ǂݍ��݃��[�h(r)�ŊJ��
		if (FileErr != NULL)
		{
			MessageBox(GetMainWindowHandle(), path, SCORE_LOAD_ERR_TITLE, MB_OK);	//�Ǎ��G���[
			return FALSE;
		}
	}

	//�������琳��ɓǂݍ��߂��Ƃ��̏���****************************************

	//CSV��1�s�ڂ��w�b�_�̂Ƃ�
	if (IsHeader == TRUE)
	{
		//�P���������o���A���s���q���g�ɂP�s�ڂ�ǂݔ�΂�
		while (GetChar != '\n') { GetChar = fgetc(fp); }
	}

	//���ۂɃf�[�^���i�[����
	while (IsEOF != EOF)	//End Of File�i�t�@�C���̍Ō�j�ł͂Ȃ��Ƃ��J��Ԃ�
	{
		//CSV�̃f�[�^�̂P�s����ǂݎ��
		IsEOF = fscanf_s(
			fp,
			SCORE_DATA_FORMAT,	//�f�[�^���u��s=���R�[�h�v�ŏ�����Ă���̂��|�C���g�I
			&(score)->Name1, STR_MAX,	//�������ǂݍ��ނƂ��́A���̈����ŕ�����ő吔���w�肷��
			&(score)->Score1,
			&(score)->Name2, STR_MAX,	//�������ǂݍ��ނƂ��́A���̈����ŕ�����ő吔���w�肷��
			&(score)->Score2,
			&(score)->Name3, STR_MAX,	//�������ǂݍ��ނƂ��́A���̈����ŕ�����ő吔���w�肷��
			&(score)->Score3
		);
	}

	fclose(fp);	//�t�@�C�������

	return TRUE;
}

/// <summary>
/// �X�R�A�f�[�^�쐬
/// </summary>
/// <returns></returns>
BOOL CreateScoreData(VOID)
{
	//�Ȃ�������X�R�A�f�[�^�����
	FILE* creFp;
	errno_t creFileErr = NULL;	//�t�@�C���ǂݍ��݃G���[���m�F
	creFileErr = fopen_s(&creFp, GetScoreDataPath(), "w");	//�t�@�C�����������݃��[�h(w)�ŊJ��(�쐬����)
	if (creFileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�w�b�_����������
	fprintf_s(creFp,
		"Name1,Score1,Name2,Score2,Name3,Score3\n"
	);

	//��̃X�R�A�f�[�^����������
	fprintf_s(creFp,
		"%s,%d,%s,%d,%s,%d",
		score_dataInit.Name1, score_dataInit.Score1,
		score_dataInit.Name2, score_dataInit.Score2,
		score_dataInit.Name3, score_dataInit.Score3
	);

	fclose(creFp);	//�X�R�A�f�[�^�����

	MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_TITLE, MB_OK);
	return TRUE;
}

/// <summary>
/// �X�R�A�f�[�^�ۑ�
/// </summary>
/// <returns></returns>
BOOL SaveScoreData(VOID)
{
	//�Ȃ�������X�R�A�f�[�^�����
	FILE* creFp;
	errno_t creFileErr = NULL;	//�t�@�C���ǂݍ��݃G���[���m�F
	creFileErr = fopen_s(&creFp, GetScoreDataPath(), "w");	//�t�@�C�����������݃��[�h(w)�ŊJ��(�쐬����)
	if (creFileErr != NULL)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_CREATE_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�w�b�_����������
	fprintf_s(creFp,
		"Name1,Score1,Name2,Score2,Name3,Score3\n"
	);

	//�X�R�A�f�[�^����������
	fprintf_s(creFp,
		"%s,%d,%s,%d,%s,%d",
		score_data.Name1, score_data.Score1,
		score_data.Name2, score_data.Score2,
		score_data.Name3, score_data.Score3
	);

	fclose(creFp);	//�X�R�A�f�[�^�����

	MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_SAVE_TITLE, MB_OK);
	return TRUE;
}

/// <summary>
/// �X�R�A�f�[�^�̍폜
/// </summary>
/// <param name="path">�X�R�A�f�[�^�̃p�X</param>
BOOL DeleteScoreData(VOID)
{
	//�t�@�C���폜
	if (remove(GetScoreDataPath()) != 0)
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_DELETE_ERR_TITLE, MB_OK);
	}
	else
	{
		MessageBox(GetMainWindowHandle(), GetScoreDataPath(), SCORE_DELETE_TITLE, MB_OK);
	}

	//�X�R�A�f�[�^���쐬
	return CreateScoreData();
}

/// <summary>
/// �X�R�A�f�[�^�̃p�X��Ԃ�
/// </summary>
/// <returns></returns>
const char* GetScoreDataPath(VOID)
{
	return score_data.path;
}

/// <summary>
/// �X�R�A�f�[�^�̃p�X��ݒ肷��
/// </summary>
/// <returns></returns>
VOID SetScoreDataPath(const char* path)
{
	strcpyDx(score_data.path, path);
	return;
}

/// <summary>
/// CSV�t�@�C����ǂݍ���
/// </summary>
/// <param name="ImgPath">�}�b�v�`�b�v�̉摜�t�@�C���̃p�X</param>
/// <param name="ShitaPath">���t�@�C���̃p�X</param>
/// <param name="NakaPath">���t�@�C���̃p�X</param>
/// <param name="NakaAtariPath">�������蔻��t�@�C���p�X</param>
/// <param name="UePath">��t�@�C���̃p�X</param>
/// <param name="map">�}�b�v�f�[�^�\���̂̐擪�A�h���X</param>
/// <param name="divYoko">���̕�����</param>
/// <param name="deivTate">�c�̕�����</param>
/// <returns>TRUE�͓ǂݍ��߂�/FALSE�͎��s����</returns>
BOOL LoadCSVMap(const char* ImgPath, const char* ShitaPath, const char* NakaPath, const char* NakaAtariPath, const char* UePath, MAP_DATA* map, int divYoko, int divTate)
{
	//�}�b�v�`�b�v��ǂݍ���
	{
		int Isload = -1;		//�摜���ǂݍ��߂����H

		int TempHandle = LoadGraph(ImgPath);

		//�ꎞ�I�ɉ摜�̃n���h����p�ӂ���
		if (TempHandle == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		//�E�B���h�E�n���h��
				ImgPath,					//�{��
				"�摜�ǂݍ��݃G���[",		//�^�C�g��
				MB_OK						//�{�^��
			);

			return FALSE;	//�ǂݍ��ݎ��s
		}

		//�摜�̕��ƍ������擾
		int Width = -1;		//��
		int Heigth = -1;		//����
		GetGraphSize(TempHandle, &Width, &Heigth);

		//�������ēǂݍ���
		Isload = LoadDivGraph(
			ImgPath,							//�摜�̃p�X
			divYoko * divTate,					//��������
			divYoko, divTate,					//���̕����A�c�̕���
			Width / divYoko, Heigth / divTate,	//�摜�P���̕��A����
			map->handle							//�A���ŊǗ�����z��̐擪�A�h���X
		);

		//�����G���[
		if (Isload == -1)
		{
			MessageBox(
				GetMainWindowHandle(),		//�E�B���h�E�n���h��
				ImgPath,					//�{��
				"�摜�ǂݍ��݃G���[",		//�^�C�g��
				MB_OK						//�{�^��
			);

			return FALSE;	//�ǂݍ��ݎ��s
		}

		//����ݒ�
		map->DivMax = divYoko * divTate;
		GetGraphSize(map->handle[0], &map->width, &map->height);

		//�摜��`�悷��
		map->IsDraw = TRUE;

		//�ꎞ�I�ɓǂݍ��񂾃n���h�������
		DeleteGraph(TempHandle);
	}

	FILE* fp;					//�t�@�C���|�C���^
	char Getchar = '\0';		//�擾���镶��
	int LoopCnt = 0;			//���[�v�J�E���^
	errno_t FileErr = NULL;		//�t�@�C���ǂݍ��݃G���[�m�F
	int IsEOF = NULL;			//�t�@�C���̏I��肩�`�F�b�N

	//��CSV��ǂݎ��
	{
		FileErr = fopen_s(&fp, ShitaPath, "r");	//�t�@�C����ǂݍ���
		if (FileErr != NULL)
		{
			MessageBox(GetMainWindowHandle(), ShitaPath, CSV_LOAD_ERR_TITLE, MB_OK);
			return FALSE;
		}

		//�������琳��ɓǂݍ��߂����̏���********************************

		//���ۂɃf�[�^���i�[����
		IsEOF = NULL; LoopCnt = 0;
		while (IsEOF != EOF)		//End Of File�i�t�@�C���̍Ō�j�ł͂Ȃ��Ƃ��J��Ԃ�
		{
			//�t�@�C�����琔�l����ǂݍ��݁i%d,�j�A�z��Ɋi�[����
			//[LoopCnt / MAP_YOKO_MAX] [LoopCnt % MAO_YOKO_MAX]�́A
			//�Ⴆ��[3][3]�̔z��̂Ƃ��ALoopCnt���T�ł���΁A
			//[5 / 3 = 1][5 % 3 = 2]�ƂȂ�A1�����z��̈ʒu��2�����z��Ƃ��ĕϊ��ł���
			IsEOF = fscanf_s(
				fp,
				CSV_MAP_FORMAT, //�f�[�^���A�uXX,�v�ŕ`����Ă���̂��|�C���g�I
				&map->CSV_shita[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]
			);

			//���̃f�[�^��
			LoopCnt++;
		}

		fclose(fp);	//�t�@�C�������
	}

	//��CSV��ǂݎ��
	{
		FileErr = fopen_s(&fp, NakaPath, "r");
		if (FileErr != NULL)
		{
			MessageBox(GetMainWindowHandle(), NakaPath, CSV_LOAD_ERR_TITLE, MB_OK); //�ǂݍ��݃G���[

			return FALSE;
		}

		//�������琳��ɓǂݍ��߂����̏���****************************************

		//���ۂɃf�[�^���i�[����
		IsEOF = NULL; LoopCnt = 0;
		while (IsEOF != EOF)		//End Of File�i�t�@�C���̍Ō�j�ł͂Ȃ��Ƃ��J��Ԃ�
		{
			//�t�@�C�����琔�l����ǂݍ��݁i%d,�j�A�z��Ɋi�[����
			//[LoopCnt / MAP_YOKO_MAX] [LoopCnt % MAO_YOKO_MAX]�́A
			//�Ⴆ��[3][3]�̔z��̂Ƃ��ALoopCnt���T�ł���΁A
			//[5 / 3 = 1][5 % 3 = 2]�ƂȂ�A1�����z��̈ʒu��2�����z��Ƃ��ĕϊ��ł���
			IsEOF = fscanf_s(
				fp,
				CSV_MAP_FORMAT, //�f�[�^���A�uXX,�v�ŕ`����Ă���̂��|�C���g�I
				&map->CSV_naka[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]
			);

			//���̃f�[�^��
			LoopCnt++;
		}

		fclose(fp);	//�t�@�C�������
	}

	//��������CSV��ǂݎ��
	{
		FileErr = fopen_s(&fp, NakaAtariPath, "r");
		if (FileErr != NULL)
		{
			MessageBox(GetMainWindowHandle(), NakaAtariPath, CSV_LOAD_ERR_TITLE, MB_OK); //�ǂݍ��݃G���[

			return FALSE;
		}

		//�������琳��ɓǂݍ��߂����̏���****************************************

		//���ۂɃf�[�^���i�[����
		IsEOF = NULL; LoopCnt = 0;
		while (IsEOF != EOF)		//End Of File�i�t�@�C���̍Ō�j�ł͂Ȃ��Ƃ��J��Ԃ�
		{
			//�t�@�C�����琔�l����ǂݍ��݁i%d,�j�A�z��Ɋi�[����
			//[LoopCnt / MAP_YOKO_MAX] [LoopCnt % MAO_YOKO_MAX]�́A
			//�Ⴆ��[3][3]�̔z��̂Ƃ��ALoopCnt���T�ł���΁A
			//[5 / 3 = 1][5 % 3 = 2]�ƂȂ�A1�����z��̈ʒu��2�����z��Ƃ��ĕϊ��ł���
			IsEOF = fscanf_s(
				fp,
				CSV_MAP_FORMAT, //�f�[�^���A�uXX,�v�ŕ`����Ă���̂��|�C���g�I
				&map->CSV_naka_atari[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]
			);

			//���̃f�[�^��
			LoopCnt++;
		}

		fclose(fp);	//�t�@�C�������
	}

	//��CSV��ǂݎ��
	{
		FileErr = fopen_s(&fp, UePath, "r");	//�t�@�C����ǂݍ��݃��[�h�i���j�ŊJ��
		if (FileErr != NULL)
		{
			MessageBox(GetMainWindowHandle(), UePath, CSV_LOAD_ERR_TITLE, MB_OK);
			//�ǂݍ��݃G���[
			return FALSE;
		}

		//�������琳��ɓǂݍ��߂����̏���****************************************

		//���ۂɃf�[�^���i�[����
		IsEOF = NULL; LoopCnt = 0;
		while (IsEOF != EOF)		//End Of File�i�t�@�C���̍Ō�j�ł͂Ȃ��Ƃ��J��Ԃ�
		{
			//�t�@�C�����琔�l����ǂݍ��݁i%d,�j�A�z��Ɋi�[����
			//[LoopCnt / MAP_YOKO_MAX] [LoopCnt % MAO_YOKO_MAX]�́A
			//�Ⴆ��[3][3]�̔z��̂Ƃ��ALoopCnt���T�ł���΁A
			//[5 / 3 = 1][5 % 3 = 2]�ƂȂ�A1�����z��̈ʒu��2�����z��Ƃ��ĕϊ��ł���
			IsEOF = fscanf_s(
				fp,
				CSV_MAP_FORMAT, //�f�[�^���A�uXX,�v�ŕ`����Ă���̂��|�C���g�I
				&map->CSV_ue[LoopCnt / MAP1_YOKO_MAX][LoopCnt % MAP1_YOKO_MAX]
			);

			//���̃f�[�^��
			LoopCnt++;
		}

		fclose(fp);	//�t�@�C�������
	}

	//�}�b�v�̓����蔻����쐬
	{
		for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
			{
				//�ʂ�Ȃ��h�c�ł����
				if (map->CSV_naka_atari[tate][yoko] == MAP_STOP_ID)
				{
					//�����蔻����쐬
					map->coll[tate][yoko].left = (yoko + 0) * map->width + 1;
					map->coll[tate][yoko].right = (yoko + 1) * map->width - 1;
					map->coll[tate][yoko].top = (tate + 0) * map->height + 1;
					map->coll[tate][yoko].bottom = (tate + 1) * map->height - 1;
				}
				else
				{
					map->coll[tate][yoko].left = 0;
					map->coll[tate][yoko].right = 0;
					map->coll[tate][yoko].top = 0;
					map->coll[tate][yoko].bottom = 0;
				}

				//�}�b�v�̏ꏊ��ݒ�
				map->x[tate][yoko] = (yoko + 0) * map->width;
				map->y[tate][yoko] = (tate + 0) * map->height;
			}
		}
	}

	return TRUE;
}

/// <summary>
/// �}�b�v�����蔻��
/// </summary>
/// <param name="rect"></param>
/// <param name="map"></param>
/// <returns></returns>
BOOL CollMap(RECT rect, MAP_DATA map)
{
	//�����蔻��`�F�b�N
	for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
	{
		for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
		{
			if (CheckCollRectToRect(rect, map.coll[tate][yoko]) == TRUE)
			{
				return TRUE;
			}
		}
	}

	return FALSE;
}

/// <summary>
/// �}�b�v�`��
/// </summary>
/// <param name="map">�}�b�v�\����</param>
/// <returns></returns>
/// <returns></returns>
VOID DrawMap(MAP_DATA map)
{
	//�摜���`��ł���Ƃ���
	if (map.IsDraw == TRUE)
	{
		for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
			{
				DrawGraph(map.x[tate][yoko], map.y[tate][yoko], map.handle[map.
				CSV_shita[tate][yoko]], TRUE);	//�����C���[
			}
		}

		for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
			{
				DrawGraph(map.x[tate][yoko], map.y[tate][yoko], map.handle[map.
				CSV_naka[tate][yoko]], TRUE);	//�����C���[
			}
		}

		//�����Ƀv���C���[�̉摜��`�悷��
		DrawDivImageChara(&samplePlayerImg);//�T���v�������摜�̕`��
		for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
			{
				DrawGraph(map.x[tate][yoko], map.y[tate][yoko], map.handle[map.
				CSV_ue[tate][yoko]], TRUE);	//�ヌ�C���[
			}
		}
	}

	//�f�o�b�O���[�h�̂Ƃ���
	if (GAME_DEBUG == TRUE)
	{
		for (int tate = 0; tate < MAP1_TATE_MAX; tate++)
		{
			for (int yoko = 0; yoko < MAP1_YOKO_MAX; yoko++)
			{
				//�����蔻���`��
				DrawRect(map.coll[tate][yoko], GetColor(255, 255, 255), FALSE);
			}
		}
	}
	return;
}