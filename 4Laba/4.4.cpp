
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

using namespace std;

bool hamilton(vector<vector<int> >& mat,  vector <bool>& visited, vector <int>& path, int curr,bool flag = true) 
{
	path.push_back(curr);
	
	if(path.size()==mat.size())
	{
		
        bool re = flag ? true : (mat[curr][path[0]] > 0) ? true : false;
        if (re)
            return re;
	}

	visited[curr] = true;

	for(int i=0;i<mat.size();i++)
	{
		if (mat[curr][i]>0 && !visited[i])
		{
			if (hamilton(mat,visited,path,i,flag)) 
			{
				return true;
			}
		}
	}



	visited[curr] = false;
	path.pop_back();
	return false;
}

vector<int> hamilton(vector<vector<int> >& mat,  vector <bool>& visited, int curr,bool flag = true) 
{
	vector <int> path;
	path.push_back(curr);
	
	if(path.size()==mat.size())
	{
		
        bool re = flag ? true : (mat[curr][path[0]] > 0) ? true : false;
        if (re)
            return path;
	}

	visited[curr] = true;

	for(int i=0;i<mat.size();i++)
	{
		if (mat[curr][i]>0 && !visited[i])
		{
			if (hamilton(mat,visited,path,i,flag)) 
			{
				return path;
			}
		}
	}
	path.clear();
	path.push_back(curr);
	return path;
}

int main() 
{
	
	vector<vector<int> > mat=
	{
        { 0, 6, 5, 6, 7, 5, 8, 8, 2 },
        { 6, 0, 2, 5, 1, 4, 4, 3, 2 },
        { 5, 2, 0, 0, 6, 7, 5, 4, 2 },
        { 6, 5, 0, 0, 2, 4, 1, 7, 4 },
        { 7, 1, 6, 2, 0, 8, 0, 9, 5 },
        { 5, 4, 7, 4, 8, 0, 9, 8, 0 },
        { 8, 4, 5, 1, 0, 9, 0, 7, 5 },
        { 8, 3, 4, 7, 9, 8, 7, 0, 7 },
        { 2, 2, 2, 4, 5, 0, 5, 7, 0 },
    };
	vector<bool> visited(mat.size(), 0);
	vector<int> path = hamilton(mat, visited, 0, false);

	for (auto el : path)
	{
		cout << el << '\t' ;
	}

	char c1; cin >> c1;

	char c; std::cin >> c;
	return 0;
}
