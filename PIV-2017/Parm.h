#pragma once

#define PARM_IN		L"-in:"				// ключ для файла исходного кода
#define PARM_OUT	L"-out:"			// ключ для файла объектного кода
#define PARM_LOG	L"-log:"			// ключ для файла журнала
#define PARM_IT		L"-IT"
#define PARM_LT		L"-LT"
#define PARM_AT		L"-AT"
#define PARM_MAX_SIZE 255				// максимальная длина строки параметра
#define PARM_OUT_DEFAULT_EXT L".py"	// расширение файла объектного кода по умолчанию
#define PARM_LOG_DEFAULT_EXT L".log"	// расширение файла протокола по умолчанию

namespace parm			// обработка входных параметров
{
	struct Parm			// входные параметры
	{
		wchar_t in[PARM_MAX_SIZE];		// -in:		имя файла исходного кода
		wchar_t out[PARM_MAX_SIZE];		// -out:	имя файла объектного кода
		wchar_t log[PARM_MAX_SIZE];		// -log:	имя файла протокола
		bool pLT = false;
		bool pIT = false;
		bool pAT = false;
	};

	Parm getParm(int argc, _TCHAR* argv[]);		// сформировать struct PARM на основе параметров функции main
};