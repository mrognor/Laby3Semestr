
#include <iostream>
#include <vector>
#include <queue>


class Node
{
public:
	int Number;
	std::vector<int> Nodes;

	bool WasPassed = false;
	int Distance = 0;

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
	if (n1.Number > n2.Number)
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

/// Алгоритм Дейкстры
std::vector<Node> Dijkstra(int index, std::vector<Node> nodes)
{
	/// Очередь с приоритетом для всех элементов
	std::queue<Node> NodesQueue;
	
	std::vector<Node> ReturnVector = nodes;
	
	nodes[index].WasPassed = true;
	NodesQueue.push(nodes[index]);

	// Проход по очереди
	while (!NodesQueue.empty())
	{
		for (int i = 0; i < nodes.size(); i++)
		{
			if (NodesQueue.front().Nodes[i] > 0 && NodesQueue.front().Distance + NodesQueue.front().Nodes[i] < nodes[i].Distance + NodesQueue.front().Nodes[i])
				nodes[i].WasPassed = false;
			
			if (NodesQueue.front().Nodes[i] > 0 && nodes[i].WasPassed == false)
			{
				nodes[i].WasPassed = true;
				nodes[i].Distance = NodesQueue.front().Distance + NodesQueue.front().Nodes[i];
				NodesQueue.push(nodes[i]);
			}
		}

		if (ReturnVector[NodesQueue.front().Number].Distance == 0)
			ReturnVector[NodesQueue.front().Number].Distance = NodesQueue.front().Distance;

		if (NodesQueue.front().Distance < ReturnVector[NodesQueue.front().Number].Distance && NodesQueue.front().Distance > 0)
			ReturnVector[NodesQueue.front().Number].Distance = NodesQueue.front().Distance;

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


	std::vector<std::vector<int>> Matrix1 = {
		{0, 8, 1, 7, 0, 0},
		{8, 0, 5, 0, 3, 0},
		{1, 5, 0, 5, 6, 4},
		{7, 0, 5, 0, 0, 2},
		{0, 3, 6, 0, 0, 0},
		{0, 0, 4, 2, 0, 0}
	};

	std::vector<Node> Nodes1;
	for (int i = 0; i < Matrix1.size(); i++)
		Nodes1.push_back(Node(i, Matrix1[i]));

	auto f = Dijkstra(0, Nodes1);

	std::cout << std::endl;

	for (int i = 0; i < f.size(); i++)
	{
		std::cout << "Number: " << f[i].Number << " Path length: " << f[i].Distance << std::endl;

		for (int j = 0; j < f[i].Nodes.size(); j++)
		{
			std::cout << f[i].Nodes[j] << " ";
		}
		std::cout << std::endl;
	}

}