﻿#include "Class_Template.h"


void sas1() {

	/*
	****	Шаблон функции -  это функции, которые служат образцом для создания других подобных функций. 
	*	Главная идея — создание функций без указания точного типа(ов) некоторых или всех переменных. 
	*	Для этого мы определяем функцию, указывая тип параметра шаблона, который используется вместо любого типа данных. 
	*	После того, как мы создали функцию с типом параметра шаблона, мы фактически создали «трафарет функции».
	* 
	****	Экземпляр функции - функция, созданная по шаблону. после вызова шаблонной функции, компилятор автоматически подставляет в нее
	*	соответствующие параметры и создает эту функцию. С помощью экземпляра можно переопределить тело функции, создав экземпляр явно!
	*/

	std::cout <<						// вызов экземпларов функции
		sum(1, 4) << '\n' <<			// экземпляр int(int, int)
		sum('s', 'z') << '\n' <<		// char(char, char)
		sum(3.14, 8.31) << '\n' <<		// double(double, double)
		big_obj_sum(1, 2) << '\n';		// const int&(const int&, const int&)

}

void sas2() {
	
	/*
	****	Шаблон класса создается идентично шаблону функции, как и его явные и неявные экземпляры с соблюдением самой структуры класса
	* 
	****	Параметр non-type в шаблоне — это специальный параметр шаблона, который заменяется не типом данных, а конкретным значением. Этим значением может быть:
	*/

	Darray<int> arrayint(10);
	Darray<double> arraydouble(5);

	Sarray<int, 5> sarrayint{};
	Sarray<double, 7> sarraydoub{};
	
}

void sas3() {

	/*
	****	Ключевое слово template сообщает компилятору, что это шаблон, а пустые угловые скобки означают, что нет никаких параметров.
	*	А параметров нет из-за того, что мы заменяем единственный параметр шаблона (T, который отвечает за тип данных) конкретным типом данных.
	* 
	****	Специализация шаблона класса (или «явная специализация шаблона класса») позволяет специализировать шаблон класса 
	*	для работы с определенным типом данных (или сразу с несколькими типами данных, если есть несколько параметров шаблона).
	*
	*	Специализация шаблона класса рассматривается компилятором как полностью отдельный и независимый класс, 
	*	хоть и выделяется как обычный шаблон класса. Это означает, что мы можем изменить в классе всё что угодно, включая его реализацию/методы/спецификаторы доступа и т.д.
	* 
	****	Специализация шаблона функции почти аналогична, разве что если это метод, то еобходимо указывать область видимости и тип экземпляра
	* 
	****	Частичная спецификация
	*/

	Repositoriy<int> vl(3);
	Repositoriy<double> doub(3.14);
	Repositoriy<const char *> cr("hellow");		// константный указатель на литерал строки
	
	char *str = new char[40];
	std::cin >> str;

	Repositoriy<char *> string(str);

	vl.print();
	doub.print();
	cr.print();
	string.print();
	

	Trais8<int> aryint{};						// создается по шаблону
	Trais8<bool> arybool{};						// создается по принципу явной специализации шаблона класса (экономим память!)


	
}	


void sas4() {



	Sarray<int, 5> mass{};
	Sarray<char, 5> st{};
	st[0] = 'h';
	st[1] = 'e';
	st[2] = 'l';
	st[3] = 'l';
	st[4] = 'o';
	print(st);
}

void sas5() {

	/*
	****
	*/

	char *sas(new char[4] {"sas"});
	int a(6);

	Repos<char*> str(sas);			
	Repos<int*> intenger(&a);
	Repos<double> pi(3.14);

	str.print();
	intenger.print();
	pi.print();

	Array <int, 5> ar{1, 2, 3, 4, 5};
	ar[3] = 0;
	ar.out();

}

int main()
{
	//sas1();
	//sas2();
	//sas3();
	//sas4();
	sas5();
}

