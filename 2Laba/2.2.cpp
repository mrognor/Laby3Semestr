using namespace std;
#include <queue>
#include <iostream>

struct Serial
{
	int Rank;
	Serial() { Rank = rand()%10; }

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

bool operator<(Serial serA, Serial serB)
{
	if (serA.Rank < serB.Rank)
		return true;
	else
		return false;
}

template<typename T>
void print_queue(T& q) {
	while (!q.empty()) {
		cout << q.top() << " ";
		q.pop();
	}
	std::cout << '\n';
}

int main()
{
	Serial A, B, C, D, E, F;
	Serial serials[6] = { A, B, C, D, E, F };

	priority_queue<Serial> q;
	for (Serial ser : serials)
		q.push(ser);
	print_queue(q);
}