// Task 1.1
void PushOnePointOne(list<double>* lst, double elem)
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

void PrintOnePointOne(list<double> lst)
{
	for (list<double>::iterator it = lst.begin(); it != lst.end(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}

void PopOnePointOne(list<double>* lst, int pos)
{
	if (pos >= lst->size())
		exit(2);

	int count = 0;
	for (list<double>::iterator it = lst->begin(); it != lst->end(); it++)
	{
		if (count == pos)
		{
			lst->remove(*it);
			return;
		}
		count++;
	}
}

bool PredicatOnePointOne(double a)
{
	return (a > 0) ? true : false;
}

list<double>* FilterOnePointOne(list<double>* lst, bool (*f)(double))
{
	list<double>* tmplst = new list<double>;
	for (list<double>::iterator it = lst->begin(); it != lst->end(); it++)
	{
		if (f(*it))
		{
			tmplst->push_back(*it);
		}
	}
	return tmplst;
}
// End task 1.1

int main()
{
	list<double> OnePointOne{ 2.0, -3.0, 5.6, -1.0, 2.0, 5.7, -23.76 };
	PrintOnePointOne(OnePointOne);

	PushOnePointOne(&OnePointOne, 89.9);
	PrintOnePointOne(OnePointOne);

	PopOnePointOne(&OnePointOne, 2);
	PrintOnePointOne(OnePointOne);

	auto p = FilterOnePointOne(&OnePointOne, PredicatOnePointOne);
	PrintOnePointOne(*p);
}