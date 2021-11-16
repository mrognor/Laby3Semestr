
#include <iostream>
#include <vector>
#include <queue>

class Node
{
public:
	int Number;
	std::vector<int> Nodes;

	int DistanceToThisElement = 0;
	int SourceElement;
	bool WasPassed = false;
	bool WasFinallyPassed = false;

	Node(int number, std::vector<int> nodes) : Number(number), Nodes(nodes) {}

	friend bool operator<(const Node& n1, const Node& n2);

	bool operator==(const Node& n)
	{
		if (Number == n.Number)
			return true;
		return false;
	}

	friend std::ostream& operator<<(std::ostream& stream, Node& nod);
};

std::ostream& operator<<(std::ostream& str, const Node& nod)
{
	str << "Number: " << nod.Number;
	return str;
}

bool operator<(const Node& n1, const Node& n2)
{
	if (n1.DistanceToThisElement > n2.DistanceToThisElement)
		return true;
	return false;
}

template <class T>
void PrinPriorityQueue(std::priority_queue<T> q)
{
	while (!q.empty())
	{
		std::cout << q.top() << std::endl;
		q.pop();
	}
}

/// Алгоритм Прима
std::vector<Node> FindOstov(int index, std::vector<Node> nodes)
{
	/// Очередь с приоритетом для всех элементов
	std::priority_queue<Node> NodesQueue;
	
	std::vector<Node> ReturnVector;
	ReturnVector.reserve(nodes.size());

	/// Добавляем в очередь первый элемент
	nodes[index].SourceElement = index;
	nodes[index].WasPassed = true;
	//nodes[index].WasFinallyPassed = true;
	NodesQueue.push(nodes[index]);


	// Проход по очереди
	while (!NodesQueue.empty())
	{
		// Сохраняем первый элемент из очереди для получения значений, а затем удаляем его из очереди
		auto f = NodesQueue.top();
		NodesQueue.pop();

		// В этом цикле мы проходим по всему вектору вершин. 
		// Тут мы определяемя дистанцию от текущего элемента в очереди до каждого элемента вектора
		// Мы помечаем вершину пройденной с помощью массива пройденных вершин
		for (int i = 0; i < nodes.size(); i++)
		{
			// Если мы были в вершине, но она не была напечатана и расстояние до нее от текущей вершины из очереди меньше, то мы должны повторно добавить ее в очередь
			if (nodes[i].WasPassed == true && nodes[i].WasFinallyPassed == false && f.Nodes[i] < nodes[i].DistanceToThisElement && nodes[i].DistanceToThisElement > 0)
				nodes[i].WasPassed = false;

			// Установка источника и расстояния для текущего элемента
			nodes[i].SourceElement = f.Number;
			nodes[i].DistanceToThisElement = f.Nodes[i];

			// Если мы не были в этой вершине и расстояние до нее больше ноля, то мы заходим в нее
			if (nodes[i].WasPassed == false && nodes[i].WasFinallyPassed == false && nodes[i].Nodes[f.Number] > 0)
			{
				nodes[i].WasPassed = true;
				NodesQueue.push(nodes[i]);
			}
		}

		// Вывод элемента в консоль
		if (nodes[f.Number].WasFinallyPassed == false)
		{
			//std::cout << "From: " << f.SourceElement << " With distance: " << nodes[f.SourceElement].Nodes[f.Number] << " To: " << f.Number << std::endl;
			f.WasPassed = false;
			f.WasFinallyPassed = false;
			ReturnVector.push_back(f);
		}
		// Говорим что прошли вершину окончательно
		nodes[f.Number].WasFinallyPassed = true;
	}

	return ReturnVector;
}

std::vector<Node> BFS(int index, std::vector<Node> nodes)
{
	std::queue<Node> NodesQueue;

	std::vector<Node> ReturnVector;
	ReturnVector.reserve(nodes.size());

	nodes[index].WasFinallyPassed = true;

	NodesQueue.push(nodes[index]);

	while (!NodesQueue.empty())
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			if (nodes[i].WasFinallyPassed == false && nodes[i].SourceElement == NodesQueue.front().Number)
			{
				nodes[i].WasFinallyPassed = true;
				NodesQueue.push(nodes[i]);
			}
		}
		
		NodesQueue.front().WasFinallyPassed = false;
		ReturnVector.push_back(NodesQueue.front());

		NodesQueue.pop();
	}

	return ReturnVector;
}
int main()
{
	std::vector<std::vector<int>> Matrix = {
	{ 0, 5, 3, 6, 8, 9, 7, 8, 1, 7, 0, 0, 4, 8 },
	{ 5, 0, 0, 3, 6, 9, 6, 5, 0, 8, 0, 0, 5, 6 },
	{ 3, 0, 0, 2, 8, 1, 3, 0, 8, 8, 5, 5, 8, 4 },
	{ 6, 3, 2, 0, 4, 6, 6, 4, 6, 8, 8, 6, 9, 4 },
	{ 8, 6, 8, 4, 0, 2, 8, 0, 9, 0, 8, 2, 0, 5 },
	{ 9, 9, 1, 6, 2, 0, 8, 5, 5, 9, 8, 8, 9, 8 },
	{ 7, 6, 3, 6, 8, 8, 0, 3, 6, 6, 8, 1, 5, 6 },
	{ 8, 5, 0, 4, 0, 5, 3, 0, 7, 1, 4, 7, 8, 5 },
	{ 1, 0, 8, 6, 9, 5, 6, 7, 0, 1, 2, 5, 2, 2 },
	{ 7, 8, 8, 8, 0, 9, 6, 1, 1, 0, 6, 2, 4, 8 },
	{ 0, 0, 5, 8, 8, 8, 8, 4, 2, 6, 0, 8, 4, 3 },
	{ 0, 0, 5, 6, 2, 8, 1, 7, 5, 2, 8, 0, 5, 5 },
	{ 4, 5, 8, 9, 0, 9, 5, 8, 2, 4, 4, 5, 0, 3 },
	{ 8, 6, 4, 4, 5, 8, 6, 5, 2, 8, 3, 5, 3, 0 },
	};

	std::vector<Node> Nodes;
	for (int i = 0; i < Matrix.size(); i++)
		Nodes.push_back(Node(i, Matrix[i]));

	FindOstov(0, Nodes);

	std::vector<std::vector<int>> Matrix1 = {
		{0, 6, 1, 5, 0, 0},
		{6, 0, 5, 0, 3, 0},
		{1, 5, 0, 5, 6, 4},
		{5, 0, 5, 0, 0, 2},
		{0, 3, 6, 0, 0, 0},
		{0, 0, 4, 2, 0, 0}
	};

	std::vector<Node> Nodes1;
	for (int i = 0; i < Matrix1.size(); i++)
		Nodes1.push_back(Node(i, Matrix1[i]));

	auto f = FindOstov(0, Nodes1);

	for (int i = 0; i < f.size(); i++)
	{
		std::cout << "From: " << f[i].SourceElement << " With distance: " << f[i].Nodes[f[i].SourceElement] << " To: " << f[i].Number <<  " Paths: ";

		for (int j = 0; j < f[i].Nodes.size(); j++)
		{
			std::cout << f[i].Nodes[j] << " ";
		}
		std::cout << std::endl;
	}

	std::cout << "G" << std::endl;

	auto b = BFS(0, f);

	for (int i = 0; i < b.size(); i++)
	{
		std::cout << "Element: " << b[i].Number << " Paths: ";

		for (int j = 0; j < b[i].Nodes.size(); j++)
		{
			std::cout << b[i].Nodes[j] << " ";
		}
		std::cout << std::endl;
	}
}