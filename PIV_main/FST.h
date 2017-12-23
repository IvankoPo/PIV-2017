#pragma once
#define FST_ARRAY_SIZE 24

namespace FST
{
	enum AUTOMAT_NAME 
	{
		INTEGER, STRING, FUNCTION, DECLARE, MAIN, PRINT, RETURN, OPERATOR, 
		LTHESIS, RTHESIS, SEMILICON, COMMA, LBRACE, RBRACE, ID, INTLIT,
		STRLIT, EQUAL, EQUALITY, NEQUALITY, IF, ELSE
	};

	struct RELATION		// �����:������ -> ������� ����� ��������� ��
	{
		char symbol;	// ������ ��������
		short nnode;	// ����� ������� �������
		RELATION(
			char c = 0x00,	// ������ ��������
			short ns = NULL	// ����� ���������
		);
	};

	struct NODE		// ������� ����� ���������
	{
		short n_relation;		// ���������� ����������� �����
		RELATION *relations;	// ����������� �����
		NODE();
		NODE(
			short n,			// ���������� ����������� �����
			RELATION rel, ...	// ������ �����
		);
	};

	struct FST		// ������������������� �������� �������
	{
		char* string;		// ������� (������, ����������� 0�00)
		char lexema;		// ������� ���������������� ��������
		AUTOMAT_NAME autoName; // ��� ��������
		short position;		// ������� ������� � �������
		short nstates;		// ���������� ��������� ��������
		NODE* nodes;		// ���� ���������: [0] - ��������� ���������, [nstate-1] - ��������
		short* rstates;		// ��������� ��������� �������� �� ������ �������
		FST(
			char* s,		// ������� (������, ����������� 0�00)
			char l,
			AUTOMAT_NAME an,
			short ns,		// ���������� ��������� ��������
			NODE n, ...		// ������ ��������� (���� ���������)
		);
		FST();
	};

	bool step(FST &fst, short *&rstates);
	bool execute(			// ��������� ������������� �������
		FST& fst	// ������������������� �������� �������
	);
	FST* getFstArray();
}
