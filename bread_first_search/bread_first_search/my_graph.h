#pragma once
#include <string>
#include <vector>

using namespace std;

class my_graph
{
private:
	vector<vector<int>> Adjacency_matrix;
	int size;

	int solve_size(string filename);

public:
	my_graph(string filename);
};

