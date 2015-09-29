/**************************************************************************
*                      МАИ Каф 302 2 курс ТОПУ                            *
***************************************************************************
*Project Type     : Win32 Console                                         *
*Project Name     : TOPU_Lab1                                             *
*Language         : MS Visual Studio 2013 C++                             *
*File Name        : TOPU_Lab1.cpp                                         *
*Programmer(s)    : 4 бригада: Жогов А., Кострулёв И., Плотникова А.,     *
*							   Филимонов В.							      *
*Modified by      : -                                                     *
*Created          : 24/09/2015                                            *
*Last Revision    : 28/09/2015                                            *
*Comment          : ТОПУ, методы одномерной оптимизации                   *
**************************************************************************/

#include <math.h>
#include <iostream>
#include <iomanip>

using namespace std;

/*-----------------------*/
/* ГЛОБАЛЬНЫЕ КОНСТАНТЫ  */
/*-------------------------------------------------------------------*/
const char *FRES = "Result.txt";        //файл выходных данных
const double alpha = 0.618;        //Коэффициент сжатия (ЗС)

/*********************************************************************/
/*              П Р О Т О Т И П Ы    Ф У Н К Ц И Й                   */
/*********************************************************************/

//ФУНКЦИЯ ВВОДА ИСХОДНЫХ ДАННЫХ
void Input(int *chalg, int *chf, double *l, double *eps, double *a, double *b, int *NapOpt, double *lyambda, double *mu);
//ПРОВЕРКА ОПТИМАЛЬНОСТИ ПОЛУЧЕННОГО РЕШЕНИЯ
bool CheckOpt(double b, double a, double l,int chf,int k, int count);
//ФУНКЦИЯ ВЫПОЛНЕНИЯ АЛГОРИТМА (ЗС)
void Algor1(double *a, double *b, double *lyambda, double *mu, int *k, double eps, int chf,int NapOpt, int *count);
//ФУНКЦИЯ ВЫПОЛНЕНИЯ АЛГОРИТМА (Д)
void Algor2(double *a, double *b, double *lyambda, double *mu, int *k, int chf, int NapOpt, int *count);
//ПОДСЧЁТ ЗНАЧЕНИЯ ФУНКЦИИ
double f(double x, int chf);

/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
/*%%                       ГЛАВНАЯ ФУНКЦИЯ                         %%*/
/*%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%*/
int main()
{
	setlocale(LC_ALL, "Russian");
	system("color F0");                //F - значение цвета фона, 0 - цвета текста

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
	cout << "K" << "         ak" << "         bk" << "    Lyambda" << "         Mu" << " F(lyambda)" << "      F(Mu)" << " Вычислений" << endl;
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
/* ФУНКЦИЯ ВВОДА ИСХОДНЫХ ДАННЫХ  */
/*--------------------------------*/
void Input(int *chalg, int *chf, double *l, double *eps, double *a, double *b,int *NapOpt, double *lyambda, double *mu)
{
	cout << "Выберите метод работы с функцией.\nДля выбора метода введите цифру:"
		<< "\n1.Метод Дихотомического поиска\n2.Метод Золотого сечения\n\nВаш выбор: ";
	cin >> *chalg;
	cout << "Был выбран метод ";
	if (*chalg == 1)
	{
		cout << "Дихотомического поиска.\n";
	}
	else
	{
		cout << "Золотого сечения.\n";
	}
	cout << "\nВыберите функцию.\nДля выбора функции введите цифру:"
		<< "\n1.Функция F1\n2.Функция F2\n3.Функция f = x^2\n\nВаш выбор: ";
	cin >> *chf;
	cout << "Была выбрана функция ";
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
	cout << "\nВыберите .\nДля выбора  введите цифру:"
		<< "\n1.Min\n2.Max\n\nВаш выбор: ";
	cin >> *NapOpt;
	for (*l; *l <= 0;)
	{
		cout << "\nВведите l > 0: ";
		cin >> *l;
		if (*l <= 0) cout << "\nНекорректное значение! Повторите ввод.";
	}
	if (*chalg == 1)
	{
		for (*eps; *eps <= 0;)
		{
			cout << "\nВведите eps > 0: ";
			cin >> *eps;
			if (*eps<= 0) cout << "\nНекорректное значение! Повторите ввод.";
		}
	}
	while (*a > *b)
	{
		cout << "\nВведите a и b:\na = ";
		cin >> *a;
		cout << "b = ";
		cin >> *b;
		if (*a > *b) cout << "\nНекорректные значение! Повторите ввод.";
	}
	cout << "\nВвод данных окончен. Введённые значения:\n"
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
/* ПРОВЕРКА ОПТИМАЛЬНОСТИ ПОЛУЧЕННОГО РЕШЕНИЯ  */
/*---------------------------------------------*/
bool CheckOpt(double b, double a, double l,int chf,int k, int count)
{
	double x;
	if (abs(b - a) < l)
	{
		x = (a + b) / 2;
		cout << "\nИнтервал неопределённости: [" << a << ";" << b << "]" << endl
			<< "Оптимальное значение аргумента: " << x << endl
			<< "Оптимальное значение функции: " << f(x, chf) << endl
			<< "Кол-во итераций: " << k - 1 << endl
			<<"Кол-во вычислений ф-ции: "<< count + 1 <<endl;
		return 1;
	}
	else
	{
		return 0;
	}
}

/*---------------------------------------------------------------------*/
/* ФУНКЦИЯ ВЫПОЛНЕНИЯ АЛГОРИТМА (Д)  */
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
/* ПОДСЧЁТ ЗНАЧЕНИЯ ФУНКЦИИ  */
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
/* ФУНКЦИЯ ВЫПОЛНЕНИЯ АЛГОРИТМА (ЗС)  */
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
