#pragma once

#include <iostream>
#include <vector>
#include <exception>

#include <chrono>
#include <utility>
#include <memory>

class Timer
{
private:
	// Используем псевдонимы типов для удобного доступа к вложенным типам
	using clock_t = std::chrono::high_resolution_clock;
	using second_t = std::chrono::duration<double, std::ratio<1> >;

	std::chrono::time_point<clock_t> m_beg;

public:
	Timer(): m_beg(clock_t::now())
	{
	}

	void reset()
	{
		m_beg = clock_t::now();
	}

	double elapsed() const
	{
		return std::chrono::duration_cast<second_t>(clock_t::now() - m_beg).count();
	}
};

class Item {
public:
	std::shared_ptr<Item> m_ptr;				// для sas4()
	std::weak_ptr<Item> m_ptr2;

	Item() { std::cout << "construct!\n"; }
	~Item() { std::cout << "destruct!\n"; }
};

template <class T>
class Auto_ptr {
private:
	T *pointer;

public:
	Auto_ptr(T *ptr = nullptr): pointer(ptr) {}

	Auto_ptr(const Auto_ptr&);						// конструктор копирования
	Auto_ptr& operator=(const Auto_ptr&);			// перегрузка оператора присваивания


	Auto_ptr(Auto_ptr &&copy) noexcept :			// конструктор перемещения, который передает право собственности copy.pointer -> pointer
		pointer(copy.pointer)						//
	{												//
		copy.pointer = nullptr;						// ликвидируем перераспределенный указатель на ресурс
	}												//
													//
	Auto_ptr& operator=(Auto_ptr&&) noexcept;		// oператор присваивания перемещением, который передает право собственности см. inline


	T& operator*() const { return *pointer; }		// перегрузка оператора разыменования
	T* operator->() const { return pointer; }		// перегрузка оператора выбора члена через указатель

	~Auto_ptr() { delete pointer; }
};

Auto_ptr<Item> generatItem();						// функция создания Auto_ptr

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Fraction {
private:
	int numenate;
	int denuminate;

public:
	Fraction(int, int);
	Fraction(): numenate(0), denuminate(1) {}
	friend std::ostream& operator<<(std::ostream&, const Fraction&);
};

#include "Templ.inl"