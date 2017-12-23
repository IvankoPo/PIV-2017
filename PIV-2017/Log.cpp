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
		char str[60];			// строка, в которой будет храниться текущее время                      
		time(&rawtime);			// текущая дата в секундах
		timeinfo = localtime(&rawtime);		 // текущее локальное время, представленное в структуре
		strftime(str, 60, "---- Протокол ------ Дата: %d.%m.%Y %X -----------", timeinfo);		// форматируем строку времени
		*log.stream << str << std::endl;
	}

	void writeParm(Log log, parm::Parm parm)
	{
		char buf[PARM_MAX_SIZE];
		*(log.stream) << "---- Параметры --------" << std::endl;
		wcstombs(buf, parm.log, PARM_MAX_SIZE);
		*(log.stream) << "-log: " << buf << std::endl;
		wcstombs(buf, parm.out, PARM_MAX_SIZE);
		*(log.stream) << "-out: " << buf << std::endl;
		wcstombs(buf, parm.in, PARM_MAX_SIZE);
		*(log.stream) << "-in: " << buf << std::endl;
	}

	void writeIn(Log log, in::In in)
	{
		*log.stream << "---- Исходные данные ------" << std::endl;
		*log.stream << "Количество символов: " << in.size << std::endl;
		*log.stream << "Проигнорировано	   : " << in.ignor << std::endl;
		*log.stream << "Количество строк   : " << in.lines+1 << std::endl;
	}

	void writeError(Log log, error::Error error)
	{
		if (!log.stream)
			std::cout << "Ошибка " << error.id << ": " << error.message << std::endl;
		else if (error.inext.col >= 0 && error.inext.line >= 0)
			*log.stream << "Ошибка " << error.id << ": " << error.message << ", строка " << error.inext.line << ", позиция " << error.inext.col << std::endl;
		else
			*log.stream << "Ошибка " << error.id << ": " << error.message << std::endl;
	}

	void writeError(Log log, error::ErrorTable error)
	{
		if (!log.stream) {
			for (int i = 0; i < error.size; i++) {
				std::cout	<< "Ошибка " << error.errors[i].id << ": " << error.errors[i].message
							<< ", строка " << error.errors[i].inext.line << ", позиция " << error.errors[i].inext.col << std::endl;
			}
		}
		else {
			for (int i = 0; i < error.size; i++) {
				*log.stream << "Ошибка " << error.errors[i].id << ": " << error.errors[i].message
							<< ", строка " << error.errors[i].inext.line << ", позиция " << error.errors[i].inext.col << std::endl;
			}
		}
	}

	void close(Log log)
	{
		log.stream->close();
		delete log.stream;
	}
}