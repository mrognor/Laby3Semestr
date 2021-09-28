// Task 1.2
struct Serial
{
	string Name = "None";
	string Producer = "None";
	int Sesons = 0;
	int Popularity = 0;
	int Rank = 0;
	string Date = "None";
	string Country = "None";
};

ostream& operator<<(ostream& stream, const Serial& S)
{
	stream << "Name: " << S.Name << " Producer: " << S.Producer << " Sesons: " << S.Sesons
		<< " Popularity: " << S.Popularity << " Rank: " << S.Rank << " Date: " << S.Date << " County: "
		<< S.Country;
	return stream;
}

Serial* PopOnePointTwo(list<Serial>* lst, int pos)
{
	if (pos >= lst->size())
		exit(2);

	Serial* MaxElem = new Serial;
	for (list<Serial>::iterator it = lst->begin(); it != lst->end(); it++)
	{
		if ((*it).Rank > MaxElem->Rank)
			MaxElem = &(*it);
		if ((*it).Rank == MaxElem->Rank)
		{
			if ((*it).Name > MaxElem->Name)
				MaxElem = &(*it);
		}
	}

	int count = 0;
	for (list<Serial>::iterator it = lst->begin(); it != lst->end(); it++)
	{
		if (count == pos)
		{
			//lst->remove(*it);
			break;
		}
		count++;
	}
	return MaxElem;
}

void PrintOnePointTwo(list<Serial> lst)
{
	for (list<Serial>::iterator it = lst.begin(); it != lst.end(); it++)
	{
		cout << *it << endl;
	}
}
int main()
{
	Serial A; Serial B; Serial C; Serial D;
	A.Rank = 10;
	B.Rank = 10;
	C.Rank = 8;
	D.Rank = 7;
	A.Name = "AAAA";
	B.Name = "AABB";
	C.Name = "AAAA";
	D.Name = "AAAA";

	list<Serial> OnePointTwo{ A,B,C,D };
	auto f = PopOnePointTwo(&OnePointTwo, 2);
	cout << *f << endl;
	cout << endl;
	PrintOnePointTwo(OnePointTwo);
}