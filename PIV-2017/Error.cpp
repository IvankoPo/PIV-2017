#include "stdafx.h"

namespace error
{
	Error errors[ERROR_MAX_ENTRY] =
	{
		ERROR_ENTRY(0, "Недопустимый код ошибки"),
		ERROR_ENTRY(1, "Системный сбой"),
		ERROR_ENTRY_NODEF(2), ERROR_ENTRY_NODEF(3), ERROR_ENTRY_NODEF(4), ERROR_ENTRY_NODEF(5),
		ERROR_ENTRY_NODEF(6), ERROR_ENTRY_NODEF(7), ERROR_ENTRY_NODEF(8), ERROR_ENTRY_NODEF(9),
		ERROR_ENTRY_NODEF10(10), ERROR_ENTRY_NODEF10(20), ERROR_ENTRY_NODEF10(30), ERROR_ENTRY_NODEF10(40), ERROR_ENTRY_NODEF10(50),
		ERROR_ENTRY_NODEF10(60), ERROR_ENTRY_NODEF10(70), ERROR_ENTRY_NODEF10(80), ERROR_ENTRY_NODEF10(90),
		ERROR_ENTRY(100, "Параметр -in должен быть задан"),
		ERROR_ENTRY_NODEF(101), ERROR_ENTRY_NODEF(102), ERROR_ENTRY_NODEF(103),
		ERROR_ENTRY(104, "Превышена длина входного параметра"),
		ERROR_ENTRY_NODEF(105), ERROR_ENTRY_NODEF(106), ERROR_ENTRY_NODEF(107),
		ERROR_ENTRY_NODEF(108), ERROR_ENTRY_NODEF(109),
		ERROR_ENTRY(110, "Ошибка при открытии файла с исходным кодом (-in)"),
		ERROR_ENTRY(111, "Недопустимый символ в исходном файле (-in)"),
		ERROR_ENTRY(112, "Ошибка при создании файла протокола (-log)"),
		ERROR_ENTRY_NODEF(113), ERROR_ENTRY_NODEF(114), ERROR_ENTRY_NODEF(115),
		ERROR_ENTRY_NODEF(116), ERROR_ENTRY_NODEF(117), ERROR_ENTRY_NODEF(118), ERROR_ENTRY_NODEF(119),
		ERROR_ENTRY(120, "[LA] Превышен максимальный размер таблицы лексем"),
		ERROR_ENTRY(121, "[LA] Таблица лексем переполнена"),
		ERROR_ENTRY_NODEF(122), ERROR_ENTRY_NODEF(123), ERROR_ENTRY_NODEF(124),
		ERROR_ENTRY_NODEF(125), ERROR_ENTRY_NODEF(126), ERROR_ENTRY_NODEF(127), ERROR_ENTRY_NODEF(128),
		ERROR_ENTRY_NODEF(129),  ERROR_ENTRY_NODEF10(130), ERROR_ENTRY_NODEF10(140), ERROR_ENTRY_NODEF10(150),
		ERROR_ENTRY(160, "[LA] Превышен максимальный размер таблицы идентификаторов"),
		ERROR_ENTRY(161, "[LA] Таблица идентификаторов переполнена"),
		ERROR_ENTRY(162, "[LA] Обнаружена неизвестная лексема"),
		ERROR_ENTRY(163, "[SEM] Не допустимо более одной точки входа"),
		ERROR_ENTRY(164, "[SEM] Не найдено точки входа"),
		ERROR_ENTRY(165, "[SEM] Несоответствие типов данных"),
		ERROR_ENTRY(166, "[SEM] Переменная не объявлена"), ERROR_ENTRY(167, "[SEM] Не верный тип данных в параметрах функции"), ERROR_ENTRY(168, "[SEM] Деление на ноль запрещено"), ERROR_ENTRY(169, ""),
		ERROR_ENTRY_NODEF10(170), ERROR_ENTRY_NODEF10(180), ERROR_ENTRY_NODEF10(190),
		ERROR_ENTRY_NODEF100(200), ERROR_ENTRY_NODEF100(300), ERROR_ENTRY_NODEF100(400), ERROR_ENTRY_NODEF100(500),
		ERROR_ENTRY(600, "[SA] Неверная структура программы"),
		ERROR_ENTRY(601, "[SA] Ошибочный оператор"),
		ERROR_ENTRY(602, "[SA] Ошибка в выражении"),
		ERROR_ENTRY(603, "[SA] Ошибка в параметрах функции"),
		ERROR_ENTRY(604, "[SA] Ошибка в параметрах вызываемой функции"),
		ERROR_ENTRY(605, "[SA] Ошибка при синтаксическом анализе"), ERROR_ENTRY_NODEF(606), ERROR_ENTRY_NODEF(607), ERROR_ENTRY_NODEF(609),
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