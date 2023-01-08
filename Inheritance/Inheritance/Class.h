#pragma once

#include <iostream>
#include <vector>
#include <functional>


class Array {

private:

	int m_size;
	int* array;
	void erase();

public:

	Array() : m_size(0), array(nullptr) {};
	Array(int);
	explicit Array(const std::initializer_list<int>& list);
	Array(const Array& copy);

	~Array();
	
	int& operator[](int);
	Array& operator =(const Array& copy);
	Array& operator =(const std::initializer_list<int>& list);
	

	void resize(int);
	int size() const { return m_size; }
	
	
	void out_array(int = 0);
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Parent_Parent {

private:		// доступ есть только у других членов класса и дружественных функций (прямое обращение к членам запрещено!)

	int p_p_value;
	int* date;

protected:		// доступ есть у других членов класса, дружественных функций и дочерних классов (прямое обращение к членам запрещено!)

	double p_p_dbvl = 9.89;

public:			// доступ открыт у всех объектов (разрешено прямое обращение)

	Parent_Parent(int p_p_vl): 
		p_p_value(p_p_vl),
		date(new int)
	{
		std::cout <<
			"Construct Parenr_Parent!\tvalue = "
			<< p_p_value << '\n';
	}

	~Parent_Parent() {
		delete date;
		std::cout << "Desstruct Parenr_Parent!\n";
	}

	int getPP() { return p_p_value; }

	void out() {
		std::cout << p_p_value << '\n';
	}
};

class Parent : public Parent_Parent{
private:

	int p_value;
	int *date;

public:

	Parent(int p_vl, int p_p_vl): 
		p_value(p_vl), 
		date(new int),
		Parent_Parent(p_p_vl) 
	{
		std::cout <<
			"Construct Parent!\t\tvalue = "
			<< p_value << '\n';
	}

	~Parent() {
		delete date;
		std::cout << "Destruct Parent!\n";
	}

	int getP() { return p_value; }

	void out() {
		Parent_Parent::out();							// вызов родительского метода
		std::cout << p_value << '\n';
	}
};

class Child : public Parent{
private:

	int c_value;
	int *date;

public:

	//Child(){}											// для родительских классов отсутствует конструктор по умолчанию

	Child(int c_vl, int p_vl, int p_p_vl): 
		c_value(c_vl),
		date(new int),
		Parent(p_vl, p_p_vl)							// используем делегирование конструкторов 
	{
														// операция присваивания! За инициализацию отвечает соответствующий конструктор
		p_p_dbvl = 10;									// protected: мы имеем доступ к этому члену из дочернего класса

		std::cout << 
			"Construct Child!\t\tvalue = "
			<< c_value << '\n';
	}

	~Child() {
		delete date;
		std::cout << "Destruct Child!\n";
	}

	int getC() { return c_value; }

	void out() {
		Parent::out();									// вызов родительского метода
		std::cout << c_value << '\n' <<
			"p_p_dbvl = " << p_p_dbvl;
	}
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Parent_t {
protected:
	int group;

private:
	int people;

public:
	int now_date;

	Parent_t(int numb, int count, int date) :
		group(numb), people(count), now_date(date)
	{
		std::cout << "Parent construct!\n";
	}

	void out() {
		std::cout << '\n'<<
			group << '\n' <<
			people << '\n' <<
			now_date << '\n';
	}
};
								
class Public_child : public Parent_t {			// открытое наследование
private:
	std::string name;

public:

	Public_child(std::string nm, int grp, int ple, int dt) :
		name(nm), Parent_t(grp, ple, dt) 
	{
		std::cout << "Child construct!\n";
	}
	void set(int group, int date) {
		this->group = group;					// protected: есть доступ					
		//people = 4;							// private: недоступен
		now_date = date;						// public: остался public
	}
};

class Private_child : Parent_t {				// закрытое наследование (по умолчанию тип наследования private)
private:
	std::string name;

public:

	Private_child(std::string nm, int grp, int ple, int dt) :
		name(nm), Parent_t(grp, ple, dt)
	{
		std::cout << "Child construct!\n";
	}
	void set(int group, int date) {
		this->group = group;					// protected: private
		//people = 4;							// private: недоступен
		now_date = date;						// public: private
	}
};

class Protect_child : protected Parent_t {		// защищенное наследование
private:
	std::string name;

public:

