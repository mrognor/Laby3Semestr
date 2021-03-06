#include <iostream>
#include <list>

using namespace std;

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

template <class T>
T PopFirst(list<T>* lst)
{
	T tmp = *(--lst->end());
	lst->pop_back();
	return tmp;
}

template <class T>
void Print(list<T> lst)
{
	for (auto it = lst.begin(); it != lst.end(); it++)
	{
		cout << *it << endl;
	}
}
int main()
{
	Serial A; Serial B; Serial C; Serial D;
	A.SetRank(10);
	B.SetRank(10);
	C.SetRank(8);
	D.SetRank(7);
	A.SetName("AAAA");
	B.SetName("AABB");
	C.SetName("AAAA");
	D.SetName("AAAA");

	list<Serial> OnePointTwo{ A,B,C,D };
	auto f = PopFirst(&OnePointTwo);
	cout << f << endl;
	cout << endl;
	Print(OnePointTwo);
}