#include "stdafx.h"

namespace IT
{
	IdTable Create(int size)
	{
		if (size > TI_MAXSIZE) throw ERROR_THROW(160);
		IdTable Table;
		Table.maxsize = size;
		Table.size = 0;
		Table.table = new Entry[size];
		return Table;
	}

	void Add(IdTable& idtable, Entry entry)
	{
		if (idtable.size > idtable.maxsize) throw ERROR_THROW(161);
		idtable.table[idtable.size++] = entry;
	}

	Entry GetEntry(IdTable& idtable, int n)
	{
		return idtable.table[n];
	}

	int IsId(IdTable& idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == 0) return i;
		}

		return TI_NULLIDX;
	}

	int isLiteral(IT::IdTable& idtable, int value)
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (idtable.table[i].value.vint == value && idtable.table[i].idtype == IT::L)
			{
				return i;
			}
		}
		return TI_NULLIDX;
	}

	int isLiteral(IT::IdTable& idtable, char value[])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (!(strcmp(idtable.table[i].value.vstr.str, value)))
			{
				return i;
			}
		}
		return TI_NULLIDX;
	}

	void Delete(IdTable& idtable)
	{
		delete[] idtable.table;
	}

	void writeEntry(Entry& e, char* id, int indxLex, IDDATATYPE dt, IDTYPE t, int value)
	{
		e.idtype = t;
		e.iddatatype = dt;
		e.idxfirstLE = indxLex;
		e.value.vint = value;
		strcpy(e.id, id);
	}

	void writeEntry(Entry& e, char* id, int indxLex, IDDATATYPE dt, IDTYPE t, int len, char* str)
	{
		e.idtype = t;
		e.iddatatype = dt;
		e.idxfirstLE = indxLex;
		e.value.vstr.len = len;
		strcpy(e.value.vstr.str, str);
		strcpy(e.id, id);
	}
	void showTable(IdTable& idtable, ostream& stream)
	{
		int i, numberOP = 0;
		stream << endl << endl << "\t\t\t\tТАБЛИЦА ИДЕНТИФИКАТОРОВ" << endl;
		stream << setfill('-') << setw(87) << '-' << endl;
		stream << "   №" << " | " << "Идентификатор" << " | " << "Тип данных" << " | " << "Тип идентификатора" << " | " << "Индекс в ТЛ" << " | " << "Значение    " << endl;
		stream << setw(87) << '-' << endl;
		for (i = 0; i < idtable.size; i++)
		{
			stream << setfill('0') << setw(4) << right << i << " | ";
			stream << setfill(' ') << setw(13) << left << idtable.table[i].id << " | ";
			switch (idtable.table[i].iddatatype)
			{
			case INT: stream << setw(10) << left;
				if (idtable.table[i].idtype == OP) stream << "-" << " | ";
				else stream << "integer" << " | "; break;
			case STR: stream << setw(10) << left;
				if (idtable.table[i].idtype == OP) stream << "-" << " | ";
				else stream << "string" << " | "; break;
			default: stream << setw(10) << left << "unknown" << " | "; break;
			}
			switch (idtable.table[i].idtype)
			{
			case V: stream << setw(18) << left << "переменная" << " | "; break;
			case F: stream << setw(18) << left << "функция" << " | "; break;
			case P: stream << setw(18) << left << "параметр" << " | "; break;
			case L: stream << setw(18) << left << "литерал" << " | "; break;
			case OP: stream << setw(18) << left << "оператор" << " | ";
				numberOP++;
				break;
			default: stream << setw(18) << left << "unknown" << " | "; break;
			}
			stream << setw(11) << left << idtable.table[i].idxfirstLE << " | ";
			if (idtable.table[i].iddatatype == INT && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				stream << setw(18) << left << idtable.table[i].value.vint;
			else if (idtable.table[i].iddatatype == STR && (idtable.table[i].idtype == V || idtable.table[i].idtype == L))
				stream << "[" << idtable.table[i].value.vstr.len << "]\'" << idtable.table[i].value.vstr.str << "\'";
			else
				stream << "-";
			stream << endl;
		}
		stream << setfill('-') << setw(87) << '-' << endl;
		stream << "Количество идентификаторов: " << i - numberOP << endl;
		stream << setw(87) << '-' << endl;
	}
}