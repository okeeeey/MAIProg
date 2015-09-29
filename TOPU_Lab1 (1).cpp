/**************************************************************************
*                      ��� ��� 302 2 ���� ����                            *
***************************************************************************
*Project Type     : Win32 Console                                         *
*Project Name     : TOPU_Lab1                                             *
*Language         : MS Visual Studio 2013 C++                             *
*File Name        : TOPU_Lab1.cpp                                         *
*Programmer(s)    : 4 �������: ����� �., �������� �., ���������� �.,     *
*							   ��������� �.							      *
*Modified by      : -                                                     *
*Created          : 24/09/2015                                            *
*Last Revision    : 28/09/2015                                            *
*Comment          : ����, ������ ���������� �����������                   *
**************************************************************************/

#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;

/*-----------------------*/
/* ���������� ���������  */
/*-------------------------------------------------------------------*/
const char *FRES = "Result.txt";        //���� �������� ������
const double alpha = 0.618;        //����������� ������ (��)

/*********************************************************************/
/*              � � � � � � � � �    � � � � � � �                   */
/*********************************************************************/

//������� ����� �������� ������
void Input(int *chalg, int *chf, double *l, double *eps, double *a, double *b, int *NapOpt, double *lyambda, double *mu);
//�������� ������������� ����������� �������
bool CheckOpt(double b, double a, double l,int chf,int k, int count);
//������� ���������� ��������� (��)
void Algor1(double *a, double *b, double *lyambda, double *mu, int *k, double eps, int chf,int NapOpt, int *count);
//������� ���������� ��������� (�)
void Algor2(double *a, double *b, double *lyambda, double *mu, int *k, int chf, int NapOpt, int *count);
//����ר� �������� �������
double f(double x, int chf);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*%%                       ������� �������                         %%*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
int main()
{
	setlocale(LC_ALL, "Russian");
	system("color F0");                //F - �������� ����� ����, 0 - ����� ������

	double l = 0,
		a = 0,
		b = -1,
		lyambda = 0,
		mu = 0,
		eps = 0,
		xopt = 0;
	int k = 1,
		chf = 0,
		chalg = 0,
		count = 0,
		NapOpt;

	Input(&chalg, &chf, &l, &eps, &a, &b, &NapOpt, &lyambda,&mu);
	cout << "K" << "         ak" << "         bk" << "    Lyambda" << "         Mu" << " F(lyambda)" << "      F(Mu)" << " ����������" << endl;
	while (1)
	{
		if (CheckOpt(b, a, l,chf,k, count))
			{
				system("pause");
				return 0;
			}
		if (chalg == 1)
		{ 
			Algor1(&a, &b, &lyambda, &mu, &k,eps,chf,NapOpt, &count);
		}
		else
		{
			Algor2(&a, &b, &lyambda, &mu, &k, chf,NapOpt, &count);
		}
	}
	system("PAUSE");
	return 0;
}//end main

/*---------------------------------------------------------------------*/
/* ������� ����� �������� ������  */
/*--------------------------------*/
void Input(int *chalg, int *chf, double *l, double *eps, double *a, double *b,int *NapOpt, double *lyambda, double *mu)
{
	cout << "�������� ����� ������ � ��������.\n��� ������ ������ ������� �����:"
		<< "\n1.����� ��������������� ������\n2.����� �������� �������\n\n��� �����: ";
	cin >> *chalg;
	cout << "��� ������ ����� ";
	if (*chalg == 1)
	{
		cout << "��������������� ������.\n";
	}
	else
	{
		cout << "�������� �������.\n";
	}
	cout << "\n�������� �������.\n��� ������ ������� ������� �����:"
		<< "\n1.������� F1\n2.������� F2\n3.������� f = x^2\n\n��� �����: ";
	cin >> *chf;
	cout << "���� ������� ������� ";
	switch (*chf)
	{
	case 1:
		cout << "F1\n";
		break;
	case 2:
		cout << "F2\n";
		break;
	case 3:
		cout << " f = x^2\n";
		break;
	}
	cout << "\n�������� .\n��� ������  ������� �����:"
		<< "\n1.Min\n2.Max\n\n��� �����: ";
	cin >> *NapOpt;
	for (*l; *l <= 0;)
	{
		cout << "\n������� l > 0: ";
		cin >> *l;
		if (*l <= 0) cout << "\n������������ ��������! ��������� ����.";
	}
	if (*chalg == 1)
	{
		for (*eps; *eps <= 0;)
		{
			cout << "\n������� eps > 0: ";
			cin >> *eps;
			if (*eps<= 0) cout << "\n������������ ��������! ��������� ����.";
		}
	}
	while (*a > *b)
	{
		cout << "\n������� a � b:\na = ";
		cin >> *a;
		cout << "b = ";
		cin >> *b;
		if (*a > *b) cout << "\n������������ ��������! ��������� ����.";
	}
	cout << "\n���� ������ �������. �������� ��������:\n"
		<< "l = " << *l << "\na = " << *a << "\nb = " << *b << endl;
	if (*chalg == 1)
	{
			cout << "eps = "<<*eps<<endl;
	}
	else
	{
		*lyambda = *a + (1 - alpha)*(*b - *a);
		*mu = *a + alpha*(*b - *a);
	}
}

