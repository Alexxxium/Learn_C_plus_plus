#pragma once

#include <iostream>
#include <string>
#include <cassert>


#include <initializer_list>
#include <exception>
#include <stdexcept>

void one();
void two();
void three();
void last();

void doSomething1() throw();
void doSomething2() throw(char);
void doSomething3() throw(...);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class ArrayException: public std::exception {					// наследуем класс-исключение из стандартной библиотеки С++
private:
	std::string excep_name;

public:
	ArrayException(std::string &error): excep_name(error) {}
	ArrayException(const char *error):  excep_name(error) {}
	const char* get_error()  { return excep_name.c_str(); }
																
	const char* what() const noexcept override					// переопределяем виртуальный метод what()
	{															// спецификатор noexсept - обещание, видимо программиста, что функция не будет выбрасывать исключения
		return excep_name.c_str(); 
	}
};

template <class T, int size>
class Array {
private:
	T array[size];

public:
	Array(const std::initializer_list<T>&); 
	Array(const T&);
	T& operator[](const int);
};

class Parent {
public:
	Parent() {}

	virtual void print() { std::cout << "Parent!\n"; }		// для sas4()
};
class Child: public Parent {
public:
	Child()  {}
	void print() override { std::cout << "Child!\n"; }		// для sas4()
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::string& except_funk();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class A {
private:
	int x;

public:
	A(int a): x(a) {
		if (a <= 0) throw float();
	}
};

class B: public A {
 
public:
	B(int b) try: A(b){}		// функциональный try-блок
	catch (...)					// блок catch повторно, неявно выбрасывает точно такое же исключение
	{
		std::cerr << "Construction of A failed\n";
	}
};


#include "Template.inl"