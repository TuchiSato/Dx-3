//�t�H���g�����̃\�[�X�t�@�C��

//########## �w�b�_�[�t�@�C���ǂݍ��� ##########
#include "game.h"
#include "font.h"

//########## �O���[�o���ϐ� ##########

//�t�H���g�f�[�^���Ǘ�
FONT fontdef;		//�f�t�H���g�̃t�H���g

FONT sampleFont1;	//�T���v���̃t�H���g(PC�ɓ����Ă������ȃt�H���g)
FONT sampleFont2;	//�T���v���̃t�H���g(�t�H���g�t�@�C������ǂݍ��񂾃t�H���g)
FONT NosutaruFont;		//�m�X�^���h�b�g

//########## �֐� ##########

/// <summary>
/// �t�H���g�̓Ǎ�
/// </summary>
/// <returns>�ǂݍ��߂���TRUE/�ǂݍ��߂Ȃ�������FALSE</returns>
BOOL FontAdd(VOID)
{
	//�t�H���g���ꎞ�I�ɓǂݍ���(WinAPI)
	if (AddFontResourceEx(FONT_JIYU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), FONT_JIYU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	//�t�H���g���ꎞ�I�ɓǂݍ���(WinAPI)
	if (AddFontResourceEx(FONT_JIYU_PATH, FR_PRIVATE, NULL) == 0)
	{
		//�G���[���b�Z�[�W�\��
		MessageBox(GetMainWindowHandle(), FONT_NOSUTARU_NAME, FONT_INSTALL_ERR_TITLE, MB_OK);
		return FALSE;
	}

	return TRUE;
}

/// <summary>
/// �t�H���g�쐬
/// </summary>
BOOL FontCreate(VOID)
{
	//�f�t�H���g�t�H���g�̏���������
	SetFont(
		&fontdef,			//�ݒ肷��t�H���g
		DEF_FONT_NAME,		//�t�H���g�̖��O���R�s�[
		DEF_FONT_SIZE,		//�t�H���g�̃T�C�Y
		DEF_FONT_THINCK,	//�t�H���g�̑���
		DEF_FONT_TYPE		//�t�H���g�̃^�C�v
	);

	//�f�t�H���g�t�H���g�̃n���h���쐬
	if (FontCreateHandle(&fontdef) == FALSE) { return FALSE; }

	//�f�t�H���g�t�H���g��S�̂ɔ��f
	SetDefaultFont(fontdef);

	//�T���v���t�H���g�̏���ݒ�
	SetFont(
		&sampleFont1,
		FONT_MSGOTH_NAME,
		32,
		5,
		DX_FONTTYPE_ANTIALIASING
	);

	//�t�H���g�n���h�����쐬
	if (FontCreateHandle(&sampleFont1) == FALSE) { return FALSE; }

	//�T���v���t�H���g�̏���ݒ�
	SetFont(
		&sampleFont2,
		FONT_JIYU_NAME,
		64,
		1,
		DX_FONTTYPE_ANTIALIASING
	);

	//�t�H���g�n���h�����쐬
	if (FontCreateHandle(&sampleFont2) == FALSE) { return FALSE; }

	//�T���v���t�H���g�̏���ݒ�
	SetFont(
		&NosutaruFont,
		FONT_NOSUTARU_NAME,
		80,
		1,
		DX_FONTTYPE_ANTIALIASING
	);

	//�t�H���g�n���h�����쐬
	if (FontCreateHandle(&NosutaruFont) == FALSE) { return FALSE; }

	return TRUE;
}

/// <summary>
/// �t�H���g�n���h�����쐬
/// </summary>
/// <param name="f">�t�H���g�\����</param>
/// <returns></returns>
BOOL FontCreateHandle(FONT* f)
{
	f->handle = CreateFontToHandle(
		f->Name,
		f->Size,
		f->Thinck,
		f->Type
	);

	if (f->handle == -1) { return FALSE; }

	return TRUE;
}


/// <summary>
/// �t�H���g�폜
/// </summary>
VOID FontDelete(VOID)
{
	//�f�t�H���g�t�H���g�폜
	DeleteFontToHandle(fontdef.handle);

	DeleteFontToHandle(sampleFont1.handle);	//�T���v���t�H���g�폜
	DeleteFontToHandle(sampleFont2.handle);	//�T���v���t�H���g�폜
	DeleteFontToHandle(NosutaruFont.handle);//�T���v���t�H���g�폜


	return;
}

/// <summary>
/// �����̃t�H���g�\���̂֐ݒ肷��
/// </summary>
/// <param name="f">�ݒ肷��t�H���g�\����</param>
/// <param name="name">�t�H���g��</param>
/// <param name="size">�t�H���g�̃T�C�Y</param>
/// <param name="thinck">�t�H���g�̑���</param>
/// <param name="type">�t�H���g�̃^�C�v</param>
/// <returns></returns>
VOID SetFont(FONT* f, const char* name, int size, int thinck, int type)
{
	strcpy_sDx(f->Name, STR_MAX, name);	//�t�H���g�̖��O���R�s�[
	f->Size = size;						//�t�H���g�̃T�C�Y
	f->Thinck = thinck;					//�t�H���g�̑���
	f->Type = type;						//�t�H���g�̃^�C�v
	return;
}

/// <summary>
/// �t�H���g����ʑS�̂ɔ��f������
/// </summary>
/// <param name="f">�ݒ肷��t�H���g�\����</param>
/// <returns></returns>
VOID SetDefaultFont(FONT f)
{
	ChangeFont(f.Name);				//�t�H���g����ݒ�
	SetFontSize(f.Size);			//�t�H���g�̃T�C�Y��ݒ�
	SetFontThickness(f.Thinck);		//�t�H���g�̑�����ݒ�
	ChangeFontType(f.Type);			//�t�H���g�̃^�C�v��ݒ�

	return;
}

/// <summary>
/// �t�H���g�̍폜
/// </summary>
/// <returns></returns>
VOID FontRemove(VOID)
{
	//�ꎞ�I�ɓǂݍ��񂾃t�H���g���폜(WinAPI)
	RemoveFontResourceEx(FONT_JIYU_PATH, FR_PRIVATE, NULL);

	return;
}