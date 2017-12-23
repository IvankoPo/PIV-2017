#pragma once
#include "stdafx.h"

namespace lex
{
	struct Lex
	{
		IT::IdTable idtable;;
		LT::LexTable lextable;
	};

	Lex lexAnalyze(in::In in);
}