	Protect_child(std::string nm, int grp, int ple, int dt) :
		name(nm), Parent_t(grp, ple, dt)
	{
		std::cout << "Child construct!\n";
	}
	void set(int group, int date) {
		group = group;							// protected: protected
		//people = 4;							// private: недоступен
		now_date = date;						// public: protected
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Light_operation {
protected:
	const int vl1, vl2;
public:
	Light_operation(int x, int y) : vl1(x), vl2(y){}

	int sum() const { return vl1 + vl2; }
	int sub() const { return vl1 - vl2; }
	double del() const { return vl1 / vl2; }

protected:
	int mul() const { return vl1 * vl2; }
	

};

class Binari_operation : Light_operation {
public:

	Binari_operation(int x, int y) : Light_operation(x, y) {}

	int sum() const { return vl1 ^ vl2; };				// переопределение родительских методов
	int sub() const { return ~(vl1 | vl2); }			// на самом деле мы не даем компилятору выбрать родительский метод

	using Light_operation::mul;							// делаем открытый доступ родительскому методу (в дочернем классе читакется, как public)

	int del() const = delete;							// запрещаем использование метода
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class A			{};
class B: A		{};
class C: A		{};
class D: B, C	{};			// множественное наследование (ситуация "алмаза смерти")

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Animal {
private:
	const char *name;

protected:
	Animal(const char *&nm): name(nm){}

public:
	const char *get_name() { return name; }
	const char *speak() { return "Animal"; }

	////////////////////////////////////////// <- виртуальная функция

	virtual void get_info() { std::cout << "Not Info!\n"; }

	//////////////////////////////////////////
};

class Cat : public Animal {
private:
	const char *name;

public:
	Cat(const char *nm): name(nm), Animal(nm){}
	const char *speak() { return "Muoy!"; }

	////////////////////////////////////////// <- виртуальная функция
	virtual void get_info() {
		std::cout <<
			"Name:\t" << name << '\n' <<			// строка c-style!!!
			"Talk:\t" << speak() << '\n';
	}
	//////////////////////////////////////////
};

class Dog : public Animal {
private:
	const char *name;
public:
	Dog(const char *nm) : name(nm), Animal(nm) {};
	const char *speak() { return "Woof!"; }

	////////////////////////////////////////// <- виртуальная функция
	virtual void get_info() {
		std::cout <<
			"Name:\t" << name << '\n' <<			// строка c-style;
			"Talk:\t" << speak() << '\n';
	}
	//////////////////////////////////////////
};

void report(Animal &);
void report(Animal *);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*
*	Модификатор override после метода означает, что метод является переопределением родительского при той же сходимости сигнатуры, если нет, то коспидятор вызывет ошибку
*	Модификатор final после метода (посде override, если есть) обозначает, что метод нельзя переопределить!
*	final после имени класса запрещает создавать дочерние классы.
* 
*	Есть один случай, когда тип возврата переопределения может не совпадать с типом возврата виртуальной функции родительского класса,
*	но при этом оставаться переопределением. Если типом возврата виртуальной функции является указатель или ссылка на класс, 
*	то переопределения могут возвращать указатель или ссылку на свой собственный класс 
*	(т.е. вместо родительского класса указывать на дочерний класс). Это называется ковариантным типом возврата.
* 
*	Виртуальные деструкторы также нужны, если указатель или ссылка ссылаются на родительский объект через дочерний, иначе, при уничтожении объекта родительского класса,
*	деструкторы всех дочерних классов будут проигнорированны
*/

class GPrnt {

public:
	int *a = new int(12);

	virtual const char* wrt_cons1(int x) { return "GPrnt!"; }
	virtual const char* wrt_cons2(int x) { return "GPrnt!"; }
	virtual const char* wrt_cons3(int x) { return "GPrnt!"; }

	virtual GPrnt* get_this() { 
		std::cout << "GrandParent\n";
		return this;
	}

	virtual ~GPrnt() { delete a; }			// виртуальный деструктор; необходим, т.к. указатель на этот класс не видит дочерние функции (может произойти утечка памяти)

};

class Prnt /* final */ : public GPrnt {		// final - запрещает создание дочерних класов

public:
	int *b = new int(13);

	// разные сигнатуры!
	virtual const char* wrt_cons1(short int x) /* override */ { return "Prnt!"; }	// override вызовет ошибку, т.к. метод не является переопределением (другя сигнатура)
	virtual const char* wrt_cons2(int x) const /* override */ { return "Prnt!"; }	// аналогично и с ключевым словом const
	virtual const char* wrt_cons3(int x) override /* final */ { return "Prnt!"; }	// доступ к переопределению в дочернем классе закрыт (а так все ок)

	virtual Prnt* get_this() override {		// компилятор не ругается, т.к. возвращаемый объект наследует родительский!
		std::cout << "Parent\n";
		return this;
	}

	virtual ~Prnt() { delete b; }			// виртуальный деструктор; необходим, т.к. указатель на этот класс не видит дочерние функции (может произойти утечка памяти)
};

class Chld : public Prnt{

public:
	int *c = new int(15);

    const char* wrt_cons3(int x) override { return "Chld!"; }

	Chld* get_this() override {				// компилятор не ругается, т.к. возвращаемый объект наследует родительский!
		std::cout << "Child\n";
		return this; 
	}

	~Chld() { delete c; }

};

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class Batya {
public:
	
	virtual void func1() {};			// Virtual table:		Batya::func1	Batya::func2
	virtual void func2() {};
};

class C1: public Batya {
public:
	virtual void func1() {};			// Virtual table:		C1::func1		Batya::func2
};

class C2: public Batya {
public:
	virtual void func2() {};			// Virtual table:		Batya::func1	C2::func2
};

class Planet {

protected:
	std::string name;
	std::string location;

	Planet(std::string &nm, std::string &loc):
	name(nm), location(loc)	
	{
		std::cout << "OBJECT!\n";
	}

	void out(){}
	virtual const char* x_ray_fon() = 0;	// реалиация в Global.cpp
};

class Mars: public Planet {
	bool life;

public:

	Mars(std::string &nm, std::string &loc, bool lf = false):
		life(lf), Planet(nm, loc) {}

	const char* x_ray_fon() override { return "max 2 rgn!"; }
};

class Neptun: public Planet {
private: 
	bool life;

public:
	Neptun(std::string &nm, std::string &loc, bool lf = false):
		life(lf), Planet(nm, loc) {}

	const char* x_ray_fon() {
		return Planet::x_ray_fon();		// используем определение по умолчанию (Global.cpp)
	}

 };

 ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Решение проблемы Алмаза смерти через виртуальный базовый класс
// Виртуальный базовый класс — это класс, объект которого является общим для использования всеми дочерними классами.

class Device {
public:
	Device() { std::cout << "Device!\n"; }
};

 class Printer: virtual public Device {				// Device стал виртуальным базовым классом!
 public:
	 Printer(): Device()							// в данной программе построение родителя проигнориркется!
	 { std::cout << "Printer!\n"; }
};

 class Scanner: virtual public Device {				// Device стал виртуальным базовым классом!
 public:
	 Scanner():Device()								// в данной программе построение родителя проигнориркется!
	 { std::cout << "Scanner!\n"; }
 };

 class Copier: public Printer, public Scanner {
 public:
	 Copier(): Printer(), Scanner(), 
		 Device()									// построение головного родителя выполняется здесь!
	 { std::cout << "Copier!\n"; }
  };

 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 class Dad {
 private:
	 int *ptr;
 
 public:
	 Dad(): ptr(new int) {}
	 Dad(const Dad &copy) { ptr = new int; }						// для преcечения утечки памяти и переадресации указателя (Sun является Dad!) + открытый доступ								
	 
	 		
	 //Dad(const Sun &copy) { ptr = new int; }
	 virtual ~Dad() { delete ptr; }
	 virtual void get_name() { std::cout << "Dad\n"; }
  };

 class Sun: public Dad {
 private:
	 int *ptr;

 public:
	 Sun(): ptr(new int), Dad() {}
	 Sun(Sun &copy) {  ptr = new int; }
	 ~Sun() { delete ptr; }
	 void get_name() override { std::cout << "Sun\n"; }
 };

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 class Apple {
 protected:
	 int *value;
	 
 public:
	 Apple(): value(new int) {};
	 Apple(const Apple &copy)
	 {
		 delete value;
		 value = new int;
	 }
	 virtual ~Apple() { delete value;}

	 virtual void get_name() { std::cout << "Apple\n"; }

	 void get_Apple() { std::cout << "Apple_info\n"; }
 };

 class Iphone: public Apple {
 protected:
	 int *ptr;

 public:
	 Iphone(): ptr(new int), Apple() {}
	 Iphone(const Iphone &copy)
	 {
		 delete ptr;
		 ptr = new int;
	 }
	 ~Iphone() override { delete ptr; }

	 void get_name() override { std::cout << "Iphone\n"; }

	 void get_Iphone() { std::cout << "Apple::XR 9\/10\n"; }

	 void out() { std::cout << ptr; }
 };

 /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

 class Box1 {
 public:
	 friend std::ostream& operator<<(std::ostream &out, const Box1 &ref) {
		 
		 return ref.print(out);
	 }

	 virtual std::ostream& print(std::ostream& out) const {
		 out << "Box1->";
		 return out;
	 }
 };

 class Box2: public Box1 {
 public:
	 Box2() {};
	 Box2(int a): Box1() {}

	 std::ostream& print(std::ostream& out) const override{
		 out << "Box2;";
		 return out;
	 }
 };

 