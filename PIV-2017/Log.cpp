#include "stdafx.h"

namespace LOG
{
	Log getLog(wchar_t logfile[])
	{
		Log log;
		log.stream = new std::ofstream(logfile);
		if (log.stream->fail())  throw ERROR_THROW(112);
		wcscpy_s(log.logfile, logfile);
		return log;
	}

	void writeLine(Log log, char* c, ...)
	{
		char **p = &c;
		while (*p != "")
		{
			(*log.stream) << *p;
			p++;
		}
	}

	void writeLine(Log log, wchar_t* c, ...)
	{
		wchar_t **p = &c;
		char buf[PARM_MAX_SIZE];
		while (*p != L"")
		{
			wcstombs(buf, *p, PARM_MAX_SIZE);
			*(log.stream) << buf;
			p++;
		}
	}

	void writeLog(Log log)
	{
		time_t rawtime;
		struct tm *timeinfo;
		char str[60];			// ������, � ������� ����� ��������� ������� �����                      
		time(&rawtime);			// ������� ���� � ��������
		timeinfo = localtime(&rawtime);		 // ������� ��������� �����, �������������� � ���������
		strftime(str, 60, "---- �������� ------ ����: %d.%m.%Y %X -----------", timeinfo);		// ����������� ������ �������
		*log.stream << str << std::endl;
	}

	void writeParm(Log log, parm::Parm parm)
	{
		char buf[PARM_MAX_SIZE];
		*(log.stream) << "---- ��������� --------" << std::endl;
		wcstombs(buf, parm.log, PARM_MAX_SIZE);
		*(log.stream) << "-log: " << buf << std::endl;
		wcstombs(buf, parm.out, PARM_MAX_SIZE);
		*(log.stream) << "-out: " << buf << std::endl;
		wcstombs(buf, parm.in, PARM_MAX_SIZE);
		*(log.stream) << "-in: " << buf << std::endl;
	}

	void writeIn(Log log, in::In in)
	{
		*log.stream << "---- �������� ������ ------" << std::endl;
		*log.stream << "���������� ��������: " << in.size << std::endl;
		*log.stream << "���������������	   : " << in.ignor << std::endl;
		*log.stream << "���������� �����   : " << in.lines+1 << std::endl;
	}

	void writeError(Log log, error::Error error)
	{
		if (!log.stream)
			std::cout << "������ " << error.id << ": " << error.message << std::endl;
		else if (error.inext.col >= 0 && error.inext.line >= 0)
			*log.stream << "������ " << error.id << ": " << error.message << ", ������ " << error.inext.line << ", ������� " << error.inext.col << std::endl;
		else
			*log.stream << "������ " << error.id << ": " << error.message << std::endl;
	}

	void writeError(Log log, error::ErrorTable error)
	{
		if (!log.stream) {
			for (int i = 0; i < error.size; i++) {
				std::cout	<< "������ " << error.errors[i].id << ": " << error.errors[i].message
							<< ", ������ " << error.errors[i].inext.line << ", ������� " << error.errors[i].inext.col << std::endl;
			}
		}
		else {
			for (int i = 0; i < error.size; i++) {
				*log.stream << "������ " << error.errors[i].id << ": " << error.errors[i].message
							<< ", ������ " << error.errors[i].inext.line << ", ������� " << error.errors[i].inext.col << std::endl;
			}
		}
	}

	void close(Log log)
	{
		log.stream->close();
		delete log.stream;
	}
}