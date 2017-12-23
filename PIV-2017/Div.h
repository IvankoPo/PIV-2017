#pragma once

#include "stdafx.h"

#define DIV_MAXSIZE_WORD 255
#define DIV_MAXSIZE_ARRAY 1000

namespace Div
{
	struct Divvy
	{
		char words[DIV_MAXSIZE_ARRAY][DIV_MAXSIZE_WORD];
		int count_words;
		int count_lines;
	};

	Divvy divideWords(in::In);
}