
template <typename T, int size>
Array<T, size>::Array(const std::initializer_list<T> &list) {

	if (list.size() > size) throw ArrayException("Initializing error!");

	int count = 0;
	for (const auto &i : list) {
		array[count] = i;
		++count;
	}
}

template <typename T, int size>
Array<T, size>::Array(const T &value) {
	
	for (int i = 0; i < size; ++i)
		array[i] = value;
}

template <typename T, int size>
T& Array<T, size>::operator[](const int index) {
	if (index < 0 || index > size) throw ArrayException("Invalid index!");
	return array[index];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

