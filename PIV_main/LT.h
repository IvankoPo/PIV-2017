#pragma once

#define LT_MAXSIZE		4096		// максимальное количество строк в таблице лексем
#define LT_TI_NULLIDX	0xfffffff	// нет элемента таблицы идентификаторов
#define LT_NO_PRIORITY	-1	// нет необходимости в приоритете
#define LEX_INTEGER		't'	// лексема дл€ integer
#define LEX_STRING		't'	// лексема дл€ string
#define LEX_ID			'i'	// лексема дл€ идентификатора
#define LEX_LITERAL		'l'	// лексема дл€ литерала
#define LEX_FUNCTION	'f'	// лексема дл€ func
#define LEX_DECLARE		'd'	// лексема дл€ var
#define LEX_RETURN		'r'	// лексема дл€ ret
#define LEX_PRINT		'p'	// лексема дл€ output
#define LEX_MAIN		'm'	// лексема дл€ main
#define LEX_SEMICOLON	'.'	// лексема дл€ ;
#define LEX_COMMA		','	// лексема дл€ ,
#define LEX_LEFTBRACE	'<'	// лексема дл€ <
#define LEX_BRACELET	'>'	// лексема дл€ >
#define LEX_LEFTTHESIS	'('	// лексема дл€ (
#define LEX_RIGHTTHESIS	')'	// лексема дл€ )
#define LEX_PLUS		'v'	// лексема дл€ +
#define LEX_MINUS		'v'	// лексема дл€ -
#define LEX_STAR		'v'	// лексема дл€ *
#define LEX_DIRSLASH	'v'	// лексема дл€ /
#define LEX_OPERATOR	'v'	// лексема дл€ операторов
#define LEX_INEQUALITY	'q'	// лексема дл€ знаков сравнени€
#define LEX_EQUAL		'=' // лексема дл€ =
#define LEX_IF			'i'	// лексема дл€ if
#define LEX_ELSE		'i'	// лексема дл€ else
#define LEX_FORBIDDEN	'#'	// запрещенна€ лексема
#define LEX_CALLFUNC	'@' // лексема дл€ вызова функции в ѕќЋ»«

namespace LT		// таблица лексем
{
	struct Entry										// строка таблицы лексем
	{
		char lexema;									// лексема
		int sn;											// номер строки в исходном тексте
		int idxTI;										// индекс в “»
		int priority;									// приоритет
		Entry(char lex, int indx, int line, int pr);	// конструктор с параметрами
		Entry();										// конструктор по умолчанию
	};

	struct LexTable										// экземпл€р таблицы лексем
	{
		int maxsize;									// емкость таблицы лексем
		int size;										// текущий размер таблицы лексем
		Entry* table;									// массив строк таблицы лексем
	};

	LexTable Create(									// создать таблицу лексем
		int size										// емкость таблицы лексем < LT_MAXSIZE
	);

	void Add(											// добавить строку в таблицу лексем
		LexTable& lextable,								// экземпл€р таблицы лексем
		Entry entry										// строка таблицы лексем
	);

	Entry GetEntry(										// получить строку таблицы лексем
		LexTable& lextable,								// экземпл€р таблицы лексем
		int n											// номер получаемой строки
	);

	void Delete(LexTable& lextable);	// удалить таблицу лексем (освободить пам€ть)
	void showTable(LexTable lextable, std::ostream& stream, bool needIndx);	// вывод таблицы лексем
};