
template<typename T>
Auto_ptr<T>::Auto_ptr(const Auto_ptr &copy) {

	if (copy.pointer)							// �������� �� ������� ���������
		pointer = new T(*copy.pointer);
	else 
		pointer = nullptr;
}

template<typename T>
Auto_ptr<T>& Auto_ptr<T>::operator=(const Auto_ptr& copy) {
	
	if (&copy == this)							// �������� �� ����������������
		return *this;

	delete pointer;

	if (copy.pointer)							// �������� �� ������� ���������
		pointer = new T(*copy.pointer);
	else
		pointer = nullptr;	

	return *this;
}

template <typename T>
Auto_ptr<T>& Auto_ptr<T>::operator=(Auto_ptr &&copy) noexcept {

	if (&copy == this)							// �������� �� ����������������
		return *this;

	delete pointer;

	pointer = copy.pointer;						// �������� ����� ������������� copy.pointer �� pointer
	copy.pointer = nullptr;						// ����������� ��������� �� ������������������ ������

	return *this;
}