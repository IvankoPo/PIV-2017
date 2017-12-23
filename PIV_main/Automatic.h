#pragma once

#define FST_DECLARE 4,	\
	NODE(1, RELATION('v', 1)),\
	NODE(1, RELATION('a', 2)),\
	NODE(1, RELATION('r', 3)),\
	NODE()

#define FST_INTEGER 7,	\
	NODE(1, RELATION('i', 1)),\
	NODE(1, RELATION('d', 2)),\
	NODE(1, RELATION('n', 3)),\
	NODE(1, RELATION('I', 4)),\
	NODE(1, RELATION('n', 5)),\
	NODE(1, RELATION('t', 6)),\
	NODE()

#define FST_STRING 7,	\
	NODE(1, RELATION('i', 1)),\
	NODE(1, RELATION('d', 2)),\
	NODE(1, RELATION('n', 3)),\
	NODE(1, RELATION('S', 4)),\
	NODE(1, RELATION('t', 5)),\
	NODE(1, RELATION('r', 6)),\
	NODE()

#define FST_FUNCTION 10,	\
	NODE(1, RELATION('b', 1)),\
	NODE(1, RELATION('l', 2)),\
	NODE(1, RELATION('o', 3)),\
	NODE(1, RELATION('c', 4)),\
	NODE(1, RELATION('k', 5)),\
	NODE(1, RELATION('C', 6)),\
	NODE(1, RELATION('o', 7)),\
	NODE(1, RELATION('d', 8)),\
	NODE(1, RELATION('e', 9)),\
	NODE()

#define FST_RETURN 4,	\
	NODE(1, RELATION('r', 1)),\
	NODE(1, RELATION('e', 2)),\
	NODE(1, RELATION('t', 3)),\
	NODE()

#define FST_PRINT 5,	\
	NODE(1, RELATION('s', 1)),\
	NODE(1, RELATION('h', 2)),\
	NODE(1, RELATION('o', 3)),\
	NODE(1, RELATION('w', 4)),\
	NODE()

#define FST_MAIN 5,	\
	NODE(1, RELATION('m', 1)),\
	NODE(1, RELATION('a', 2)),\
	NODE(1, RELATION('i', 3)),\
	NODE(1, RELATION('n', 4)),\
	NODE()

#define FST_IF 7,	\
	NODE(1, RELATION('s', 1)),\
	NODE(1, RELATION('t', 2)),\
	NODE(1, RELATION('r', 2)),\
	NODE(1, RELATION('l', 2)),\
	NODE(1, RELATION('e', 2)),\
	NODE(1, RELATION('n', 2)),\
    NODE()

#define FST_ELSE 7,	\
	NODE(1, RELATION('s', 1)),\
	NODE(1, RELATION('u', 2)),\
	NODE(1, RELATION('b', 3)),\
	NODE(1, RELATION('s', 4)),\
	NODE(1, RELATION('t', 2)),\
	NODE(1, RELATION('r', 2)),\
    NODE()

#define FST_ID 2,	\
	NODE(52,	\
	RELATION('a', 0), RELATION('b', 0), RELATION('c', 0), RELATION('d', 0), RELATION('e', 0), RELATION('f', 0),\
	RELATION('g', 0), RELATION('h', 0), RELATION('i', 0), RELATION('j', 0), RELATION('k', 0), RELATION('l', 0),\
	RELATION('m', 0), RELATION('n', 0), RELATION('o', 0), RELATION('p', 0), RELATION('q', 0), RELATION('r', 0),\
	RELATION('s', 0), RELATION('t', 0), RELATION('u', 0), RELATION('v', 0), RELATION('w', 0), RELATION('x', 0),\
	RELATION('y', 0), RELATION('z', 0),\
	\
	RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1), RELATION('f', 1),\
	RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1),\
	RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1), RELATION('q', 1), RELATION('r', 1),\
	RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),\
	RELATION('y', 1), RELATION('z', 1)),\
	NODE()

#define FST_INTLIT 3,	\
	NODE(21,	\
	RELATION('-', 1), RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), RELATION('5', 1), RELATION('6', 1),\
	RELATION('7', 1), RELATION('8', 1), RELATION('9', 1), RELATION('0', 1),\
	RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2), RELATION('5', 2), RELATION('6', 2), \
	RELATION('7', 2), RELATION('8', 2), RELATION('9', 2), RELATION('0', 2)),\
	\
	NODE(20,	\
	RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), RELATION('5', 1), RELATION('6', 1),\
	RELATION('7', 1), RELATION('8', 1), RELATION('9', 1), RELATION('0', 1),\
	\
	RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2), RELATION('5', 2), RELATION('6', 2),\
	RELATION('7', 2), RELATION('8', 2), RELATION('9', 2), RELATION('0', 2)),\
	NODE()

