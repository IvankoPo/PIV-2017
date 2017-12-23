#include "stdafx.h"
#include "Automatic.h"
#include "FST.h"

#define PLUS  '+'
#define MINUS '+'
#define DIV   '/'
#define STAR  '*'
#define FN FST::AUTOMAT_NAME

namespace lex
{
	int getFst(char* word)		// получить атомат для цепочки
	{
		FST::FST* arrayOfFst = FST::getFstArray();
		for (int i = 0; i < FST_ARRAY_SIZE; i++)
		{
			arrayOfFst[i].string = word;
			if (FST::execute(arrayOfFst[i]))
			{
				delete[] arrayOfFst;
				return i;
			}
		}
		delete[] arrayOfFst;
		return -1;
	}

	char* getLiteralName(int& clit) // формирование имени литерала
	{
		char* literalName = new char[ID_LIT_MAXSIZE]{ "" };
		char* buf = new char[ID_LIT_MAXSIZE]{ "L" };
		_itoa_s(++clit, literalName, sizeof(char) * ID_LIT_MAXSIZE, 10);	// преобразуем значение счетчика в строку(literalName)
		literalName = strcat(buf, literalName);	// формируем имя для литерала (L + literalName)
		return literalName;
	}

	Lex lexAnalyze(in::In in)
	{
		LT::LexTable lextable = LT::Create(LT_MAXSIZE);
		IT::IdTable idtable = IT::Create(TI_MAXSIZE);

		Lex lex;
		error::ErrorTable error;

		Div::Divvy div = Div::divideWords(in);
		/*for (int i = 0; i < div.count_words; i++)
			cout << div.words[i] << endl;*/

		int indxLex = 0;		// индекс лексемы
		int idxID = 0;			// индекс идент.
		int clit = 0;			// счетчик литералов
		int line = 1;			// номер строки
		int position = 0;		// номер позиции в исходном файле
		int fstNumber;			// номер автомата в массиве автоматов

		char emptystr[] = "";	// пустая строка
		char* prefix = new char[10]{ "" };	// текущий префикс
		char* bufprefix = new char[10]{ "" };	// буфер для префикса
		char* oldprefix = new char[10]{ "" };	// предыдущий префикс
		char* nameLiteral = new char[ID_LIT_MAXSIZE]{ "" };

		bool findFunc = false;
		bool findParm = false;

		bool findMain = false;

		IT::Entry entryIT;
		FST::FST* arrayOfFst = FST::getFstArray();

		for (int i = 0; i < div.count_words; i++, indxLex++)
		{
			bool findSameID = false;

			if (div.words[i][0] == IN_CODE_DIV) {
				line++;
				position = 0;
				indxLex--;
				continue;
			}

			fstNumber = getFst(div.words[i]);

			if (fstNumber == -1)
			{
				error.addError(162, line, position); i++;
				continue;
			}

			switch (arrayOfFst[fstNumber].autoName)
			{
			case FN::DECLARE:
			case FN::RETURN:
			case FN::PRINT:
			case FN::SEMILICON:
			case FN::LBRACE:
			case FN::RBRACE:
			case FN::EQUAL:
			case FN::EQUALITY:
			case FN::NEQUALITY:
			case FN::COMMA:
			case FN::FUNCTION:
			{
				LT::Entry entryLT(arrayOfFst[fstNumber].lexema, LT_TI_NULLIDX, line, LT_NO_PRIORITY);
				LT::Add(lextable, entryLT);

				if (arrayOfFst[fstNumber].autoName == FN::FUNCTION) {
					entryIT.idtype = IT::F;
					findFunc = true;
				}
				break;
			}
		
        	case FN::INTEGER: case FN::STRING:
			{
				LT::Entry entryLT(arrayOfFst[fstNumber].lexema, LT_TI_NULLIDX, line, LT_NO_PRIORITY);
				LT::Add(lextable, entryLT);
				if (arrayOfFst[fstNumber].autoName == FN::INTEGER) {
					entryIT.iddatatype = IT::INT;
				}
				else {
					entryIT.iddatatype = IT::STR;
					strcpy(entryIT.value.vstr.str, emptystr);
				}
				break;
			}
			case FN::MAIN:
			{
				if (findMain)
					error.addError(163, line, position);
				findMain = true;
				LT::Entry entryLT(arrayOfFst[fstNumber].lexema, LT_TI_NULLIDX, line, LT_NO_PRIORITY);
				LT::Add(lextable, entryLT);
				strcpy(oldprefix, prefix);
				strcpy(prefix, div.words[i]);
				strcpy(entryIT.visibility, emptystr);
				break;
			}
			case FN::ID: 
			{
				// поиск такого же
				int idxIT = IT::IsId(idtable, div.words[i]);	// ищем без префикса (если это функция), а потом с префиксом
				if (idxIT != TI_NULLIDX) {		// если такой идентификатор уже есть
					LT::Entry entryLT(arrayOfFst[fstNumber].lexema, idxIT, line, LT_NO_PRIORITY);;
					LT::Add(lextable, entryLT);
					findFunc = false;
					break;
				}
				if (!findFunc) {
					strcpy(bufprefix, prefix);
					strcpy(div.words[i], strcat(bufprefix, div.words[i]));
					idxIT = IT::IsId(idtable, div.words[i]);
					if (idxIT != TI_NULLIDX) {		// если такой идентификатор уже есть
						LT::Entry entryLT(arrayOfFst[fstNumber].lexema, idxIT, line, LT_NO_PRIORITY);;
						LT::Add(lextable, entryLT);
						break;
					}
				}

				LT::Entry entryLT(arrayOfFst[fstNumber].lexema, idxID++, line, LT_NO_PRIORITY);;
				LT::Add(lextable, entryLT);

				if (findParm) {			// если параметр
					entryIT.idtype = IT::P;
					strcpy(entryIT.visibility, prefix);
				}
				else if (findFunc) {	// если функция
					strcpy(oldprefix, prefix);
					strcpy(prefix, div.words[i]);
					strcpy(entryIT.visibility, emptystr);
					
				}
				else {					// если переменная

					if ((lextable.table[lextable.size - 2].lexema != LEX_DECLARE && lextable.table[lextable.size - 3].lexema != LEX_DECLARE) && (strcmp(div.words[i], "mainstrlen") != 0 && strcmp(div.words[i], "mainsubstr") != 0))
						error.addError(166, line, position);
					entryIT.idtype = IT::V;
					strcpy(entryIT.visibility, prefix);
					if (entryIT.iddatatype == IT::INT)
						entryIT.value.vint = TI_INT_DEFAULT;
					if (entryIT.iddatatype == IT::STR) {
						entryIT.value.vstr.len = 0;
						memset(entryIT.value.vstr.str, TI_STR_DEFAULT, sizeof(char));
					}
				}

				entryIT.idxfirstLE = indxLex;
				strcpy(entryIT.id, div.words[i]);
				IT::Add(idtable, entryIT);
				findFunc = false;
				break;
			}
			case FN::INTLIT:
			{
				int value = atoi((char*)div.words[i]);	// значение литерала
				int idxTI = IT::isLiteral(idtable, value);
				if (idxTI != TI_NULLIDX) {
					LT::Entry entryLT(arrayOfFst[fstNumber].lexema, idxTI, line, LT_NO_PRIORITY);
					LT::Add(lextable, entryLT);
					break;
				}
				LT::Entry entryLT(arrayOfFst[fstNumber].lexema, idxID++, line, LT_NO_PRIORITY);
				LT::Add(lextable, entryLT);
				nameLiteral = getLiteralName(clit);
				IT::writeEntry(entryIT, nameLiteral, indxLex, IT::INT, IT::L, value);
				IT::Add(idtable, entryIT);
				break;
			}
			case FN::STRLIT:
			{
				// запись значения
				int length = strlen(div.words[i]);
				for (int k = 0; k < length; k++)	// перезапись массива, убираем кавычки
					div.words[i][k] = div.words[i][k + 1];
				div.words[i][length - 2] = 0;
				int idxTI = IT::isLiteral(idtable, div.words[i]);
				if (idxTI != TI_NULLIDX) {
					LT::Entry entryLT(arrayOfFst[fstNumber].lexema, idxTI, line, LT_NO_PRIORITY);
					LT::Add(lextable, entryLT);
					break;
				}
				LT::Entry entryLT(arrayOfFst[fstNumber].lexema, idxID++, line, LT_NO_PRIORITY);
				LT::Add(lextable, entryLT);
				nameLiteral = getLiteralName(clit);
				IT::writeEntry(entryIT, nameLiteral, indxLex, IT::STR, IT::L, length - 2, div.words[i]);
				IT::Add(idtable, entryIT);
				break;
			}
			case FN::OPERATOR:
			{
				int priority = -1;
				if (div.words[i][0] == PLUS || div.words[i][0] == MINUS)
					priority = 2;
				if ((div.words[i][0] == STAR || div.words[i][0] == DIV))
					priority = 3;
				LT::Entry entryLT(arrayOfFst[fstNumber].lexema, idxID++, line, priority);
				LT::Add(lextable, entryLT);
				strcpy(entryIT.id, div.words[i]);
				entryIT.idxfirstLE = indxLex;
				entryIT.idtype = IT::OP;
				IT::Add(idtable, entryIT);
				break;
			}
			case FN::LTHESIS: case FN::RTHESIS:
			{
				LT::Entry entryLT(arrayOfFst[fstNumber].lexema, LT_TI_NULLIDX, line, 0);
				LT::Add(lextable, entryLT);
				if (arrayOfFst[fstNumber].autoName == FN::LTHESIS && idtable.table[idxID - 1].idtype == IT::F) {
					findParm = true;
					break;
				}
				if (arrayOfFst[fstNumber].autoName == FN::RTHESIS && findParm && div.words[i + 1][0] != LEX_LEFTBRACE && div.words[i + 2][0] != LEX_LEFTBRACE) {
					// если после функции нет {
					strcpy(prefix, oldprefix);		// возвращаем предыдущую обл. видимости
				}
				findParm = false;
				break;
			}
			}
			position += strlen(div.words[i]);
		}
		if (!findMain)
			error.addError(164, line, position);
		if (error.size != 0)
			throw error;
		lex.idtable = idtable;
		lex.lextable = lextable;
		return lex;
	}
}