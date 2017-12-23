#pragma once
#include "stdafx.h"
namespace Generator
{
	void Generate(parm::Parm par, lex::Lex lex)
	{
		error::ErrorTable error;
		int line = 0;
		ofstream outfile(par.out);
		bool funcFlag = false;
		bool printParFunc = false;
		bool brace = false;
		IT::IDDATATYPE type;
		outfile << "from lib import mainstrlen, mainsubstr" << endl;
		for (int i = 0; i < lex.lextable.size; i++)
		{
			if (lex.lextable.table[i].lexema == LEX_BRACELET)
				brace = false;
			if (lex.lextable.table[i].lexema == LEX_LEFTBRACE)
				brace = true;
			if (lex.lextable.table[i].lexema == LEX_BRACELET && lex.lextable.table[i + 1].lexema != LEX_SEMICOLON)
				error.addError(600, line, 0);
			line = lex.lextable.table[i].sn;
			if (lex.lextable.table[i].lexema == LEX_ID) { // если ид то просто выводим 
				if (lex.lextable.table[i - 1].lexema == LEX_SEMICOLON && funcFlag)
					outfile << "\t";
				// проверяю нет ли перед обьявления и спререди = 
				if (lex.lextable.table[i - 1].lexema == LEX_INTEGER && lex.lextable.table[i + 1].lexema == LEX_SEMICOLON)
					continue;
				if ((lex.lextable.table[i - 1].lexema == LEX_INTEGER || lex.lextable.table[i - 1].lexema == LEX_STRING) && (lex.lextable.table[i+1].lexema != LEX_EQUAL) && !funcFlag)
					continue;
				outfile << lex.idtable.table[lex.lextable.table[i].idxTI].id;
				if (strcmp(lex.idtable.table[lex.lextable.table[i].idxTI].id, "mainsubstr") == 0 && lex.idtable.table[lex.lextable.table[i + 2].idxTI].iddatatype == IT::STR && lex.idtable.table[lex.lextable.table[i + 4].idxTI].iddatatype == IT::STR)
					continue;
				else if (strcmp(lex.idtable.table[lex.lextable.table[i].idxTI].id, "mainsubstr") == 0)
				{
					error.addError(167, line, 0);
				}
				if (strcmp(lex.idtable.table[lex.lextable.table[i].idxTI].id, "mainstrlen") == 0 && lex.idtable.table[lex.lextable.table[i + 2].idxTI].iddatatype == IT::STR)
					continue;
				else if (strcmp(lex.idtable.table[lex.lextable.table[i].idxTI].id, "mainstrlen") == 0)
				{
					error.addError(167, line, 0);
				}
			}
			if (lex.lextable.table[i].lexema == LEX_RETURN) {
				outfile << "\treturn ";
				funcFlag = false;
			}
			if (lex.lextable.table[i].lexema == LEX_FUNCTION) {
				outfile << "def ";
				funcFlag = true;
			}
			if (lex.lextable.table[i].lexema == LEX_PLUS && strcmp(lex.idtable.table[lex.lextable.table[i].idxTI].id, "+") == 0) {
				outfile << "+";
				if (lex.lextable.table[i + 1].lexema == LEX_MINUS)
					error.addError(602, line, 0);
			}
			if (lex.lextable.table[i].lexema == LEX_MINUS && strcmp(lex.idtable.table[lex.lextable.table[i].idxTI].id, "-") == 0) {
				outfile << "-";
				if (lex.lextable.table[i + 1].lexema == LEX_MINUS)
					error.addError(602, line, 0);
			}
			if (lex.lextable.table[i].lexema == LEX_DIRSLASH && strcmp(lex.idtable.table[lex.lextable.table[i].idxTI].id, "/") == 0) {
				if ((lex.lextable.table[i+1].lexema == LEX_ID && lex.idtable.table[lex.lextable.table[i+1].idxTI].idtype != IT::F) || lex.lextable.table[i+1].lexema == LEX_LITERAL)
					{
						if (lex.idtable.table[lex.lextable.table[i + 1].idxTI].value.vint == 0)
						{
							error.addError(168, line, 0);
						}
					}
				if (lex.lextable.table[i + 1].lexema == LEX_MINUS)
					error.addError(602, line, 0);
				outfile << "/";
			}
			if (lex.lextable.table[i].lexema == LEX_STAR && strcmp(lex.idtable.table[lex.lextable.table[i].idxTI].id, "*") == 0) {
				outfile << "*";
				if (lex.lextable.table[i + 1].lexema == LEX_MINUS)
					error.addError(602, line, 0);
			}
			if (lex.lextable.table[i].lexema == LEX_EQUAL) { // если равно то просто выводим его
				outfile << " = ";
				if (lex.lextable.table[i + 1].lexema == LEX_MINUS)
					error.addError(602, line, 0);
				if (lex.lextable.table[i - 1].lexema == LEX_ID && (lex.lextable.table[i + 1].lexema == LEX_ID || lex.lextable.table[i + 1].lexema == LEX_LITERAL || lex.lextable.table[i + 1].lexema == LEX_LEFTTHESIS))
				{
					int j = i + 1;
					type = lex.idtable.table[lex.lextable.table[i - 1].idxTI].iddatatype;
					for (j; lex.lextable.table[j].lexema != LEX_SEMICOLON; j++)
					{
						if (lex.lextable.table[j].lexema == LEX_COMMA || lex.lextable.table[j].lexema == LEX_RIGHTTHESIS || lex.lextable.table[j].lexema == LEX_LEFTTHESIS || lex.lextable.table[j].lexema == LEX_PLUS)
							continue;
						if ((strcmp(lex.idtable.table[lex.lextable.table[j].idxTI].id, "func") == 0) && (lex.idtable.table[lex.lextable.table[j + 2].idxTI].iddatatype != IT::INT || lex.idtable.table[lex.lextable.table[j + 4].idxTI].iddatatype != IT::INT))
							error.addError(167, line, 0);
						if ((strcmp(lex.idtable.table[lex.lextable.table[j].idxTI].id, "func") == 0) && lex.lextable.table[j + 5].lexema != LEX_RIGHTTHESIS)
							error.addError(167, line, 0);
						if (lex.idtable.table[lex.lextable.table[j].idxTI].idtype == IT::F && lex.idtable.table[lex.lextable.table[j].idxTI].iddatatype == type)
						{
							while (lex.lextable.table[j].lexema != LEX_RIGHTTHESIS)
							{
								j++;
							}
							continue;
						}
						if (strcmp(lex.idtable.table[lex.lextable.table[j].idxTI].id, "mainstrlen") == 0 && lex.lextable.table[j + 3].lexema != LEX_RIGHTTHESIS)
							error.addError(167, line, 0);
						if (strcmp(lex.idtable.table[lex.lextable.table[j].idxTI].id, "mainsubstr") == 0 && lex.lextable.table[j + 5].lexema != LEX_RIGHTTHESIS)
							error.addError(167, line, 0);

						if (strcmp(lex.idtable.table[lex.lextable.table[j].idxTI].id, "mainstrlen") == 0 && type == IT::INT) {
							j = j + 2;
							continue;
						}
						else if (strcmp(lex.idtable.table[lex.lextable.table[j].idxTI].id, "mainstrlen") == 0 && type != IT::INT)
							error.addError(165, line, 0);
						if (strcmp(lex.idtable.table[lex.lextable.table[j].idxTI].id, "mainsubstr") == 0 && type == IT::STR)
						{
							j = j + 2;
							continue;
						}
						else if (strcmp(lex.idtable.table[lex.lextable.table[j].idxTI].id, "mainsubstr") == 0 && type != IT::STR)
							error.addError(165, line, 0);

						if (lex.idtable.table[lex.lextable.table[j].idxTI].iddatatype != type)
							error.addError(165, line, 0);
					}
				}

			}
			if (lex.lextable.table[i].lexema == LEX_LEFTTHESIS) {
				outfile << "(";
			}
			if (lex.lextable.table[i].lexema == LEX_RIGHTTHESIS) {
				outfile << ")";
				if (printParFunc)
				{
					outfile << ")";
					printParFunc = false;

				}
				if (lex.lextable.table[i + 1].lexema == LEX_LEFTBRACE) {
					outfile << ":\n\t";
				}
			}
			if (lex.lextable.table[i].lexema == LEX_COMMA) {
				outfile << ", ";
			}
			if (lex.lextable.table[i].lexema == LEX_LITERAL) { // если литерал то просто печатаем его 
				if (lex.idtable.table[lex.lextable.table[i].idxTI].iddatatype == IT::STR)
				{
					outfile << "\"" << lex.idtable.table[lex.lextable.table[i].idxTI].value.vstr.str << "\"";
				}
				if (lex.idtable.table[lex.lextable.table[i].idxTI].iddatatype == IT::INT)
				{
					outfile << lex.idtable.table[lex.lextable.table[i].idxTI].value.vint;
				}
			}
			if (lex.lextable.table[i].lexema == LEX_SEMICOLON) { // если равно то просто печатаем его
				outfile << endl;
			}
			if (lex.lextable.table[i].lexema == LEX_PRINT) { // вывод проверки если ид то выводим если лексема то смотрим какая
				if (lex.lextable.table[i+1].lexema == LEX_ID) {
					if (funcFlag)
						outfile << "\t";
					if (lex.idtable.table[lex.lextable.table[i + 1].idxTI].idtype == IT::F || strcmp(lex.idtable.table[lex.lextable.table[i + 1].idxTI].id, "mainstrlen") == 0 || strcmp(lex.idtable.table[lex.lextable.table[i + 1].idxTI].id, "mainsubstr") == 0)
					{
						outfile << "print(" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id;
						printParFunc = true;
						i = i + 1;
					}
					else
					{
						outfile << "print(" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].id << ")";
						i = i + 1;
					}
				}
				else if (lex.lextable.table[i+1].lexema == LEX_LITERAL) {
					if (funcFlag)
						outfile << "\t";
					if (lex.idtable.table[lex.lextable.table[i + 1].idxTI].iddatatype == IT::STR) {
						outfile << "print(\"" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].value.vstr.str << "\")";
						i = i + 1;
					}
					else if (lex.idtable.table[lex.lextable.table[i + 1].idxTI].iddatatype == IT::INT) {
						outfile << "print(" << lex.idtable.table[lex.lextable.table[i + 1].idxTI].value.vint << ")";
						i = i + 1;
					}
				}
			}
		}
		outfile.close();
		if (brace)
			error.addError(600, line, 0);
		if (error.size != 0)
			throw error;
	}
	void StartCompile(parm::Parm par)
	{
		char buf[255];
		char out[255];
		strcpy_s(buf, sizeof("python "), "python ");

		size_t i;
		wcstombs_s(&i, out, 255, par.out, sizeof(par.out));
		strcat_s(buf, out);
		WinExec(buf, 1);
	}
}