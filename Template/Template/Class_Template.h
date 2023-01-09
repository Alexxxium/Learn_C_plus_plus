#pragma once
#include <iostream>
#include "assert.h"
#include <initializer_list> // дл€ std::initializer_list

template <typename T> T sum(T x, T y) {
	return x + y;
}

template <typename T>
const T& big_obj_sum(const T &x, const T &y) {
	return x + y;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>
class Darray {
private:
	T *data;
	int size;

public:
	Darray(int lenght) {
		assert(lenght > 0 && "lenght error!\n");
		data = new T[lenght];
		size = lenght;
	}
	~Darray() {
		delete[] data;
		size = 0;
	}
	T& operator[](const int index) {
		assert(index > 0 && index < size && "index error!\n");
		return data[index];
	}
	
	void getlenght();
	void set();
	void erase();
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, int lenght>
class Sarray {
private:
	T array[lenght];

public:
	//Sarray(){ /* обошлись без только конструктером по умол€анию */ }
	T& operator[](const int index) {
		assert(index >= 0 && index < lenght && "index error!\n");
		return array[index];
	}

	void getlenght();
	void set();
	void erase();
};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class T>
class Repositoriy {
private:
	T m_value;

public:
	Repositoriy(T value) : m_value(value) {}
	~Repositoriy() {}

	void print() {
		std::cout << m_value << '\n';
	}
};

template <class T>
class Trais8 {
private:
	T m_array[8];

public:
	void set(const int index, const T value) {
		m_array[index] = value;
	}
	const T& get(const int index) {
		return m_array[index];
	}
};


template <typename T, int size>				// частична€ специализаци€ функции
void print(Sarray<T, size> &array) {		// благодар€ non-type параметру
	for (int i = 0; i < size; ++i)
		std::cout << array[i] << ' ';
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T, int size>				// size - non type параметр
class Base_static_array {
protected:
	T array[size];
	
public:
	
	T& operator[](const int index) {
		return array[index];
	}

	virtual void set(const int index, const T value) {
		array[index] = value;
	}
	virtual void print() {
		for (int i = 0; i < size; ++i)
			std::cout << array[i] << ' ';
	}
};

template <class T, int size>
class static_array: public Base_static_array<T, size> {		// наследуем базовый класс
	
	// наследуем весь функционал родительского класса!

};

template <int size>
class static_array<char, size>: public Base_static_array<char, size> {		// дочерний класс дл€ частичной специализации шаблона класса (экземпл€р char)
	void print() override {
		for (int i = 0; i < size; ++i)
			std::cout << this->array[i];		// ¬ажно!, разумного объ€снени€ не найдено
	}
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class T>

// дл€ работы с не указател€ми
class Repos {
private:

	T m_value;

public:

	Repos(const T value): m_value(value) {}

	~Repos() {}

	void print() {
		std::cout << m_value << '\n';
	}
};

template <typename T>

class Repos<T*> {

private:

	T *m_value;

public:

	Repos(T *value): m_value(new T(*value)) {}

	~Repos() { delete m_value; }

	void print() {
		std::cout << *m_value << '\n';
	}
};

template<>
class Repos<char*> {

private:

	char *m_value;

public:

	Repos(char *value): m_value(value) {}

	~Repos() { delete[] m_value; }

	void print() {
		std::cout << m_value << '\n';
	}
};

////////////// —татический массив ////////////////////

template<typename T, int size = 0>
class Array {
private:
	T m_data[size];

public:
	Array() {}
	Array(const std::initializer_list<T> &list);
	
	int lenght() { return size; }
	T& operator[](const int index) { return m_data[index]; }

	void out() {
		for (int i = 0; i < size; ++i)
			std::cout << m_data[i] << ' ';
	}
};

#include "Relese.inl"