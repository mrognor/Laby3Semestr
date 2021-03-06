#include <iostream>
#include <fstream>

using namespace std;

template <class T>
class Element
{
	//элемент связного списка
private:
	//указатель на предыдущий и следующий элемент
	Element* next;
	Element* prev;

	//информация, хранимая в поле
	T field;
public:
	//доступ к полю *next
	virtual Element* getNext() { return next; }
	virtual void setNext(Element* value) { next = value; }

	//доступ к полю *prev
	virtual Element* getPrevious() { return prev; }
	virtual void setPrevious(Element* value) { prev = value; }

	//доступ к полю с хранимой информацией field
	virtual T getValue() { return field; }
	virtual void setValue(T value) { field = value; }

	Element() { next = prev = NULL; }
	Element(T value) { next = prev = NULL; field = value; }

	template<class T> friend ostream& operator<< (ostream& ustream, Element<T>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, Element<T>& obj)
{
	ustream << obj.field;
	return ustream;
}

template <class T>
class LinkedListParent
{
protected:
	//достаточно хранить начало и конец
	Element<T>* head;
	Element<T>* tail;
	//для удобства храним количество элементов
	int num;
public:
	virtual int Number() { return num; }

	virtual Element<T>* getBegin() { return head; }

	virtual Element<T>* getEnd() { return tail; }

	LinkedListParent()
	{
		//конструктор без параметров
		cout << "\nParent constructor";
		head = NULL;
		num = 0;
	}

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать добавление
	virtual Element<T>* push(T value) = 0;

	//чисто виртуальная функция: пока не определимся с типом списка, не сможем реализовать удаление
	virtual Element<T>* pop() = 0;

	virtual ~LinkedListParent()
	{
		if (tail == nullptr && head == nullptr)
			return;
		if (tail == head)
			delete tail;

		for (auto i = tail->getPrevious(); i != head; i = i->getPrevious())
		{
			delete i->getNext();
		}
		delete head;
	}

	//получение элемента по индексу - какова асимптотическая оценка этого действия?
	virtual Element<T>* operator[](int i)
	{
		//индексация
		if (i<0 || i>num) return NULL;
		int k = 0;

		//ищем i-й элемент - вставем в начало и отсчитываем i шагов вперед
		Element<T>* cur = head;
		for (k = 0; k < i; k++)
		{
			cur = cur->getNext();
		}
		return cur;
	}

	template<class T> friend ostream& operator<< (ostream& ustream, LinkedListParent<T>& obj);
	template<class T> friend istream& operator>> (istream& ustream, LinkedListParent<T>& obj);
};

template<class T>
ostream& operator << (ostream& ustream, LinkedListParent<T>& obj)
{
	if (typeid(ustream).name() == typeid(ofstream).name())
	{
		ustream << obj.num << "\n";
		for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext())
			ustream << current->getValue() << " ";
		return ustream;
	}

	ustream << "\nLength: " << obj.num << "\n";
	int i = 0;
	for (Element<T>* current = obj.getBegin(); current != NULL; current = current->getNext(), i++)
		ustream << "arr[" << i << "] = " << current->getValue() << "\n";

	return ustream;
}

template<class T>
istream& operator >> (istream& ustream, LinkedListParent<T>& obj)
{
	//чтение из файла и консоли совпадают
	int len;
	ustream >> len;
	//здесь надо очистить память под obj, установить obj.num = 0
	double v = 0;
	for (int i = 0; i < len; i++)
	{
		ustream >> v;
		obj.push(v);
	}
	return ustream;
}

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
private:
	//текущий элемент
	Element<ValueType>* ptr;
};

//класс итерируемый список - наследник связного списка, родитель для Очереди и Стека
template <class T>
class IteratedLinkedList : public LinkedListParent<T>
{
public:
	IteratedLinkedList() : LinkedListParent<T>() { cout << "\nIteratedLinkedList constructor"; }


	ListIterator<T> begin() { ListIterator<T> it = LinkedListParent<T>::head; return it; }
	ListIterator<T> end() { ListIterator<T> it = LinkedListParent<T>::tail; return it; }
};

template <class T>
class Stack : public IteratedLinkedList<T>
{
public:
	Stack() : IteratedLinkedList<T>() { cout << "\nStack constructor"; }

	virtual Element<T>* push(T value) override
	{
		if (IteratedLinkedList<T>::num > 0)
		{
			Element<T>* newElem = new Element<T>(value);
			IteratedLinkedList<T>::tail->setNext(newElem);
			newElem->setPrevious(IteratedLinkedList<T>::tail);
			IteratedLinkedList<T>::tail = IteratedLinkedList<T>::tail->getNext();
		}
		else
		{
			IteratedLinkedList<T>::tail = new Element<T>(value);
			IteratedLinkedList<T>::head = IteratedLinkedList<T>::tail;
		}
		IteratedLinkedList<T>::num++;
		return IteratedLinkedList<T>::tail;
	}

