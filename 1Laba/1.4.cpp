#include <iostream>
#include <fstream>
using namespace std;

//дописать класс итератора по списку
template<typename ValueType>
class ListIterator : public std::iterator<std::input_iterator_tag, ValueType>
{
public:
	//конструкторы
	ListIterator() { ptr = NULL; }
	ListIterator(Element<ValueType>* p) { ptr = p; }
	ListIterator(const ListIterator& it) { ptr = it.ptr; }

	//методы работы с итераторами
	//присваивание
	ListIterator& operator=(const ListIterator& it) { ptr = it.ptr; return *this; }
	ListIterator& operator=(Element<ValueType>* p) { ptr = p; return *this; }

	//проверка итераторов на равенство
	bool operator!=(ListIterator const& other) const { return ptr != other.ptr; }
	bool operator==(ListIterator const& other) const { return ptr == other.ptr; }
	//получить значение
	Element<ValueType>& operator*()
	{
		return *ptr;
	}
	//перемещение с помощью итераторов
	ListIterator& operator++()
	{
		if (ptr != NULL)
			ptr = ptr->getNext();
		return *this;
	}
	ListIterator& operator++(int v)
	{
		if (ptr != NULL)
			ptr = ptr->getNext();
		return *this;
	}
	ListIterator& operator--()
	{
		if (ptr != NULL)
			ptr = ptr->getPrevious();
		return *this;
	}
	ListIterator& operator--(int v)
	{
		if (ptr != NULL)
			ptr = ptr->getPrevious();
		return *this;
	}
private:
	//текущий элемент
	Element<ValueType>* ptr;;
};