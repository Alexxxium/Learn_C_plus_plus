﻿
#include "Header.h"

void sas1() {

	/*
	****	try, throw, catch - пытаться (генерировать), выбрасывать, ловить:
	*	В блоке try мы генерируем исключение с помощью оператора throw, который его и выбрасывает, а опереатор catch его ловит и обрабатывает
	* 
	****	Если исключение поймано оператором cath, то оно считается обработанным, даже если блок catch пуст
	*/



	try									// блок try
	{
		std::cout << "Block try!\n";

	}
	catch(...){}						// соответствубщи(й/е) блоки catch



	try									// следующая связь блоков try catch
	{
		const char* cstr("sas");
		std::string str("sys");
									// выбрасываем исключения определенного типа:
		throw - 1;					// типа int	(в данном случае обработка исключения сразу уйдет в блок cath, пропустив следующие строки блока try)
		throw 'a';					// char
		throw str;					// std::string
		throw cstr;					// const char* и др.

		// Следующий код не скомпилируется, т.к. мы перейдем к оператору catch
		// Утечка памяти

		int *ptr(new int);
		delete ptr;

	}

	catch(int err) {									// параметр обработки int
		std::cout << "Exeption type is int\n";
	}
	catch (char) {										// char, переменная по значению не указана
		std::cout << "Exaption type is char\n";
	}
	catch (std::string &str) {							// передаем по ссылке
		std::cout << "Exaption: " << str << '\n';
	}
	catch (...) {										// элипсис для обработки пропущенных исключений (эдепсис принимает любые параметры)
		std::cout << "Lost exeption: std:string\n";
	}
}

void sas2() {

	/*
	****	Раскручивание стека - действие, которое выполняет компилятор при поиске обработчика исключения в вышестоящих, вызывающих функциях.
	*	Поиск обработчиков catch игнорирует выполнение дальнейшего тела функции при возврате в caller!
	*	Раскручивание происходит до тех пор, пока не найдется подходящий обработчик, если исключение не удалось обработать, то программа сбоится:
	*	вызывает консольную ошибку или massagebox
	* 
	****	Спецификация исключений - не несет никаких реальных изменений, это лишь визульное определение функции,
	*	которая будет/не будет генерировать исключения определенного/не определенной типа данных
	*/

	// Разкручивание стека
	
	std::cout << "Start main\n";	// сообщение (1)
	try
	{
		one();	// заходим в функцию one() см. Funck.cpp
	}
	catch (int)	// исключение уже обработано!
	{
		std::cerr << "main caught int exception\n";
	}
	std::cout << "End main\n";	// сообщение (9)

	// Спецификация исключений

	try
	{
		doSomething1();
		doSomething2();		// при исключении мы покидаем блок try!
		doSomething3();
	}
	catch (double) { std::cerr << "\nExeption!\n"; }
	
}

void sas3() {
	/*
	****	Исключния в наследовании. Выбросив исключение типа данных дочернего объекта, стоит учитывать,
	*	что обработчик исключения родительского класса так же может обработать и свой дочерний класс, из-за типа отношений
	*
	****	Начиная с C++14, существует больше 20 классов - исключений, которые могут быть выброшены, а в C++17 их еще больше.
	* Хорошей новостью является то, что все эти классы - исключения являются дочерними классу std::exception.
	*
	****	Интерфейсный класс std::exception - это небольшой интерфейсный класс,
	*	который используется в качестве родительского класса для любого исключения, которое выбрасывается в Стандартной библиотеке C++.
	*/
	

	Array<int, 3> arr1{ 1, 3, 5};
	try		// намеренно создаем исключения
	{
		arr1[12] = 0;											// неправильный индекс
		Array<std::string, 2>  arr2{ "sss", "sas", "more"};		// превышение списка инициализации
	}
	catch (ArrayException &exception) {	// обрабатываем их с помощью класса-исключения
		std::cout << "An array exception occurred(" << exception.get_error() << ")\n";
	}


	// Исключения и наследование

	try
	{
		throw Child();
	}
	catch (Parent&) {
		std::cerr << "\ncaught Parent!\n";		// подходит, т.к. child является parent
	}
	catch (Child&) {
		std::cerr << "\ncaught Child\n";
	}
	

	// Интерфейсный класс std::exception

	try
	{
		std::string str;
		str.resize(-2);													// генерируем исключение
	}
	catch (std::bad_alloc&) {											// класс bad_alloc дочерний классу exception, применяем catch только для исключения типа bad_alloc
		std::cerr << "Out of memory!";
	}
	catch (std::exception &excep) {										// класс exception, принимает все дочерние типы исключений, сам класс интерфейсный
		std::cerr << "Standard exception: " << excep.what() << '\n';	// виртуальный метод what() возвращает строку c-style с описанием ошибки
	}

	try { throw std::runtime_error("Exemple error name!"); }			// генерируем исключение с собственным именем
	catch (std::exception &excep) {
		std::cerr << "Standard exception: " << excep.what() << '\n';
	}

	Array <float, 10> flt{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };				// класс-исключение ArrayExaption наследует std::exception
	try{ flt[-1]; }														// исключение из-за некорректного индекса
	catch (std::exception &excep) {
		std::cerr << "Array exception:\t" << excep.what() << '\n';		// благодаря полиморфизму, мы переопределили родительский метод
	}

}

void sas4() {

	/*
	****	Повторная генерация исключений - в блоке catch можно выбрасывать исключения любого типа данных.
	*	Это актуально в случае, если нам необходимо обработать это исключение в другом месте, например в caller-е
	* 
	****	Функциональный try-блок - другая версия try, которая пишется после сигнатуры функции, после скобок
	*	Имеет смысл объявлять такой блок после конструктора, до инициализации членов, а соответствующий такому try-блоку блок catch
	*	неявно сгенерирует точно такое же исключение для обработке вне тела конструктора
	*/

	try
	{
		except_funk();					// функция сгенерировала исключение, обработала и выбросила копию/клон см. функцию
	}
	catch (std::exception &except) {
		std::cout << "Funk Exception:\t" << except.what() << '\n';
	}

	// Пояснение:

	try
	{
		try
		{
			throw Child();	// исключение дочернего типа
		}
		catch (Parent &p) {	// исключение может обработать родитель
			std::cout << "Exception type:\t";
			p.print();

			throw p;		// копия!   копирование исключения! + обрезка объкта!				
			throw;			//  клон!   выбрасываеся точно такое же исключение без лишних затрат и обрезок!
		}
	}
	catch (Parent &p) {		
		std::cout << "Exception type:\t";
		p.print();			// если копия, то Parent (обрезка объекта)
							// если клон, то Child (метод виртуальный)
	}

	try 
	{
		B b(0);				// генерируется исключение в конструктор
	}
	catch (float) {
		std::cout << "Catch!\n";
	}
}




int main()
{
	//sas1();
	//sas2();
	//sas3();
	sas4();

	return 0;
}


