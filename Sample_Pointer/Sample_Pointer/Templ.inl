
template<typename T>
Auto_ptr<T>::Auto_ptr(const Auto_ptr &copy) {

	if (copy.pointer)							// проверка на нулевой указатель
		pointer = new T(*copy.pointer);
	else 
		pointer = nullptr;
}

template<typename T>
Auto_ptr<T>& Auto_ptr<T>::operator=(const Auto_ptr& copy) {
	
	if (&copy == this)							// проверка на самоприсваивание
		return *this;

	delete pointer;

	if (copy.pointer)							// проверка на нулевой указатель
		pointer = new T(*copy.pointer);
	else
		pointer = nullptr;	

	return *this;
}

template <typename T>
Auto_ptr<T>& Auto_ptr<T>::operator=(Auto_ptr &&copy) noexcept {

	if (&copy == this)							// проверка на самоприсваивание
		return *this;

	delete pointer;

	pointer = copy.pointer;						// передаем право собственности copy.pointer на pointer
	copy.pointer = nullptr;						// ликвилируем указатель на перераспределенный ресурс

	return *this;
}