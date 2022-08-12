// big int sum as string.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <deque>
#include <algorithm>
using namespace std;

string  SUM_STR(string a, string b); ////сложение чисел в формате строки без знака
bool  IS_ZERO(string a); //// проверка числа в формате строки в дополнительном коде на ноль
string POW(string a, int pow); //// возведение в степень числа в формате строки
deque<unsigned int> TO_INT_DEQUE(int a); //// конветация инта в безразмерное число по основанию /max uint + 1
deque<unsigned int> BIG_MUL(deque<unsigned int> x, deque<unsigned int> y); //// умножение безразмерных чисел в системе счисления по основанию /max uint + 1 без знака
string TO_STRING_FROM_BIG(deque<unsigned int> a);//// преобразование безразмерного числа из системы счисления по основанию  /max uint + 1 в десятичную систему в строчном виде
deque<unsigned int> BIG_SUM(int a, int b);//// сложение двух чисел возвращает значение в безразмерном виде /max uint + 1
deque<unsigned int> BIG_SUM(deque<unsigned int> a, deque<unsigned int> b);//// сложение двух безразмерных чисел /max uint + 1
string MUL(string a, string b); //// умнодение чиссел в виде строки в дополнительном коде со знаком
string  SUM_STR_SIG(string a, string b/*, char *sum*/); ///// сложение двух чисел в формате строки со знаком
string factorial(unsigned int n); ////расчёт факториала числа в формате строки



