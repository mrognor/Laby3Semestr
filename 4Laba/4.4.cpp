// TestGraph.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <iomanip>  
#include <set>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


class Edge
{
public:
	int from, to, weight;
	Edge(int from = -1, int to = -1, int weight = 0) : from(from), to(to), weight(weight) {}
	Edge(const Edge& E)
	{
		from = E.from;
		to = E.to;
		weight = E.weight;
	}
	int operator<(Edge& E)
	{
		return (weight < E.weight);
	}
	friend ostream& operator<<(ostream& s, Edge& e);
};

ostream& operator<<(ostream& s, Edge& e)
{
	s << "From: " << e.from << ", to: " << e.to << ", weight: " << e.weight;
	return s;
}
//для планарного графа достаточно 4х цветов, если граф не планарный то может понадобиться больше цветов
void paintgraph(vector<vector<int> >& matrix, vector <int>& color, int curr=0)
{
	//структура данных для цветов смежных вершин с исследуемой
	set<int> neighbours;//set-потому что поиск и добавление идет максимально быстро

	//аналоги поиска в ширину
	queue<int> q;
	q.push(curr);
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		//вершина уже закрашена?
		if (color[curr] != 0)
			continue;
		neighbours.clear();

		for (int next = 0; next < matrix.size(); next++)
			if (matrix[curr][next] == 1&& !color[next])
			{
				
				//проверяем цвета всех смежных вершин
				if(color[next])
				{
					neighbours.insert(color[next]);
				}
				else
				{
				q.push(next);
				}
			}

		//счетчик цветов - ищем допустимый цвет с наименьшим индексом
		int color_counter = 1;
		auto it = neighbours.begin();
		do
		{
			//есть ли этот номер цвета среди соседей?
		    it=neighbours.find(color_counter);
			if(it==neighbours.end())
			{//цвет не найден- выходим
				break;
			}
			color_counter++;
		} while (true);

		//красим вершину в допустимый цвет
		color[curr] = color_counter;
	}
}

int main() {

	vector<vector<int> > mat =
	{
	{ 0, 1, 0, 0, 0, 1 },
	{ 1, 0, 1, 0, 0, 0 },
	{ 0, 1, 0, 1, 1, 0 },
	{ 0, 0, 1, 0, 1, 0 },
	{ 0, 0, 1, 1, 0, 1 },
	{ 1, 0, 0, 0, 1, 0 }
	};

	vector<int> color(6, 0);
	drawgraph(mat, color, 0);
	std::cout << "\nColor: ";
	for (int i = 0; i < 6; i++) std::cout << color[i] << " ";

	char c1; cin >> c1;

	return 0;
}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