	virtual Element<T>* pop() override
	{
		if (IteratedLinkedList<T>::num > 0)
		{
			auto f = IteratedLinkedList<T>::tail;
			IteratedLinkedList<T>::tail = IteratedLinkedList<T>::tail->getPrevious();
			IteratedLinkedList<T>::tail->setNext(NULL);
			f->setPrevious(NULL);
			return f;
		}
		return NULL;
	}
};

bool condition(int value)
{
	return (value > 0);
}

template <class T>
void filter(IteratedLinkedList<T>* source, IteratedLinkedList<T>* dest, bool (*ptrfunc)(T))
{
	ListIterator<T> it = source->begin();
	while (it != source->end())
	{
		if (ptrfunc((*it).getValue()))
			dest->push((*it).getValue());
		it++;
	}
	if (source->Number() != 0 && ptrfunc((*it).getValue()))
		dest->push((*it).getValue());
}

template<class T>
class SortedStack : public Stack<T>
{
	SortedStack() : Stack<T>() { cout << "\nSortedStack constructor"; }

	virtual Element<T>* push(T value) override
	{
		if (IteratedLinkedList<T>::num > 0)
		{
			Element<T>* newElem = new Element<T>(value);
			auto f = IteratedLinkedList<T>::head;
			while (f != IteratedLinkedList<T>::tail)
			{
				if (f.getValue() > value)
					break;
				f = f.getNext();
			}
			f.getPrevious().setNext(newElem);
			newElem->setPrevious(f.getPrevious());
			newElem->setNext(f);
			f.setPrevious(newElem);
		}
		else
		{
			IteratedLinkedList<T>::tail = new Element<T>(value);
			IteratedLinkedList<T>::head = IteratedLinkedList<T>::tail;
		}
		IteratedLinkedList<T>::num++;
		return IteratedLinkedList<T>::tail;
	}
};

class Serial
{
private:
	string Name = "None";
	string Producer = "None";
	int Sesons = 0;
	int Popularity = 0;
	int Rank = 0;
	string Date = "None";
	string Country = "None";
public:

	friend ostream& operator<<(ostream& stream, const Serial& S);

	void SetName(string name) { Name = name; }
	void SetRank(int rank) { Rank = rank; }

	bool operator==(const Serial& s)
	{
		bool f = true;

		if (Name == s.Name)
			f = false;

		if (Producer == s.Producer)
			f = false;

		if (Sesons == s.Sesons)
			f = false;

		if (Popularity == s.Popularity)
			f = false;

		if (Rank == s.Rank)
			f = false;

		if (Date == s.Date)
			f = false;

		if (Country == s.Country)
			f = false;

		return f;
	}

	bool operator>(const Serial& s)
	{
		if (Rank > s.Rank)
			return true;
		if (Rank < s.Rank)
			return false;
		if (Rank == s.Rank)
		{
			if (Name > s.Name)
				return true;
			if (Name < s.Name)
				return false;
		}
		return false;
	}

	bool operator<(const Serial& s)
	{
		if (Rank < s.Rank)
			return true;
		if (Rank > s.Rank)
			return false;
		if (Rank == s.Rank)
		{
			if (Name < s.Name)
				return true;
			if (Name > s.Name)
				return false;
		}
		return false;
	}
};

ostream& operator<<(ostream& stream, const Serial& S)
{
	stream << "Name: " << S.Name << " Producer: " << S.Producer << " Sesons: " << S.Sesons
		<< " Popularity: " << S.Popularity << " Rank: " << S.Rank << " Date: " << S.Date << " County: "
		<< S.Country;
	return stream;
}

int main()
{

	Stack<int> S;
	cout << "\n";
	S.push(1);
	S.push(2);
	S.push(3);
	cout << S;
	cout << "\n";
	Element<int>* e1 = S.pop();
	cout << "\nElement = " << e1->getValue();
	cout << S;
	cout << "\nIndex in the Stack class: " << S[1]->getValue();

	cout << S;
	cout << "\nIterators:\n";
	auto f = S.begin();
	while (f != S.end())
	{
		cout << *f << " ";
		f++;
	}
	cout << *f << " ";

	Stack<int> S1;
	filter(&S, &S1, condition);
	cout << "\nFilter: " << S1;
	cout << endl;

	Stack<Serial> S2;
	Serial A; Serial B; Serial C; Serial D;
	A.SetRank(10);
	B.SetRank(10);
	C.SetRank(8);
	D.SetRank(7);
	A.SetName("AAAA");
	B.SetName("AABB");
	C.SetName("AAAA");
	D.SetName("AAAA");
	cout << S2 << endl;
}
