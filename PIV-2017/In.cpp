#include "stdafx.h"

namespace in
{
	In::In()
	{
		this->size = 0;
		this->lines = 0;
		this->ignor = 0;
		this->text = new unsigned char[IN_MAX_LEN_TEXT];
	}

	In getIn(wchar_t infile[])
	{
		ifstream file(infile);
		if (file.fail())  throw ERROR_THROW(110);

		In in;
		error::ErrorTable error;
		unsigned char tempChar;
		int position = 0;						// ?
		while ((tempChar = file.get()) && !file.eof())
		{
			switch (in.code[tempChar])
			{
			case in.N: in.text[in.size++] = IN_CODE_DIV; position = 0; in.lines++; break;
			case in.T: case in.S: case in.Q: in.text[in.size++] = tempChar; position++; break;
			case in.F: error.addError(111, in.lines, position++); in.size++; cout << tempChar << endl; break;
			case in.I: in.ignor++; break;			// in.size-- ?
			}
		}
		in.text[in.size] = IN_CODE_NULL;
		if (error.size != 0)
			throw error;
		file.close();
		clearSpace(in);
		return in;
	}

	In clearSpace(In &in)
	{
		bool findLit = false;
		int k = 0;
		unsigned char* text = new unsigned char[in.size];
		for (int i = 0; i < in.size; i++) {
			if (in.text[i] == IN_CODE_QUOTE)  findLit = !findLit;
			if (in.text[i] == IN_CODE_SPACE && !findLit) {
				if (in.code[in.text[i + 1]] == in.S || in.code[in.text[i - 1]] == in.S || i == 0)
					continue;
			}
			text[k++] = in.text[i];
		}
		text[k] = IN_CODE_NULL;
		in.text = text;
		return in;
	}
}