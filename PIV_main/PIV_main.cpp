// PIV_main.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "MFST.h"
#include <Windows.h>

#define LOG_STREAM *log.stream
#define CONSOLE_STREAM cout

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "Russian");
	LOG::Log log = LOG::INITLOG;
	try
	{
		parm::Parm parm = parm::getParm(argc, argv);
		log = LOG::getLog(parm.log);
		LOG::writeLog(log);
		LOG::writeParm(log, parm);
		in::In in = in::getIn(parm.in);
		LOG::writeIn(log, in);
		lex::Lex lex = lex::lexAnalyze(in);
		//MFST_TRACE_START
			unsigned int start_time = clock();
		MFST::Mfst mfst(lex, GRB::getGreibach());
		mfst.start(LOG_STREAM);
		unsigned int end_time = clock();
		unsigned int search_time = end_time - start_time;
		cout << "Кол-во тактов процессора - " << search_time << endl;
		mfst.savededucation();
		if (parm.pAT) mfst.printrules(LOG_STREAM);
		//		bool rc = startPolishNotation(lex);
		//		if (rc)
		//		cout << "Польская запись построена" << endl;
		//		else
		//	cout << "Польская запись не построена" << endl;*/
		if (parm.pLT) LT::showTable(lex.lextable, LOG_STREAM, true);
		if (parm.pIT) IT::showTable(lex.idtable, LOG_STREAM);
		Generator::Generate(parm, lex);
		cout << "========== Результат ==========" << endl;
		Generator::StartCompile(parm);
		LOG::close(log);
	}
	catch (error::Error e)
	{
		writeError(log, e);
	}
	catch (error::ErrorTable e)
	{
		writeError(log, e);
	}
	catch (FST::FST& f)
	{
		*log.stream << "Ошибка в разборе цепочки - " << f.string << endl;
	}
	catch (exception e)
	{
		cout << "Неопознаная ошибка" << endl;
	}
	system("notepad in.txt.log");
	system("pause");
	return 0;
}


