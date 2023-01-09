
template <typename T>
void Darray<T>::getlenght() {
	return size;
}

template <typename T>
void Darray<T>::set() {
	
}

template <typename T>
void Darray<T>::erase() {
	delete[] data;
	size = 0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T, int sz>
void Sarray<T, sz>::getlenght() {
	return sz;
}

template <typename T, int sz>
void Sarray<T, sz>::set(){}

template <typename T, int sz>
void Sarray<T, sz>::erase() {
	for (int i = 0; i < sz; ++i)
		array[i] = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
			// специализация шаблонов функции

template<>
void Repositoriy<double>::print() {
	std::cout << std::scientific << m_value << '\n';		// экспонентальная запись для double
}

template<>
Repositoriy<char* >::~Repositoriy() {						// деструктор для char*
	delete[] m_value;
}

template <>
class Trais8<bool> {
protected:
	unsigned char m_array;

public:
	void set(const int index, const bool bit) {
		unsigned char mask = 1 << index;
		if (bit) m_array |= mask;
		else m_array &= mask;
	}

	bool getindex(const int index) {
		return (m_array & (1 << index)) != 0;
	}
};


template <int size>
void print(Sarray<char, size> array) {
	for(int i = 0; i < size; ++i)
		std::cout << array[i];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, int size>
Array<T, size>::Array(const std::initializer_list<T> &list) {

	assert(list.size() <= size && "initializing error!");

	int index = 0;
	for (const auto &i : list) {
		m_data[index] = i;
		++index;
	}
}