#define FST_STRLIT 4,	\
	NODE(2, RELATION('\"', 1), RELATION('\"', 2)),\
	NODE(158,	\
	RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1), RELATION('f', 1),\
	RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1), RELATION('k', 1), RELATION('l', 1),\
	RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1), RELATION('q', 1), RELATION('r', 1),\
	RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),\
	RELATION('y', 1), RELATION('z', 1), RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1),\
	RELATION('5', 1), RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1), RELATION('0', 1),\
	\
	RELATION('à', 1), RELATION('á', 1), RELATION('â', 1), RELATION('ã', 1), RELATION('ä', 1), RELATION('å', 1),\
	RELATION('¸', 1), RELATION('æ', 1), RELATION('ç', 1), RELATION('è', 1), RELATION('é', 1), RELATION('ê', 1),\
	RELATION('ë', 1), RELATION('ì', 1), RELATION('í', 1), RELATION('î', 1), RELATION('ï', 1), RELATION('ð', 1),\
	RELATION('ñ', 1), RELATION('ò', 1), RELATION('ó', 1), RELATION('ô', 1), RELATION('õ', 1), RELATION('ö', 1),\
	RELATION('÷', 1), RELATION('ø', 1), RELATION('ù', 1), RELATION('ú', 1), RELATION('û', 1), RELATION('ü', 1),\
	RELATION('ý', 1), RELATION('þ', 1), RELATION('ÿ', 1), RELATION(' ', 1), RELATION('.', 1), RELATION(',', 1),\
	RELATION('?', 1), RELATION('!', 1), RELATION(';', 1), RELATION(':', 1), RELATION('-', 1), RELATION(')', 1),\
	RELATION('(', 1), \
	\
	RELATION('a', 2), RELATION('b', 2), RELATION('c', 2), RELATION('d', 2), RELATION('e', 2), RELATION('f', 2),\
	RELATION('g', 2), RELATION('h', 2), RELATION('i', 2), RELATION('j', 2), RELATION('k', 2), RELATION('l', 2),\
	RELATION('m', 2), RELATION('n', 2), RELATION('o', 2), RELATION('p', 2), RELATION('q', 2), RELATION('r', 2),\
	RELATION('s', 2), RELATION('t', 2), RELATION('u', 2), RELATION('v', 2), RELATION('w', 2), RELATION('x', 2),\
	RELATION('y', 2), RELATION('z', 2), RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2),\
	RELATION('5', 2), RELATION('6', 2), RELATION('7', 2), RELATION('8', 2), RELATION('9', 2), RELATION('0', 2),\
	\
	RELATION('à', 2), RELATION('á', 2), RELATION('â', 2), RELATION('ã', 2), RELATION('ä', 2), RELATION('å', 2),\
	RELATION('¸', 2), RELATION('æ', 2), RELATION('ç', 2), RELATION('è', 2), RELATION('é', 2), RELATION('ê', 2),\
	RELATION('ë', 2), RELATION('ì', 2), RELATION('í', 2), RELATION('î', 2), RELATION('ï', 2), RELATION('ð', 2),\
	RELATION('ñ', 2), RELATION('ò', 2), RELATION('ó', 2), RELATION('ô', 2), RELATION('õ', 2), RELATION('ö', 2),\
	RELATION('÷', 2), RELATION('ø', 2), RELATION('ù', 2), RELATION('ú', 2), RELATION('û', 2), RELATION('ü', 2),\
	RELATION('ý', 2), RELATION('þ', 2), RELATION('ÿ', 2), RELATION(' ', 2), RELATION('.', 2), RELATION(',', 2),\
	RELATION('?', 2), RELATION('!', 2), RELATION(';', 2), RELATION(':', 2), RELATION('-', 2), RELATION(')', 2),\
	RELATION('(', 2)),\
	\
	NODE(1, RELATION('\"', 3)),\
	NODE()

#define FST_OPERATOR 2,	\
	NODE(4, RELATION('+', 1), RELATION('-', 1), RELATION('*', 1), RELATION('/', 1)),\
	NODE()

#define FST_MORE_OR_EQUALLY 3,	\
	NODE(1, RELATION('>', 1)),\
	NODE(1, RELATION('=', 1)),\
	NODE()

#define FST_LESS_OR_EQUALLY 3,	\
	NODE(1, RELATION('<', 1)),\
	NODE(1, RELATION('=', 1)),\
	NODE()

#define FST_EQUALITY 3,	\
	NODE(1, RELATION('=', 1)),\
	NODE(1, RELATION('=', 1)),\
	NODE()

#define FST_NOT_EQUALITY 3,	\
	NODE(1, RELATION('!', 1)),\
	NODE(1, RELATION('=', 1)),\
	NODE()

#define FST_PLUS 2,	\
	NODE(1, RELATION('+', 1)),\
	NODE()

#define FST_MINUS 2,	\
	NODE(1, RELATION('-', 1)),\
	NODE()

#define FST_STAR 2,	\
	NODE(1, RELATION('*', 1)),\
	NODE()

#define FST_DIRSLASH 2,	\
	NODE(1, RELATION('/', 1)),\
	NODE()

#define FST_SEMICOLON 2,	\
	NODE(1, RELATION('.', 1)),\
	NODE()

#define FST_COMMA 2,	\
	NODE(1, RELATION(',', 1)),\
	NODE()

#define FST_LEFTBRACE 2,	\
	NODE(1, RELATION('<', 1)),\
	NODE()

#define FST_BRACELET 2,	\
	NODE(1, RELATION('>', 1)),\
	NODE()

#define FST_LEFTTHESIS 2,	\
	NODE(1, RELATION('(', 1)),\
	NODE()

#define FST_RIGHTTHESIS 2,	\
	NODE(1, RELATION(')', 1)),\
	NODE()

#define FST_EQUAL 2,	\
	NODE(1, RELATION('=', 1)),\
	NODE()