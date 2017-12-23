#pragma once
#include "stdafx.h"
namespace LOG	// ������ � ����������
{
	struct Log		// ��������
	{
		wchar_t logfile[PARM_MAX_SIZE];		// ��� ����� ���������
		std::ofstream *stream;				// �������� ����� ���������
	};

	static const Log INITLOG = { L"", NULL };	// ��������� ��� ��������� ������������� LOG
	Log getLog(wchar_t logfile[]);				// ������������ ��������� LOG
	void writeLine(Log log, char* c, ...);		// ������� � �������� ������������ �����
	void writeLine(Log log, wchar_t* c, ...);	// ������� � �������� ������������ �����
	void writeLog(Log log);						// ������� � �������� ���������
	void writeParm(Log log, parm::Parm parm);	// ������� � �������� ���������� � ������� ����������
	void writeIn(Log log, in::In in);			// ������� � �������� ���������� � ������� ������
	void writeError(Log log, error::Error error);	// ������� � �������� ���������� �� ������
	void writeError(Log log, error::ErrorTable error);
	void close(Log log);						// ������� ��������
};