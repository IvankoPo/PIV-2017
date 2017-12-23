#include "stdafx.h"
#include <cwchar>

namespace parm
{
	Parm getParm(int argc, _TCHAR* argv[])
	{
		Parm parm;
		wcscpy_s(parm.in, L"");
		wcscpy_s(parm.out, L"");
		wcscpy_s(parm.log, L"");

		int size_parm_in = wcslen(PARM_IN), size_parm_out = wcslen(PARM_OUT), size_parm_log = wcslen(PARM_LOG);

		if (argc == 1)  throw ERROR_THROW(100);

		for (int i = 1; i < argc; i++) {
			if (wcslen(argv[i]) > PARM_MAX_SIZE)  throw ERROR_THROW(104);
			if (wcsstr(argv[i], PARM_IN) == argv[i])  wcscpy_s(parm.in, argv[i] + size_parm_in);
			else if (wcsstr(argv[i], PARM_OUT) == argv[i])  wcscpy_s(parm.out, argv[i] + size_parm_out);
			else if (wcsstr(argv[i], PARM_LOG) == argv[i])  wcscpy_s(parm.log, argv[i] + size_parm_log);
			if (wcsstr(argv[i], PARM_IT) == argv[i]) parm.pIT = true;
			if (wcsstr(argv[i], PARM_LT) == argv[i]) parm.pLT = true;
			if (wcsstr(argv[i], PARM_AT) == argv[i]) parm.pAT = true;
		
		}

		if (wcslen(parm.in) == 0)  throw ERROR_THROW(100);
		if (wcslen(parm.out) == 0) {
			if (wcslen(parm.in) + wcslen(PARM_OUT_DEFAULT_EXT) > PARM_MAX_SIZE)  throw ERROR_THROW(104);
			wcscpy_s(parm.out, parm.in);
			wcsncat_s(parm.out, PARM_OUT_DEFAULT_EXT, size_parm_out);
		}
		if (wcslen(parm.log) == 0) {
			if (wcslen(parm.in) + wcslen(PARM_LOG_DEFAULT_EXT) > PARM_MAX_SIZE)  throw ERROR_THROW(104);
			wcscpy_s(parm.log, parm.in);
			wcsncat_s(parm.log, PARM_LOG_DEFAULT_EXT, size_parm_log);
		}
		return parm;
	}
}