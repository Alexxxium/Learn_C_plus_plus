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
	// ���������� ���������� ����� ��� �������� ������� � ��������� �����
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
	std::shared_ptr<Item> m_ptr;				// ��� sas4()
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

	Auto_ptr(const Auto_ptr&);						// ����������� �����������
	Auto_ptr& operator=(const Auto_ptr&);			// ���������� ��������� ������������


	Auto_ptr(Auto_ptr &&copy) noexcept :			// ����������� �����������, ������� �������� ����� ������������� copy.pointer -> pointer
		pointer(copy.pointer)						//
	{												//
		copy.pointer = nullptr;						// ����������� ������������������ ��������� �� ������
	}												//
													//
	Auto_ptr& operator=(Auto_ptr&&) noexcept;		// o������� ������������ ������������, ������� �������� ����� ������������� ��. inline


	T& operator*() const { return *pointer; }		// ���������� ��������� �������������
	T* operator->() const { return pointer; }		// ���������� ��������� ������ ����� ����� ���������

	~Auto_ptr() { delete pointer; }
};

Auto_ptr<Item> generatItem();						// ������� �������� Auto_ptr

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