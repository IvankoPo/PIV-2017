#include "stdafx.h"

namespace Div
{
	Divvy divideWords(in::In in)
	{
		Divvy* div = new Divvy;

		div->count_words = 0;
		div->count_lines = 1;

		bool foundC = false;
		int position = 0;
		for (int i = 0; i < in.size; i++)
		{
			switch (in.code[in.text[i]])
			{
			case in.T: div->words[div->count_words][position++] = in.text[i]; break;
			case in.Q: 
			{
				div->words[div->count_words][position++] = in.text[i++];
				while (in.code[in.text[i]] != in.Q)
					div->words[div->count_words][position++] = in.text[i++];
				div->words[div->count_words][position++] = in.text[i];
				div->words[div->count_words++][position] = IN_CODE_NULL;
				position = 0; 
				break;
			}
			case in.S:
			{
				if (in.text[i] == IN_CODE_DIV)
				{
					if (in.code[in.text[i - 1]] != in.S && in.code[in.text[i - 1]] != in.Q && !foundC)
						div->words[div->count_words++][position] = IN_CODE_NULL;
					div->words[div->count_words][0] = IN_CODE_DIV;
					div->words[div->count_words++][1] = IN_CODE_NULL;
					div->count_lines++; position = 0; 
					foundC = false;
					break;
				}

				if (in.text[i] == IN_CODE_SPACE)
				{
					div->words[div->count_words++][position] = IN_CODE_NULL;
					position = 0; 
					break;
				}

				if (in.text[i + 1] == '=' && (in.text[i] == '=' || in.text[i] == '<' || in.text[i] == '>' || in.text[i] == '!'))
				{
					div->words[div->count_words][0] = in.text[i++];
					div->words[div->count_words][1] = in.text[i];
					div->words[div->count_words++][2] = IN_CODE_NULL;
					position = 0;
					break;
				}
				
				if (in.code[in.text[i - 1]] == in.T)
				{
					div->words[div->count_words++][position] = IN_CODE_NULL; 
					position = 0;
				}

				div->words[div->count_words][0] = in.text[i];
				div->words[div->count_words++][1] = IN_CODE_NULL;
			}
			}
		}
		return *div;
	}
}