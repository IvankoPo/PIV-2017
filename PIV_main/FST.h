#pragma once
#define FST_ARRAY_SIZE 24

namespace FST
{
	enum AUTOMAT_NAME 
	{
		INTEGER, STRING, FUNCTION, DECLARE, MAIN, PRINT, RETURN, OPERATOR, 
		LTHESIS, RTHESIS, SEMILICON, COMMA, LBRACE, RBRACE, ID, INTLIT,
		STRLIT, EQUAL, EQUALITY, NEQUALITY, IF, ELSE
	};

	struct RELATION		// ребро:символ -> вершина графа переходов КА
	{
		char symbol;	// символ перехода
		short nnode;	// номер смежной вершины
		RELATION(
			char c = 0x00,	// символ перехода
			short ns = NULL	// новое состояние
		);
	};

	struct NODE		// вершина графа переходов
	{
		short n_relation;		// количество инцидентных ребер
		RELATION *relations;	// инцидентные ребра
		NODE();
		NODE(
			short n,			// количество инцедентных ребер
			RELATION rel, ...	// список ребер
		);
	};

	struct FST		// недетерминированный конечный автомат
	{
		char* string;		// цепочка (строка, завершается 0х00)
		char lexema;		// лексема соответствующего автомата
		AUTOMAT_NAME autoName; // имя автомата
		short position;		// текущая позиция в цепочке
		short nstates;		// количество состояний автомата
		NODE* nodes;		// граф переходов: [0] - начальное состояние, [nstate-1] - конечное
		short* rstates;		// возможные состояния автомата на данной позиции
		FST(
			char* s,		// цепочка (строка, завершается 0х00)
			char l,
			AUTOMAT_NAME an,
			short ns,		// количество состояний автомата
			NODE n, ...		// список состояний (граф переходов)
		);
		FST();
	};

	bool step(FST &fst, short *&rstates);
	bool execute(			// выполнить распознавание цепочки
		FST& fst	// недетерминированный конечный автомат
	);
	FST* getFstArray();
}
