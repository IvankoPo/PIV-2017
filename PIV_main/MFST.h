#pragma once
#include "stdafx.h"
#include "Greibach.h"
#include <stack>

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
#define MFST_TRACE_START	cout << setw(4) << left << "Шаг" << ": " \
									  << setw(20) << left << "Правило" \
									  << setw(30) << left << "Входная лента" \
									  << setw(20) << left << "Стек" \
									  << endl;

#define MFST_TRACE1		cout << setw(4) << left << ++FST_TRACE_n << ": " \
								  << setw(20) << left << rule.getCRule(rbuf, nrulechain) \
								  << setw(30) << left << getCLenta(lbuf, lenta_position) \
								  << setw(20) << left << getCSt(sbuf) \
								  << endl;

#define MFST_TRACE2		cout << setw(4) << left << FST_TRACE_n<<": " \
								  << setw(20) << left << " " \
								  << setw(30) << left << getCLenta(lbuf, lenta_position) \
								  << setw(20) << left << getCSt(sbuf) \
								  << endl;

#define MFST_TRACE3		cout << setw(4) << left << ++FST_TRACE_n <<": " \
								  << setw(20) << left << " " \
								  << setw(30) << left << getCLenta(lbuf, lenta_position) \
								  << setw(20) << left << getCSt(sbuf) \
								  << endl;

#define MFST_TRACE4(c)	cout << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << c <<endl; 
#define MFST_TRACE5(c)	cout << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << c << endl; 
#define MFST_TRACE6(c, k)	cout << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << c << k << endl; 
#define MFST_TRACE7		stream << setw(4) << left << state.lenta_position << ": " \
								  << setw(20) << left << rule.getCRule(rbuf, state.nrulechain) \
								  << endl;

typedef stack<short> MFSTSTACK;		// стек автомата

namespace MFST
{
	struct MfstState				// состояние автомата (для сохранения)
	{
		short lenta_position;			// позиция на ленте
		short nrule;					// номер текущего правила
		short nrulechain;				// номер текущей цепочки, текущего правила
		MFSTSTACK st;					// стек автомата
		MfstState();
		MfstState(
			short pposition,			// позиция на ленте
			MFSTSTACK pst,				// стек автомата
			short pnrulechain			// номер текущей цепочки, текущего правила
		);
		MfstState(
			short pposition,			// позиция на ленте
			MFSTSTACK pst,				// стек автомата
			short pnrule,				// номер текущего правила
			short pnrulechain			// номер текущей цепочки, текущего правила
		);
	};

	struct Mfst				// магазинный автомат
	{
		enum RC_STEP {			// код возвтара функции step
			NS_OK,				// найдено правило и цепочка, цепочка записана в стек
			NS_NORULE,			// не найдено правило грамматики (ошибка в грамматике)
			NS_NORULECHAIN,		// не найдена подходящая цепочка правила (ошибка в исходном коде)
			NS_ERROR,			// неизвестный нетерминальный символ грамматики
			TS_OK,				// тек. символ ленты == вершине стека, продвинулась лента, pop стека
			TS_NOK,				// тек. символ ленты != вершине стека, восстановлено состояние
			LENTA_END,			// текущая позиция ленты >= lenta_size
			SURPRISE			// неожиданный код возврата (ошибка в step)
		};

		struct MfstDiagnosis	// диагностика
		{
			short lenta_position;		// позиция на ленте
			RC_STEP rc_step;			// код завершения шага
			short nrule;				// номер правила
			short nrule_chain;			// номер цепочки правила
			MfstDiagnosis();
			MfstDiagnosis(
				short plenta_position,	// позиция на ленте
				RC_STEP prt_step,		// код завершения шага
				short pnrule,			// номер правила
				short pnrule_chain		// номер цепочки правила
			);
		} diagnosis[MFST_DIAGN_NUMBER];		// последние самые глубокие сообщения

		GRBALPHABET* lenta;				// перекодированная (TS/NS) лента (из LEX)
		short lenta_position;			// текущая позиция на ленте
		short nrule;					// номер текущего правила
		short nrulechain;				// номер текущей цепочки, текущего правила
		short lenta_size;				// размер ленты
		GRB::Greibach grebach;			// грамматика Грейбах
		lex::Lex lex;					// результат работы лексического анализатора
		MFSTSTACK st;					// стек автомата
		stack<MfstState> storestate;	// стек для сохранения состояний 
		Mfst();
		Mfst(
			lex::Lex plex,				// результат работы лексического анализатора
			GRB::Greibach pgrebach		// грамматика Грейбах
		);
		char* getCSt(char* buf);		// получить содержимое стека
		char* getCLenta(char* buf, short pos, short n = 25);	// лента: n символов с pos
		char* getDiagnosis(short n, char* buf);		// получить n-ю строку диагностики или 0х00
		bool savestate();				// сохранить состояние автомата
		bool reststate();				// восстановить состояние автомата
		bool push_chain(				// поместить цепочку правила в стек
			GRB::Rule::Chain chain		// цепочка правила
		);
		RC_STEP step();					// выполнить шаг автомата
		bool start(ostream& stream);					// запустить автомат
		bool savediagnosis(
			RC_STEP pprc_step			// код завершения шага
		);
		void printrules(std::ostream& stream);				// вывести последовательность правил

		struct Deducation		// вывод
		{
			short size;			// количество шагов в выводе
			short* nrules;		// номера правил грамматики
			short* nrulechains;	// номера цепочек правик грамматики (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;

		bool savededucation();	// сохранить дерево вывода
	};
}