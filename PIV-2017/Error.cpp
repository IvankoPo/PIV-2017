#include "stdafx.h"

namespace error
{
	Error errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "������������ ��� ������"),
		ERROR_ENTRY(1, "��������� ����"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "�������� -in ������ ���� �����"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "��������� ����� �������� ���������"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "������ ��� �������� ����� � �������� ����� (-in)"),
		ERROR_ENTRY(111, "������������ ������ � �������� ����� (-in)"),
		ERROR_ENTRY(112, "������ ��� �������� ����� ��������� (-log)"),
		ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "[LA] �������� ������������ ������ ������� ������"),
		ERROR_ENTRY(121, "[LA] ������� ������ �����������"),
		ERROR_ENTRY_NODEF(122), ERROR_ENTRY_NODEF(123), ERROR_ENTRY_NODEF(124),
		ERROR_ENTRY_NODEF(125), ERROR_ENTRY_NODEF(126), ERROR_ENTRY_NODEF(127), ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),  ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY(160, "[LA] �������� ������������ ������ ������� ���������������"),
		ERROR_ENTRY(161, "[LA] ������� ��������������� �����������"),
		ERROR_ENTRY(162, "[LA] ���������� ����������� �������"),
		ERROR_ENTRY(163, "[SEM] �� ��������� ����� ����� ����� �����"),
		ERROR_ENTRY(164, "[SEM] �� ������� ����� �����"),
		ERROR_ENTRY(165, "[SEM] �������������� ����� ������"),
		ERROR_ENTRY(166, "[SEM] ���������� �� ���������"), ERROR_ENTRY(167, "[SEM] �� ������ ��� ������ � ���������� �������"), ERROR_ENTRY(168, "[SEM] ������� �� ���� ���������"), ERROR_ENTRY(169, ""),
		ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "[SA] �������� ��������� ���������"),
		ERROR_ENTRY(601, "[SA] ��������� ��������"),
		ERROR_ENTRY(602, "[SA] ������ � ���������"),
		ERROR_ENTRY(603, "[SA] ������ � ���������� �������"),
		ERROR_ENTRY(604, "[SA] ������ � ���������� ���������� �������"),
		ERROR_ENTRY(605, "[SA] ������ ��� �������������� �������"), ERROR_ENTRY_NODEF(606), ERROR_ENTRY_NODEF(607), ERROR_ENTRY_NODEF(609),
		ERROR_ENTRY_NODEF10(610), ERROR_ENTRY_NODEF10(620), ERROR_ENTRY_NODEF10(630), ERROR_ENTRY_NODEF10(640),
		ERROR_ENTRY_NODEF10(660), ERROR_ENTRY_NODEF10(670), ERROR_ENTRY_NODEF10(680), ERROR_ENTRY_NODEF10(690),
		ERROR_ENTRY_NODEF100(700), ERROR_ENTRY_NODEF100(800), ERROR_ENTRY_NODEF100(900)
	};

	Error getError(int id)
	{
		if (id < 0 || id > ERROR_MAX_ENTRY)  return errors[0];
		return errors[id];
	}

	Error getErrorIn(int id, int line = -1, int col = -1)
	{
		Error error;
		if (id < 0 || id > ERROR_MAX_ENTRY)  return errors[0];
		error.id = id;
		error.inext.line = line;
		error.inext.col = col;
		strcpy_s(error.message, errors[id].message);
		return error;
	}

	void ErrorTable::addError(int id, int line, int col)
	{
		errors[size++] = getErrorIn(id, line, col);
		if (size == ERROR_MAXSISE_TABLE)  throw *this;
	}
};