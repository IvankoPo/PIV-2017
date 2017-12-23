#pragma once

#define LT_MAXSIZE		4096		// ������������ ���������� ����� � ������� ������
#define LT_TI_NULLIDX	0xfffffff	// ��� �������� ������� ���������������
#define LT_NO_PRIORITY	-1	// ��� ������������� � ����������
#define LEX_INTEGER		't'	// ������� ��� integer
#define LEX_STRING		't'	// ������� ��� string
#define LEX_ID			'i'	// ������� ��� ��������������
#define LEX_LITERAL		'l'	// ������� ��� ��������
#define LEX_FUNCTION	'f'	// ������� ��� func
#define LEX_DECLARE		'd'	// ������� ��� var
#define LEX_RETURN		'r'	// ������� ��� ret
#define LEX_PRINT		'p'	// ������� ��� output
#define LEX_MAIN		'm'	// ������� ��� main
#define LEX_SEMICOLON	'.'	// ������� ��� ;
#define LEX_COMMA		','	// ������� ��� ,
#define LEX_LEFTBRACE	'<'	// ������� ��� <
#define LEX_BRACELET	'>'	// ������� ��� >
#define LEX_LEFTTHESIS	'('	// ������� ��� (
#define LEX_RIGHTTHESIS	')'	// ������� ��� )
#define LEX_PLUS		'v'	// ������� ��� +
#define LEX_MINUS		'v'	// ������� ��� -
#define LEX_STAR		'v'	// ������� ��� *
#define LEX_DIRSLASH	'v'	// ������� ��� /
#define LEX_OPERATOR	'v'	// ������� ��� ����������
#define LEX_INEQUALITY	'q'	// ������� ��� ������ ���������
#define LEX_EQUAL		'=' // ������� ��� =
#define LEX_IF			'i'	// ������� ��� if
#define LEX_ELSE		'i'	// ������� ��� else
#define LEX_FORBIDDEN	'#'	// ����������� �������
#define LEX_CALLFUNC	'@' // ������� ��� ������ ������� � �����

namespace LT		// ������� ������
{
	struct Entry										// ������ ������� ������
	{
		char lexema;									// �������
		int sn;											// ����� ������ � �������� ������
		int idxTI;										// ������ � ��
		int priority;									// ���������
		Entry(char lex, int indx, int line, int pr);	// ����������� � �����������
		Entry();										// ����������� �� ���������
	};

	struct LexTable										// ��������� ������� ������
	{
		int maxsize;									// ������� ������� ������
		int size;										// ������� ������ ������� ������
		Entry* table;									// ������ ����� ������� ������
	};

	LexTable Create(									// ������� ������� ������
		int size										// ������� ������� ������ < LT_MAXSIZE
	);

	void Add(											// �������� ������ � ������� ������
		LexTable& lextable,								// ��������� ������� ������
		Entry entry										// ������ ������� ������
	);

	Entry GetEntry(										// �������� ������ ������� ������
		LexTable& lextable,								// ��������� ������� ������
		int n											// ����� ���������� ������
	);

	void Delete(LexTable& lextable);	// ������� ������� ������ (���������� ������)
	void showTable(LexTable lextable, std::ostream& stream, bool needIndx);	// ����� ������� ������
};