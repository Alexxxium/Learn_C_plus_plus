#include "Class.h"
#include <cassert>			// список инициализации


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Array::Array(int lenght) : m_size(lenght) {

	assert(lenght >= 0 && "Error size!\n");

	if (lenght > 0) array = new int[lenght];
	else array = nullptr;
}

Array::Array(const std::initializer_list<int>& list) : Array(list.size()) {

	int indx = 0;

	for (const auto& i : list) {
		array[indx] = i;
		++indx;
	}
}

Array::Array(const Array& copy) : m_size(copy.m_size) {
	std::cout << "Copy!\n";
	if (copy.array) {
		array = new int[copy.m_size];
		for (int i = 0; i < m_size; ++i)
			array[i] = copy.array[i];
	}
	else
		array = nullptr;
}


Array::~Array() {
	delete[] array;
	array = nullptr;
	m_size = 0;
}


int& Array::operator[](int index) {

	assert(index >= 0 && index < m_size && "Error index!\n");

	return array[index];
}

Array& Array::operator = (const Array& copy) {

	if (this == &copy) return *this;

	m_size = copy.m_size;
	delete[] array;

	if (copy.array) {

		array = new int[copy.m_size];
		for (int i = 0; i < m_size; ++i)
			array[i] = copy.array[i];
	}
	else
		array = nullptr;

	return *this;
}

Array& Array::operator = (const std::initializer_list<int>& list) {
	
	m_size = list.size();
	delete[] array;

	if (list.size()) {

		array = new int[list.size()];
		int indx = 0;
		for (const auto& i : list) {
			array[indx] = i;
			++indx;
		}
	}
	else array = nullptr;
	return *this;
}


void Array::erase() {
	delete[] array;
	array = nullptr;
	m_size = 0;
}

void Array::out_array(int str) {

	if (str) {
		for (int i = 0; i < m_size; ++i) {
			if (i % str == 0) std::cout << '\n';
			std::cout << array[i] << '\t';
		}
	}
	else
		for (int i = 0; i < m_size; ++i)
			std::cout << array[i] << '\t';
}

void Array::resize(int new_size) {

	assert(new_size >= 0 && "Eroor index!\n");

	if (!new_size) { erase(); return; }

	int need_size = (new_size > m_size) ? m_size : new_size;
	int* new_array = new int[need_size];

	for (int i = 0; i < need_size; ++i)
		new_array[i] = array[i];
	
	delete[] array;
	array = new_array;
	m_size = new_size;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 
void report(Animal &animal) {
	std::cout << animal.get_name() << '\t' << animal.speak() << '\n';
}
void report(Animal *animal) {
	std::cout << animal->get_name() << '\t' << animal->speak() << '\n';
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const char* Planet::x_ray_fon() {
	return "more 1000 rgns!";
}

