/*	Bartosz Ujazdowski
*	202322
*	Algorytm Booth'a
*/

#include <iostream>

using namespace std;

struct iloczyn_t {
	char M[8];
	char A[8];
	char Q[8];
	char Q_1;
};

void init(iloczyn_t * p, const char * A, const char * B)
{
	memset(p, '0', sizeof(iloczyn_t));
	memcpy(p->M, A, 8);
	memcpy(p->Q, B, 8);
}

void show_num(char * num)
{

	for (int i = 0; i < 8; i++)
		cout << num[i];
}

void show_row(iloczyn_t *p, int event)
{
	char buf[6] = { 0 };
	switch (event)
	{
	case -1:
		memcpy(buf, "-->", 3);
		break;
	case 0:
		memcpy(buf, "A - M", 5);
		break;
	case 1:
		memcpy(buf, "A + M", 5);
		break;
	}

	show_num(p->A); cout << " | "; show_num(p->Q); cout << " | " << p->Q_1 << " | " << buf << endl;
}

int cmp(iloczyn_t *p)
{
	if (p->Q_1 == p->Q[7])  return -1;	//11 lub 00
	else if (p->Q_1 == '0') return 0;	//10 A - M
	else					return 1;	//01 A + M
}

void shift(iloczyn_t *p)
{
	char tmp = p->A[0];
	for (int i = 1; i < 17; i++)
	{
		char help = p->A[i];
		p->A[i] = tmp;
		tmp = help;
	}
}

void sub_help_borrow(iloczyn_t *p, int pos, char *borrow)
{
	for (int i = pos; i != -1; i--)
	{
		borrow[i] = '1';
		if (p->A[i] == '1')
			return;
	}
}

void sub(iloczyn_t *p)
{
	char borrow[8] = { '0', '0', '0', '0', '0', '0', '0', '0' };

	for (int i = 0; i < 8; i++)
	{
		int pos = 7 - i;

		if (p->A[pos] == '0' && p->M[pos] == '0' && borrow[pos] == '0')		 { p->A[pos] = '0'; }
		else if (p->A[pos] == '0' && p->M[pos] == '0' && borrow[pos] == '1') { p->A[pos] = '1'; }
		else if (p->A[pos] == '0' && p->M[pos] == '1' && borrow[pos] == '0') { p->A[pos] = '1'; if (pos != 0) sub_help_borrow(p, pos - 1, borrow); }
		else if (p->A[pos] == '0' && p->M[pos] == '1' && borrow[pos] == '1') { p->A[pos] = '0'; }
		else if (p->A[pos] == '1' && p->M[pos] == '0' && borrow[pos] == '0') { p->A[pos] = '1'; }
		else if (p->A[pos] == '1' && p->M[pos] == '0' && borrow[pos] == '1') { p->A[pos] = '0'; }
		else if (p->A[pos] == '1' && p->M[pos] == '1' && borrow[pos] == '0') { p->A[pos] = '0'; }
		else if (p->A[pos] == '1' && p->M[pos] == '1' && borrow[pos] == '1') { p->A[pos] = '1'; if ( pos != 0 ) sub_help_borrow(p, pos - 1, borrow);	}
		else cout << "Blad";
	}

}
void add(iloczyn_t *p)
{
	char carry = '0';

	for (int i = 0; i < 8; i++)
	{
		int pos = 7 - i;
		if		(carry == '0' && p->A[pos] == '0' && p->M[pos] == '0') {}
		else if (carry == '0' && p->A[pos] == '0' && p->M[pos] == '1') { p->A[pos] = '1'; }
		else if (carry == '0' && p->A[pos] == '1' && p->M[pos] == '0') {}
		else if (carry == '0' && p->A[pos] == '1' && p->M[pos] == '1') { p->A[pos] = '0'; carry = '1'; }
		else if (carry == '1' && p->A[pos] == '0' && p->M[pos] == '0') { p->A[pos] = '1'; }
		else if (carry == '1' && p->A[pos] == '0' && p->M[pos] == '1') { carry = '1'; }
		else if (carry == '1' && p->A[pos] == '1' && p->M[pos] == '0') { p->A[pos] = '0'; carry = '1'; }
		else if (carry == '1' && p->A[pos] == '1' && p->M[pos] == '1') { carry = '1'; }
	}
}

void multiply(iloczyn_t *p)
{
	show_num(p->M); cout << " x "; show_num(p->Q); cout << endl;

	for (int i = 0; i < 8; i++)
	{
		switch (cmp(p))
		{
		case -1:
			break;
		case 0:
			show_row(p, 0);
			sub(p);
			break;
		case 1:
			show_row(p, 1);
			add(p);
			break;
		}

		show_row(p, -1);
		shift(p);
		cout << "------------------------------\n";
	}
	
	show_row(p, 2);
}

int main()
{
	iloczyn_t x;
	init(&x, "10010000", "00010011");

	multiply(&x);

	cin.get();
	cin.get();

	return 0;
}