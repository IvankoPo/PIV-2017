#pragma once

#define PARM_IN		L"-in:"				// ���� ��� ����� ��������� ����
#define PARM_OUT	L"-out:"			// ���� ��� ����� ���������� ����
#define PARM_LOG	L"-log:"			// ���� ��� ����� �������
#define PARM_IT		L"-IT"
#define PARM_LT		L"-LT"
#define PARM_AT		L"-AT"
#define PARM_MAX_SIZE 255				// ������������ ����� ������ ���������
#define PARM_OUT_DEFAULT_EXT L".py"	// ���������� ����� ���������� ���� �� ���������
#define PARM_LOG_DEFAULT_EXT L".log"	// ���������� ����� ��������� �� ���������

namespace parm			// ��������� ������� ����������
{
	struct Parm			// ������� ���������
	{
		wchar_t in[PARM_MAX_SIZE];		// -in:		��� ����� ��������� ����
		wchar_t out[PARM_MAX_SIZE];		// -out:	��� ����� ���������� ����
		wchar_t log[PARM_MAX_SIZE];		// -log:	��� ����� ���������
		bool pLT = false;
		bool pIT = false;
		bool pAT = false;
	};

	Parm getParm(int argc, _TCHAR* argv[]);		// ������������ struct PARM �� ������ ���������� ������� main
};