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
//��� ���������� ����� ���������� 4� ������, ���� ���� �� ��������� �� ����� ������������ ������ ������
void paintgraph(vector<vector<int> >& matrix, vector <int>& color, int curr = 0)
{
	//��������� ������ ��� ������ ������� ������ � �����������
	set<int> neighbours;//set-������ ��� ����� � ���������� ���� ����������� ������

	//������� ������ � ������
	queue<int> q;
	q.push(curr);
	while (!q.empty())
	{
		curr = q.front();
		q.pop();
		//������� ��� ���������?
		if (color[curr] != 0)
			continue;
		neighbours.clear();

		for (int next = 0; next < matrix.size(); next++)
			if (matrix[curr][next] == 1 && !color[next])
			{

				//��������� ����� ���� ������� ������
				if (color[next])
				{
					neighbours.insert(color[next]);
				}
				else
				{
					q.push(next);
				}
			}

		//������� ������ - ���� ���������� ���� � ���������� ��������
		int color_counter = 1;
		auto it = neighbours.begin();
		do
		{
			//���� �� ���� ����� ����� ����� �������?
			it = neighbours.find(color_counter);
			if (it == neighbours.end())
			{//���� �� ������- �������
				break;
			}
			color_counter++;
		} while (true);

		//������ ������� � ���������� ����
		color[curr] = color_counter;
	}
}

int main() {

	vector<vector<int> > mat =
	{
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
	}

	vector<int> color(6, 0);
	drawgraph(mat, color, 0);
	std::cout << "\nColor: ";
	for (int i = 0; i < 6; i++) std::cout << color[i] << " ";

	char c1; cin >> c1;

	return 0;
}