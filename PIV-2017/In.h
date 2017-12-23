#pragma once
#define IN_MAX_LEN_TEXT 1024*1024		// ������������ ������ ��������� ���� = 1��
#define IN_CODE_ENDL '\n'				// ������ ����� ������
#define IN_CODE_QUOTE '\"'
#define IN_CODE_SPACE ' '
#define IN_CODE_DIV  '|'					
#define IN_CODE_NULL '\0'

#define IN_CODE_TABLE {\
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::T, In::F, In::F, In::N, In::F, In::F, In::I, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
	In::S, In::T, In::Q, In::F, In::F, In::F, In::F, In::Q, In::S, In::S, In::S, In::S, In::S, In::S, In::S, In::S, \
	In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::S, In::S, In::S, In::T, \
	In::F, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, \
	In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::F, In::F, In::F, In::F, In::T, \
	In::F, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, \
	In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::S, In::S, In::S, In::F, In::F, \
	\
	In::F, In::F, In::T, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::T, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::T, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::T, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::T, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
}

namespace in
{
	struct In			// �������� ������
	{
		enum { T, F, I, S, N, Q};			// � - ���������� ������, F - ������������, I - ������������, S - ���������, N - ������� �� ����� ������, C - �����������, Q - �������
		int size = 0;							// ������ ��������� ����
		int lines = 0;							// ���������� �����
		int ignor = 0;							// ���������� ����������������� ��������
		unsigned char* text ;					// �������� ��� (Windows - 1251)
		int code[256] = IN_CODE_TABLE;			// ������� ��������: T, F, I ����� ��������
		In();
	};

	In getIn(wchar_t infile[]);					// ������ � ��������� ������� �����
	In clearSpace(In &in);
};