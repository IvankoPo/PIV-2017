#include "stdafx.h"

namespace LT
{
	Entry::Entry(char lexema, int indx, int line, int pr)
	{
		this->lexema = lexema;
		this->idxTI = indx;
		this->sn = line;
		this->priority = pr;
	}

	Entry::Entry()
	{
		this->lexema = LEX_FORBIDDEN;
		this->idxTI = -1;
		this->sn = -1;
		this->priority = -1;
	}

	LexTable Create(int size)
	{
		if (size > LT_MAXSIZE) throw ERROR_THROW(120);
		LexTable Table;
		Table.maxsize = size;
		Table.size = 0;
		Table.table = new Entry[size];
		return Table;
	}

	void Add(LexTable& lextable, Entry entry)
	{
		if (lextable.size > lextable.maxsize) throw ERROR_THROW(121);
		lextable.table[lextable.size++] = entry;
	}

	Entry GetEntry(LexTable& lextable, int n)
	{
		return lextable.table[n];
	}

	void Delete(LexTable& lextable)
	{
		delete[] lextable.table;
	}
		
	

	Entry writeEntry(Entry &entry, char lexema, int indx, int line, int pr)
	{
		entry.lexema = lexema;
		entry.idxTI = indx;
		entry.sn = line;
		entry.priority = pr;
		return entry;
	}

	void showTable(LexTable lextable, ostream& stream, bool needIndx)		// вывод таблицы лексем
	{
		int number = 1;
		stream << "\t“јЅЋ»÷ј Ћ≈ —≈ћ" << endl;
		stream << "01 ";
		for (int i = 0; i < lextable.size; i++)
		{
			if (lextable.table[i].sn != number && lextable.table[i].sn != -1)
			{
				while (lextable.table[i].sn - number > 1)	// пока строки не станут равны
					number++;
				if (number < 9)
					stream << endl << '0' << lextable.table[i].sn << ends;
				else
					stream << endl << lextable.table[i].sn << ends;
				number++;
			}
			stream << lextable.table[i].lexema;
			if (needIndx && (lextable.table[i].lexema == LEX_ID || lextable.table[i].lexema == LEX_OPERATOR || lextable.table[i].lexema == LEX_LITERAL))
				stream << "[" << lextable.table[i].idxTI << "]";
		}
	}
}