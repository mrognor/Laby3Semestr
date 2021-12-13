// TestGraph.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <iomanip>  
#include <set>
#include <vector>
#include <string>
#include <algorithm>
#include <typeinfo>
#include <fstream>
#include <stack>
#include <queue>
#define BIG_NUMBER 1000

using namespace std;

bool try_kuhn(int v, vector < vector<int> >& g, vector<int>& used, vector<int>& mt) {
	if (used[v])
		return false;
	used[v] = true;
	for (int i = 0; i < g[v].size() ; ++i) 
	{
		int to = g[v][i];
		if (mt[to] == -1 || try_kuhn(mt[to], g, used, mt))
		{
			mt[to] = v;
			return true;
		}
	}
	return false;
}

vector<int> khun( vector<vector<int>>& g )
{
	int n = 8; int k = 8;
	vector<int> mt;
	vector<int> used;
	vector<int> connections;
	connections.assign(n, -1);
	for (int i = 0; i < n; i++) used.push_back(0);

	mt.assign(k, -1);
	for (int v = 0; v < n; v++) {
		used.assign(n, false);
		if (try_kuhn(v, g, used, mt))
		{

			for (int i = 0; i < k; ++i)
			{
				if (mt[i] != -1)
				{
					connections[mt[i]] = i;
				}
			}
			
		}
	}
	return connections;
}

int main()
{
	std::cout << "\n---Kuhn algorithm---\n";
	vector < vector<int> > g;


	g = {
		{ 4,6}, // список ребер
		{ 5,6},
		{ 4,6 },
		{ 5,7 },
		{},
		{},
		{},
		{}
	};

	vector<int> a = khun(g);
	for (auto el : a)
	{
		cout << el << endl;
	}
	char c; cin >> c;
	return 0;
}
