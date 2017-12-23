#pragma once
#include "stdafx.h"
#include "Greibach.h"
#include <stack>

#define MFST_DIAGN_MAXSIZE 2*ERROR_MAXSIZE_MESSAGE
#define MFST_DIAGN_NUMBER 3
#define MFST_TRACE_START	cout << setw(4) << left << "���" << ": " \
									  << setw(20) << left << "�������" \
									  << setw(30) << left << "������� �����" \
									  << setw(20) << left << "����" \
									  << endl;

#define MFST_TRACE1		cout << setw(4) << left << ++FST_TRACE_n << ": " \
								  << setw(20) << left << rule.getCRule(rbuf, nrulechain) \
								  << setw(30) << left << getCLenta(lbuf, lenta_position) \
								  << setw(20) << left << getCSt(sbuf) \
								  << endl;

#define MFST_TRACE2		cout << setw(4) << left << FST_TRACE_n<<": " \
								  << setw(20) << left << " " \
								  << setw(30) << left << getCLenta(lbuf, lenta_position) \
								  << setw(20) << left << getCSt(sbuf) \
								  << endl;

#define MFST_TRACE3		cout << setw(4) << left << ++FST_TRACE_n <<": " \
								  << setw(20) << left << " " \
								  << setw(30) << left << getCLenta(lbuf, lenta_position) \
								  << setw(20) << left << getCSt(sbuf) \
								  << endl;

#define MFST_TRACE4(c)	cout << setw(4) << left << ++FST_TRACE_n << ": " << setw(20) << left << c <<endl; 
#define MFST_TRACE5(c)	cout << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << c << endl; 
#define MFST_TRACE6(c, k)	cout << setw(4) << left << FST_TRACE_n << ": " << setw(20) << left << c << k << endl; 
#define MFST_TRACE7		stream << setw(4) << left << state.lenta_position << ": " \
								  << setw(20) << left << rule.getCRule(rbuf, state.nrulechain) \
								  << endl;

typedef stack<short> MFSTSTACK;		// ���� ��������

namespace MFST
{
	struct MfstState				// ��������� �������� (��� ����������)
	{
		short lenta_position;			// ������� �� �����
		short nrule;					// ����� �������� �������
		short nrulechain;				// ����� ������� �������, �������� �������
		MFSTSTACK st;					// ���� ��������
		MfstState();
		MfstState(
			short pposition,			// ������� �� �����
			MFSTSTACK pst,				// ���� ��������
			short pnrulechain			// ����� ������� �������, �������� �������
		);
		MfstState(
			short pposition,			// ������� �� �����
			MFSTSTACK pst,				// ���� ��������
			short pnrule,				// ����� �������� �������
			short pnrulechain			// ����� ������� �������, �������� �������
		);
	};

	struct Mfst				// ���������� �������
	{
		enum RC_STEP {			// ��� �������� ������� step
			NS_OK,				// ������� ������� � �������, ������� �������� � ����
			NS_NORULE,			// �� ������� ������� ���������� (������ � ����������)
			NS_NORULECHAIN,		// �� ������� ���������� ������� ������� (������ � �������� ����)
			NS_ERROR,			// ����������� �������������� ������ ����������
			TS_OK,				// ���. ������ ����� == ������� �����, ������������ �����, pop �����
			TS_NOK,				// ���. ������ ����� != ������� �����, ������������� ���������
			LENTA_END,			// ������� ������� ����� >= lenta_size
			SURPRISE			// ����������� ��� �������� (������ � step)
		};

		struct MfstDiagnosis	// �����������
		{
			short lenta_position;		// ������� �� �����
			RC_STEP rc_step;			// ��� ���������� ����
			short nrule;				// ����� �������
			short nrule_chain;			// ����� ������� �������
			MfstDiagnosis();
			MfstDiagnosis(
				short plenta_position,	// ������� �� �����
				RC_STEP prt_step,		// ��� ���������� ����
				short pnrule,			// ����� �������
				short pnrule_chain		// ����� ������� �������
			);
		} diagnosis[MFST_DIAGN_NUMBER];		// ��������� ����� �������� ���������

		GRBALPHABET* lenta;				// ���������������� (TS/NS) ����� (�� LEX)
		short lenta_position;			// ������� ������� �� �����
		short nrule;					// ����� �������� �������
		short nrulechain;				// ����� ������� �������, �������� �������
		short lenta_size;				// ������ �����
		GRB::Greibach grebach;			// ���������� �������
		lex::Lex lex;					// ��������� ������ ������������ �����������
		MFSTSTACK st;					// ���� ��������
		stack<MfstState> storestate;	// ���� ��� ���������� ��������� 
		Mfst();
		Mfst(
			lex::Lex plex,				// ��������� ������ ������������ �����������
			GRB::Greibach pgrebach		// ���������� �������
		);
		char* getCSt(char* buf);		// �������� ���������� �����
		char* getCLenta(char* buf, short pos, short n = 25);	// �����: n �������� � pos
		char* getDiagnosis(short n, char* buf);		// �������� n-� ������ ����������� ��� 0�00
		bool savestate();				// ��������� ��������� ��������
		bool reststate();				// ������������ ��������� ��������
		bool push_chain(				// ��������� ������� ������� � ����
			GRB::Rule::Chain chain		// ������� �������
		);
		RC_STEP step();					// ��������� ��� ��������
		bool start(ostream& stream);					// ��������� �������
		bool savediagnosis(
			RC_STEP pprc_step			// ��� ���������� ����
		);
		void printrules(std::ostream& stream);				// ������� ������������������ ������

		struct Deducation		// �����
		{
			short size;			// ���������� ����� � ������
			short* nrules;		// ������ ������ ����������
			short* nrulechains;	// ������ ������� ������ ���������� (nrules)
			Deducation() { size = 0; nrules = 0; nrulechains = 0; };
		} deducation;

		bool savededucation();	// ��������� ������ ������
	};
}