/*---------------------------------------------------------------------*/
/* �������� ������������� ����������� �������  */
/*---------------------------------------------*/
bool CheckOpt(double b, double a, double l,int chf,int k, int count)
{
	double x;
	if (abs(b - a) < l)
	{
		x = (a + b) / 2;
		cout << "\n�������� ���������������: [" << a << ";" << b << "]" << endl
			<< "����������� �������� ���������: " << x << endl
			<< "����������� �������� �������: " << f(x, chf) << endl
			<< "���-�� ��������: " << k - 1 << endl
			<<"���-�� ���������� �-���: "<< count + 1 <<endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

/*---------------------------------------------------------------------*/
/* ������� ���������� ��������� (�)  */
/*-----------------------------------*/
void Algor1(double *a, double *b, double *lyambda, double *mu, int *k, double eps,int chf, int NapOpt, int *count)
{
	double fu;

	*lyambda = (*a + *b) / 2 - eps;
	*mu = (*a + *b) / 2 + eps;

	cout << *k << setw(11) << setprecision(2) << *a
		<< setw(11) << setprecision(2) << *b
		<< setw(11) << setprecision(2) << *lyambda
		<< setw(11) << setprecision(2) << *mu;
	fu = f(*lyambda, chf);
	*count+=1;
	cout << setw(11) << setprecision(2) << fu ;
	fu = f(*mu, chf);
	*count+=1;
	cout << setw(11) << setprecision(2) << fu
		 << setw(11) << setprecision(2) << *count << endl;

	if (((f(*lyambda, chf) > f(*mu, chf)) && (NapOpt == 2)) || ((f(*lyambda, chf) < f(*mu, chf)) && (NapOpt == 1)))
	{
		*b = *mu;
	}
	else
	{
		*a = *lyambda;
	}

	*k += 1;
}

/*---------------------------------------------------------------------*/
/* ����ר� �������� �������  */
/*---------------------------*/
double f(double x, int chf)
{
	double fun;
	switch (chf)
	{
	case 3:
		fun = x * x;
		break;
	case 1:
		fun = 2 * x * x - 4 * x + 5;
		break;
	case 2:
		fun = x / (x * x + 1);
		break;
	}
	return fun;
}

/*---------------------------------------------------------------------*/
/* ������� ���������� ��������� (��)  */
/*------------------------------------*/
void Algor2(double *a, double *b, double *lyambda, double *mu, int *k, int chf,int NapOpt, int *count)
{
	double fu;
	cout << *k << setw(11) << setprecision(2) << *a
		<< setw(11) << setprecision(2) << *b
		<< setw(11) << setprecision(2) << *lyambda
		<< setw(11) << setprecision(2) << *mu;
	fu = f(*lyambda, chf);
	*count+=1;
	cout << setw(11) << setprecision(2) << fu;
	fu = f(*mu, chf);
	*count+=1;
	cout << setw(11) << setprecision(2) << fu
		 << setw(11) << setprecision(2) << *count <<  endl;

	if (((f(*lyambda, chf) > f(*mu, chf)) && (NapOpt == 1)) || ((f(*lyambda, chf) < f(*mu, chf)) && (NapOpt == 2)))
		{
			*a = *lyambda;
			*lyambda = *mu;
			*mu = *a + alpha*(*b - *a);
		}
		else
		{
			*b = *mu;
			*mu = *lyambda;
			*lyambda = *a + (1 - alpha)*(*b - *a);
		}
		*k += 1;
}
