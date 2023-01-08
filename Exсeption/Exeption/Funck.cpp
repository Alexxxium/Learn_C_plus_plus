#include "Header.h"

void one() {
	std::cout << "Start One!\n";		// выводим сообщение (2)
	try
	{
		two();		// идем в функцию two() /обратный путь ->/ из two()->one(), ищем блок catch(int)
	}
	catch (int) {					// вот он!
		std::cerr << "One\n";		// (7)
	}
	catch (double) {
		std::cerr << "One";
	}
	std::cout << "End One!\n";		// (8) выполнение функции проддолжается!
}
void two() {
	std::cout << "Stat Two!\n";		// (3)
	try
	{
		three();		// идем в функцию three() // из three() -> two(), нет блока catch(int) -> one()
	}
	catch (double) {
		std::cerr << "Two";
	}
	std::cout << "End Two!\n";
}
void three() {
	std::cout << "Start Thre!\n";	// (4)
	last();							// идем в функцию last() // из last()->three(), блока catch нет -> two() 
	std::cout << "End Three!\n";
}
void last() {
	std::cout << "Start Last\n";	// (5)
	std::cout << "last throwing int exception\n";	// (6)
	throw - 1;										// выбрасываем исключенме -> обратно в three() искать блок cath
	std::cout << "End Last\n";
}


void doSomething1() {		// функция не должна выбрасывать исключения, хотя может	
	throw 1.5;
}
void doSomething2() throw(char) {	// ОЖИДАЕНИЕ генерации исключения типа char - похоже больше на кодовый комментраий
	//throw 1;
	throw 3.14;		// можно сгенерировать исключение любого типа
}
void doSomething3() {
	//throw 1;
	throw 1.4;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string& except_funk() {
	try
	{
		std::string str("sas");
		str.resize(-3);					// гнерируем исключение
		return str;						// игнорируем возвращаемое значение
	}
	catch (std::exception& except) {	// попадаем в обработчик
		throw except;					// повторно генерируем копию исключения + образка объекта
		throw;							// повторно генерируем точно такое же исключение, с которым будет разбираться caller
	}
}
