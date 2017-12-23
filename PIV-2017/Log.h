#pragma once
#include "stdafx.h"
namespace LOG	// работа с протоколом
{
	struct Log		// протокол
	{
		wchar_t logfile[PARM_MAX_SIZE];		// имя файла протокола
		std::ofstream *stream;				// выходной поток протокола
	};

	static const Log INITLOG = { L"", NULL };	// структура для начальной инициализации LOG
	Log getLog(wchar_t logfile[]);				// сформировать структуру LOG
	void writeLine(Log log, char* c, ...);		// вывести в протокол конкатенацию строк
	void writeLine(Log log, wchar_t* c, ...);	// вывести в протокол конкатенацию строк
	void writeLog(Log log);						// вывести в протокол заголовок
	void writeParm(Log log, parm::Parm parm);	// вывести в протокол информацию о входных параметрах
	void writeIn(Log log, in::In in);			// вывести в протокол информацию о входном потоке
	void writeError(Log log, error::Error error);	// вывести в протокол информацию об ошибке
	void writeError(Log log, error::ErrorTable error);
	void close(Log log);						// закрыть протокол
};