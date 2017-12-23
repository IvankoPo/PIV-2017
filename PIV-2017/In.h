#pragma once
#define IN_MAX_LEN_TEXT 1024*1024		// максимальный размер исходного кода = 1ћ¬
#define IN_CODE_ENDL '\n'				// символ конца строки
#define IN_CODE_QUOTE '\"'
#define IN_CODE_SPACE ' '
#define IN_CODE_DIV  '|'					
#define IN_CODE_NULL '\0'

#define IN_CODE_TABLE {\
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::T, In::F, In::F, In::N, In::F, In::F, In::I, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
	In::S, In::T, In::Q, In::F, In::F, In::F, In::F, In::Q, In::S, In::S, In::S, In::S, In::S, In::S, In::S, In::S, \
	In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::S, In::S, In::S, In::T, \
	In::F, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, \
	In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::F, In::F, In::F, In::F, In::T, \
	In::F, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, \
	In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::T, In::S, In::S, In::S, In::F, In::F, \
	\
	In::F, In::F, In::T, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::T, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::T, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::T, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::T, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
	In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, In::F, \
}

namespace in
{
	struct In			// исходные данные
	{
		enum { T, F, I, S, N, Q};			// “ - допустимый символ, F - недопустимый, I - игнорируемый, S - сеператор, N - переход на новую строку, C - комментарий, Q - кавычка
		int size = 0;							// размер исходного кода
		int lines = 0;							// количество строк
		int ignor = 0;							// количество проигнорированных символов
		unsigned char* text ;					// исходный код (Windows - 1251)
		int code[256] = IN_CODE_TABLE;			// таблица проверки: T, F, I новое значение
		In();
	};

	In getIn(wchar_t infile[]);					// ввести и проверить входной поток
	In clearSpace(In &in);
};