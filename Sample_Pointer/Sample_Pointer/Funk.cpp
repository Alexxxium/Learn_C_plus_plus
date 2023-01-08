
#include "Header.h"

Auto_ptr<Item> generatItem() {

	Auto_ptr<Item> item(new Item);
	return item;
}

Fraction::Fraction(int x, int y) try :
	numenate(x), denuminate(y)
{
	std::cout << "\n\tFraction\n";
	if (!y) throw std::exception("Denumenator is 0\n");
}
catch(...){}

std::ostream& operator<<(std::ostream& out, const Fraction &frac) {
	return (out << frac.numenate << '/' << frac.denuminate);
}