string  SUM_STR_SIG(string a, string b)
{
	short unsigned int E = 0; //перенос

	int size = 0; //размер массива суммы

	bool is_a_negativ = false;
	bool is_b_negativ = false;

	string a_buff = a;
	string b_buff = b;
	/////////////////////////////////проверям числа на знак

	if (a[0] == '-')
	{
		is_a_negativ = true;
		a_buff.erase(0, 1);////удаляем из строки "-"
	}
	if (b[0] == '-')
	{
		is_b_negativ = true;
		b_buff.erase(0, 1);
	}
	////проверка операндов на 0

	if (IS_ZERO(a_buff))
	{
		a_buff.clear();
		b_buff.clear();
		return b;
	}

	if (IS_ZERO(b_buff))
	{
		a_buff.clear();
		b_buff.clear();
		return a;
	}

	int size_a = a_buff.size();
	int size_b = b_buff.size();

	//
	////приводим массивы к одинаковому размеру
	if (size_a > size_b)
	{
		size = size_a;

		for (int i = 0; i < size_a - size_b; i++)
		{
			b_buff = '0' + b_buff;
		}
	}
	else {
		size = size_b;

		for (int i = 0; i < size_b - size_a; i++)
		{
			a_buff = '0' + a_buff;
		}
	}
	//// пераброзуем отрицательную строку в дополнительный код  

	if (is_a_negativ) {

		for (int i = 0; i < a_buff.size(); i ++)
		{
			int num = a_buff[i] - '0';
			num = 9 - num;
			char buf = '0' + num % 10;
			a_buff[i] = buf;
		}
		a_buff = SUM_STR(a_buff, "1");
	}

	if (is_b_negativ) {

		for (int i = 0; i < b_buff.size(); i++)
		{
			int num = b_buff[i] - '0';
			num = 9 - num;
			char buf = '0' + num % 10;
			b_buff[i] = buf;
		}
		b_buff = SUM_STR(b_buff, "1");
	}

	////начинаем сложение 

	string SUM = "";

	int A;
	int B;
	int C;

	for (int i = size - 1; i >= 0; i--)
	{
		A = b_buff[i] - '0'; // to int from char
		B = a_buff[i] - '0'; // to int from char
		C = A + B + E; //сумма одного разряда

		if (C / 10 > 0) //сумма больше 9, перенос в старший разряд = 1
		{
			E = 1;
		}
		else
		{
			E = 0;
		}

		char buf = '0' + C % 10;
		SUM = buf + SUM; //младший разряд записываем в результат
	}
	

	////проверка на переполнение, знак

	if ((is_a_negativ && !is_b_negativ) || (!is_a_negativ && is_b_negativ)) 
	{
		if (E == 0) ////результат отрицательный, переводим в ПК и добовляем "-" спереди
		{
			for (int i = 0; i < SUM.size(); i++)
			{
				int num = SUM[i] - '0';
				num = 9 - num;
				char buf = '0' + num % 10;
				SUM[i] = buf;
			}
			SUM = SUM_STR(SUM, "1");
			SUM = "-" + SUM;
			b_buff.clear();
			a_buff.clear();
			return SUM;
		}

		if (E == 1)
		{
			int zero = 0; ////проверка на 0

			/*for (int i = 0; i < SUM.size(); i++)
			{
				int num = SUM[i] - '0';
				zero += num;
			}*/

			if (IS_ZERO(SUM))
			{
				SUM.clear();
				b_buff.clear();
				a_buff.clear();
				return "0";
			}
			//////////////// коррекция разрадности

			for (int i = 0; i < SUM.size(); i++)
			{
				if (SUM[i] == '0')
				{
					SUM.erase(0, 1);
				}
				else
				{
					break;
				}
			}
			b_buff.clear();
			a_buff.clear();
			return SUM;
			
		}
	}

	if (is_a_negativ && is_b_negativ) {

		if (E == 0) ////число отрицательное с переполнением, переводим сумму в ПК и добавляем в начало строки "-1"
		{
			for (int i = 0; i < SUM.size(); i++)
			{
				int num = SUM[i] - '0';
				num = 9 - num;
				char buf = '0' + num % 10;
				SUM[i] = buf;
			}
			SUM = SUM_STR(SUM, "1");
			SUM = "-1" + SUM;
			b_buff.clear();
			a_buff.clear();
			return SUM;
		}

		if (E == 1) ////результат отрицательный без переполнения, переводим сумму в ПК
		{
			for (int i = 0; i < SUM.size(); i++)
			{
				int num = SUM[i] - '0';
				num = 9 - num;
				char buf = '0' + num % 10;
				SUM[i] = buf;
			}
			SUM = SUM_STR(SUM, "1");
			SUM = "-" + SUM;
			b_buff.clear();
			a_buff.clear();
			return SUM;
		}

	}

	if (!is_a_negativ && !is_b_negativ)
	{
		if (E == 1)
		{
			SUM = '1' + SUM;
		}

		b_buff.clear();
		a_buff.clear();

		return SUM;
	}

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


string  SUM_STR(string a, string b)
{
	short unsigned int E = 0; //перенос

	int size = 0; //размер массива суммы
	int size_a = a.size();
	int size_b = b.size();

	string a_buff = a;
	string b_buff = b;
	
	////проверка операндов на 0

	if (IS_ZERO(a_buff))
	{
		a_buff.clear();
		b_buff.clear();
		return b;
	}

	if (IS_ZERO(b_buff))
	{
		a_buff.clear();
		b_buff.clear();
		return a;
	}

	////приводим массивы к одинаковому размеру
	if (size_a > size_b)
	{
		size = size_a;

		for (int i = 0; i < size_a - size_b; i++)
		{
			b_buff = '0' + b_buff;
		}
	}
	else {
		size = size_b;

		for (int i = 0; i < size_b - size_a; i++)
		{
			a_buff = '0' + a_buff;
		}
	}

	////начинаем сложение 

	string SUM = "";
	
	int A;
	int B;
	int C;

	for (int i = size - 1; i >= 0; i--)
	{
		 A = b_buff[i] - '0'; // to int from char
		 B = a_buff[i] - '0'; // to int from char
		 C = A + B + E; //сумма одного разряда

		 if (C / 10 > 0) //сумма больше 9, перенос в старший разряд = 1
		 {
			 E = 1;
		 }
		 else
		 {
			 E = 0;
		 }

		 char buf = '0' + C % 10;
		 SUM = buf + SUM; //младший разряд записываем в результат
	}

	if (E == 1)
	{
		SUM = '1' + SUM;
	}

	b_buff.clear();
	a_buff.clear();

	 return SUM;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

string MUL(string a, string b)
{
	bool is_a_negativ = false;
	bool is_b_negativ = false;

	string a_buff = a;
	string b_buff = b;
	/////////////////////////////////проверям числа на знак

	if (a[0] == '-')
	{
		is_a_negativ = true;
		a_buff.erase(0, 1);////удаляем из строки "-"
	}
	if (b[0] == '-')
	{
		is_b_negativ = true;
		b_buff.erase(0, 1);
	}

	int size_a = a_buff.size();
	int size_b = b_buff.size();

	if (size_a > size_b)
	{
		string buf_str = a_buff;
		a_buff = b_buff;
		b_buff = buf_str;
		buf_str.clear();
	}
	

	////// проверка операндов на 0

	if (IS_ZERO(a_buff) || IS_ZERO(b_buff))
	{
		return "0";
	}

	//////
	string BUF_SUM = "";
	string SUM = "0";
	int A = 0, B = 0, C = 0, E = 0;

	for (int i = a_buff.size() - 1; i >= 0; i --)
	{
		E = 0;

		for (int j = b_buff.size() - 1; j >= 0; j --)
		{
			int A = b_buff[j] - '0'; // to int from char
			int B = a_buff[i] - '0'; // to int from char
			int C = A * B + E; //сумма одного разряда

			char buf = '0' + (C % 10);

			E = C / 10;

			BUF_SUM = buf + BUF_SUM; //младший разряд записываем в результат
		}

		if (E != 0)
		{
			BUF_SUM = (char)('0' + (E % 10)) + BUF_SUM;
		}

		if (a_buff.size() != 1)
		{
			BUF_SUM.append(a_buff.size() - i -1, '0'); //// сдвиг промежуточного результата на кол во разрядов
		}
		

		SUM = SUM_STR(SUM, BUF_SUM);
		BUF_SUM = "";
	}

	if (is_a_negativ || is_b_negativ)
	{
		SUM = "-" + SUM;
	}

	BUF_SUM.clear();
	a_buff.clear();
	b_buff.clear();

	return SUM;
}


bool  IS_ZERO(string a) {

	int zero = 0; ////проверка на 0

	for (int i = 0; i < a.size(); i++)
	{
		int num = a[i] - '0';
		zero += num;
	}

	if (zero == 0)
	{
		return true;
	}
	else {
		return false;
	}
}


string factorial(unsigned int n)
{
	if (n == 0)
	{
		return "1";
	}
	else
	{
		string RES = "1";
	
		for (int i = 2; i <= n; i++)
		{
			RES = MUL(RES,to_string(i));
			//cout << 1000000 / n * i << "       i = " << i << endl ;
		}

		return RES;
	}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////

string POW(string a, int pow)
{

	if (pow <= 0)
	{
		return "1";
	}
	string res = a;
	
	for (int i = 1; i <= pow; i ++)
	{
		res = MUL(res, to_string(i));
	}
	return res;
}

/////////////////////////////////////////////////////////////////////////////////


deque<unsigned int> BIG_SUM(deque<unsigned int> a, deque<unsigned int> b)
{
	signed long long BASE = 4294967296;
	deque<unsigned int> A = a;
	deque<unsigned int> B = b;
	deque<unsigned int> S;
	int E = 0;


	for (auto i = 0; i < std::max(B.size(), A.size()); ++i)
	{
		auto aa = i >= A.size() ? 0 : A[i];
		auto bb = i >= B.size() ? 0 : B[i];
		uint64_t r = 0ULL + aa + bb + E;
		S.push_back(r % BASE);
		E = r / BASE;
	}
	if (E != 0)
	{
		S.push_back(E);
	}

	A.clear();
	B.clear();
	return S;


}

/////////////////////////////////////////////////////////////////////////////

deque<unsigned int> BIG_SUM(int a, int b)
{
	signed long long BASE = 4294967296;
	deque<unsigned int> A;
	deque<unsigned int> B;
	deque<unsigned int> S;
	int E = 0;


	while (a > 0)
	{
		A.push_back(a % BASE);
		a /= BASE;
	}

	while (b > 0)
	{
		B.push_back(b % BASE);
		b /= BASE;
	}


	for (auto i = 0; i < std::max(B.size(), A.size()); ++i)
	{
		auto aa = i >= A.size() ? 0 : A[i];
		auto bb = i >= B.size() ? 0 : B[i];
		uint64_t r = 0ULL + aa + bb + E;
		S.push_back(r % BASE);
		E = r / BASE;
	}
	if (E != 0)
	{
		S.push_back(E);
	}

	//deque<int> rez;
	A.clear();
	B.clear();
	return S;
 
	
}

/////////////////////////////////////////////////////////////////////

string TO_STRING_FROM_BIG(deque<unsigned int> a)
{
	string BASE = "4294967296";
	string REZ = "0";
	int size = a.size();
	

	for (int i = 0; i < a.size(); i++)
	{
		int pow = i;
		string ai = to_string(a[i]);
		string b_p = POW(BASE, pow);
		string buf = MUL(ai, b_p);
		REZ = SUM_STR_SIG(REZ, buf);
	}
	return REZ;
}
////////////////////////////////////////////////////////////////////


deque<unsigned int> BIG_MUL(deque<unsigned int> x, deque<unsigned int> y)
{

	deque<unsigned int> result;
	signed long long BASE = 4294967296;

	for (auto i = 0u; i < y.size(); ++i)
	{
		unsigned carrier = 0;
		deque<unsigned int> k;


		for (auto j = 0u; j < i; ++j)
			k.push_back(0);
		for (auto j = 0u; j < x.size(); ++j)
		{
			auto xx = x[j];
			auto yy = y[i];
			uint64_t r = 1ULL * xx * yy + carrier;
			k.push_back(r % BASE);
			carrier = r / BASE;
		}
		if (carrier != 0)
			k.push_back(carrier);
		result = BIG_SUM(result, k);
	}
	return result;
}


deque<unsigned int> TO_INT_DEQUE(int a)
{
	deque<unsigned int> A;
	signed long long BASE = 4294967296;

	while (a > 0)
	{
		A.push_back(a % BASE);
		a /= BASE;
	}
	return A;
}


int main()
{

	deque<unsigned int> r = TO_INT_DEQUE(1);



	for (int i = 1; i <= 123456; i++)
	{
		r = BIG_MUL(r, TO_INT_DEQUE(i));
		
		cout << "i = " << i << endl;
	}

	cout << TO_STRING_FROM_BIG(r);

	
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
