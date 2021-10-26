using namespace std;
#include <map>
#include <iostream>

struct Serial
{
	int Rank;
	Serial() { Rank = rand() % 10; }

	friend std::ostream& operator<<(std::ostream& stream, const Serial& serial)
	{
		stream << "Rank: " << serial.Rank;
		return stream;
	}
};

bool operator==(Serial serA, Serial serB)
{
	if (serA.Rank == serB.Rank)
		return true;
	else
		return false;
}

template <class TKey, class TValue>
pair<TKey, TValue> FindByKey(const map<TKey, TValue>& Map, TKey key)
{
	auto res = Map.find(key);

	if (res != Map.end())
	{
		return pair<TKey, TValue>(res->first, res->second);
	}
	
}

template <class TKey, class TValue>
pair<TKey, TValue> FindByValue(const map<TKey, TValue>& Map, TValue value)
{
	auto it = Map.begin();
		while (it != Map.end())
		{
			if (it->second == value)
				return pair<TKey, TValue>(it->first, it->second);
				it++;
		}
}

template <class TKey, class TValue>
void PrintMap(const map<TKey, TValue>& Map)
{
	auto it_m = Map.begin();
	while (it_m != Map.end())
	{
		cout << "Key: " << it_m->first << ", value: " << it_m->second << "\n";
		it_m++;
	}
}

bool Predicat(Serial x)
{
	if (x.Rank > 6) return true;
	return false;
}

template <class TKey, class TValue>
std::map<TKey, TValue> filter(std::map<TKey, TValue>& mp, bool(*func)(TValue x))
{
	std::map<TKey, TValue> newmap;
	for (auto element : mp)
	{
		if (func(element.second)) { newmap[element.first] = element.second; }
	}
	return newmap;
}

int main()
{
	map<string, Serial> Serials;

	Serial A, B, C, D, E, F;

	Serials["Serial A"] = A;
	Serials["Serial B"] = B;
	Serials["Serial C"] = C;
	Serials["Serial D"] = D;
	Serials["Serial E"] = E;
	Serials["Serial F"] = F;

	auto f = FindByKey<string, Serial>(Serials, "Serial A");
	cout << "Key: " << f.first << ", value: " << f.second << endl;
	cout << endl;
	auto d = FindByValue<string, Serial>(Serials, D);
	cout << "Key: " << d.first << ", value: " << d.second << endl;
	cout << endl;
	PrintMap(Serials);
	cout << endl;
	auto g = filter(Serials, Predicat);
	PrintMap(g);
}