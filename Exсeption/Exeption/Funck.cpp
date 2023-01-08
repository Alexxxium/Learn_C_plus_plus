#include "Header.h"

void one() {
	std::cout << "Start One!\n";		// ������� ��������� (2)
	try
	{
		two();		// ���� � ������� two() /�������� ���� ->/ �� two()->one(), ���� ���� catch(int)
	}
	catch (int) {					// ��� ��!
		std::cerr << "One\n";		// (7)
	}
	catch (double) {
		std::cerr << "One";
	}
	std::cout << "End One!\n";		// (8) ���������� ������� �������������!
}
void two() {
	std::cout << "Stat Two!\n";		// (3)
	try
	{
		three();		// ���� � ������� three() // �� three() -> two(), ��� ����� catch(int) -> one()
	}
	catch (double) {
		std::cerr << "Two";
	}
	std::cout << "End Two!\n";
}
void three() {
	std::cout << "Start Thre!\n";	// (4)
	last();							// ���� � ������� last() // �� last()->three(), ����� catch ��� -> two() 
	std::cout << "End Three!\n";
}
void last() {
	std::cout << "Start Last\n";	// (5)
	std::cout << "last throwing int exception\n";	// (6)
	throw - 1;										// ����������� ���������� -> ������� � three() ������ ���� cath
	std::cout << "End Last\n";
}


void doSomething1() {		// ������� �� ������ ����������� ����������, ���� �����	
	throw 1.5;
}
void doSomething2() throw(char) {	// ��������� ��������� ���������� ���� char - ������ ������ �� ������� �����������
	//throw 1;
	throw 3.14;		// ����� ������������� ���������� ������ ����
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
		str.resize(-3);					// ��������� ����������
		return str;						// ���������� ������������ ��������
	}
	catch (std::exception& except) {	// �������� � ����������
		throw except;					// �������� ���������� ����� ���������� + ������� �������
		throw;							// �������� ���������� ����� ����� �� ����������, � ������� ����� ����������� caller
	}
}
