#include <iostream>
#include <list>

using namespace std;

template <class T>
void Push(list<double>* lst, T elem)
{
	for (list<double>::iterator it = lst->begin(); it != lst->end(); it++)
	{
		if (elem < *it)
		{
			lst->insert(it, elem);
			return;
		}
	}
	lst->insert(lst->end(), elem);
}

template <class T>
void Print(list<T> lst)
{
	for (auto it = lst.begin(); it != lst.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

template <class T>
void Pop(list<T>* lst, int pos)
{
	if (pos >= lst->size())
		exit(2);

	int count = 0;
	for (auto it = lst->begin(); it != lst->end(); it++)
	{
		if (count == pos)
		{
			lst->remove(*it);
			return;
		}
		count++;
	}
}

template <class T>
bool Predicat(T a)
{
	return (a > 0) ? true : false;
}

template <class T>
list<T>* Filter(list<T>* lst, bool (*f)(T))
{
	// После использования new мы должны сделать delete, но мы возвращаем указатель. Как нам потом очистить память 
	list<T>* tmplst = new list<T>;
	for (auto it = lst->begin(); it != lst->end(); it++)
	{
		if (f(*it))
		{
			tmplst->push_back(*it);
		}
	}
	return tmplst;
}


int main()
{
	list<double> OnePointOne{ 2.0, -3.0, 5.6, -1.0, 2.0, 5.7, -23.76 };
	Print(OnePointOne);

	Push(&OnePointOne, 89.9);
	Print(OnePointOne);

	Pop(&OnePointOne, 2);
	Print(OnePointOne);

	auto p = Filter(&OnePointOne, Predicat);
	Print(*p);
}