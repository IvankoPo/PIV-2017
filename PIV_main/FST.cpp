#include "stdafx.h"
#include "Automatic.h"
#include "FST.h"

namespace FST
{
	RELATION::RELATION(char c, short nn)
	{
		symbol = c;
		nnode = nn;
	};

	NODE::NODE()
	{
		n_relation = 0;
		RELATION *relations = NULL;
	};

	NODE::NODE(short n, RELATION rel, ...)
	{
		n_relation = n;
		RELATION *p = &rel;
		relations = new RELATION[n];
		for (short i = 0; i < n; i++) relations[i] = p[i];
	};

	FST::FST() {}

	FST::FST(char* s, char l, AUTOMAT_NAME an, short ns, NODE n, ...)
	{
		string = s;
		lexema = l;
		autoName = an;
		nstates = ns;
		nodes = new NODE[ns];
		NODE *p = &n;
		for (int k = 0; k < ns; k++) nodes[k] = p[k];
		rstates = new short[nstates];
		memset(rstates, 0xff, sizeof(short)*nstates);
		rstates[0] = 0;
		position = -1;
	};

	bool step(FST& fst, short* &rstates)
	{
		bool rc = false;
		swap(rstates, fst.rstates);
		for (short i = 0; i < fst.nstates; i++)
		{
			if (rstates[i] == fst.position)
				for (short j = 0; j < fst.nodes[i].n_relation; j++)
				{
					if (fst.nodes[i].relations[j].symbol == fst.string[fst.position])
					{
						fst.rstates[fst.nodes[i].relations[j].nnode] = fst.position + 1;
						rc = true;
					};
				};
		};
		return rc;
	};

	bool execute(FST& fst)
	{
		if (fst.nstates < 0) throw fst;
		short* rstates = new short[fst.nstates];
		memset(rstates, 0xff, sizeof(short)*fst.nstates);
		short lstring = strlen(fst.string);
		bool rc = true;
		for (short i = 0; i < lstring && rc; i++)
		{
			fst.position++;
			rc = step(fst, rstates);
		};
		delete[] rstates;
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);
	};

	FST* getFstArray()
	{
		FST fstDeclare("", LEX_DECLARE, DECLARE, FST_DECLARE);
		FST	fstTypeInteger("", LEX_INTEGER, INTEGER, FST_INTEGER);
		FST fstTypeString("", LEX_STRING, STRING, FST_STRING);
		FST fstFunction("", LEX_FUNCTION, FUNCTION, FST_FUNCTION);
		FST fstReturn("", LEX_RETURN, RETURN, FST_RETURN);
		FST fstPrint("", LEX_PRINT, PRINT, FST_PRINT);
		FST	fstMain("", LEX_MAIN, MAIN, FST_MAIN);
		FST	fstIdentif("", LEX_ID, ID, FST_ID);
		FST	fstLiteralInt("", LEX_LITERAL, INTLIT, FST_INTLIT);
		FST	fstLiteralString("", LEX_LITERAL, STRLIT, FST_STRLIT);
		FST	fstOperator("", LEX_OPERATOR, OPERATOR, FST_OPERATOR);
		FST	fstSemicolon("", LEX_SEMICOLON, SEMILICON, FST_SEMICOLON);
		FST	fstComma("", LEX_COMMA, COMMA, FST_COMMA);
		FST	fstLeftBrace("", LEX_LEFTBRACE, LBRACE, FST_LEFTBRACE);
		FST	fstRightBrace("", LEX_BRACELET, RBRACE, FST_BRACELET);
		FST	fstLeftThesis("", LEX_LEFTTHESIS, LTHESIS, FST_LEFTTHESIS);
		FST	fstRightThesis("", LEX_RIGHTTHESIS, RTHESIS, FST_RIGHTTHESIS);
		FST	fstEqual("", LEX_EQUAL, EQUAL, FST_EQUAL);
		FST	fstEqually("", LEX_INEQUALITY, EQUALITY, FST_EQUALITY);
		FST	fstNotEqually("", LEX_INEQUALITY, NEQUALITY, FST_NOT_EQUALITY);
		FST	fstIf("", LEX_IF, IF, FST_IF);
		FST	fstElse("", LEX_ELSE, ELSE, FST_ELSE);

		FST* ArrayOfFst = new FST[FST_ARRAY_SIZE] { 
			fstDeclare, fstTypeInteger, fstTypeString, fstFunction, fstReturn, fstIf, fstElse,
			fstPrint, fstMain, fstIdentif, fstLiteralInt, fstLiteralString,
			fstOperator, fstSemicolon, fstComma, fstLeftBrace, fstRightBrace,
			fstLeftThesis, fstRightThesis, fstEqual, fstEqually, fstNotEqually };
		
		return ArrayOfFst;
	}
}