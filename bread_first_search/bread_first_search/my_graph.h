#pragma once
#include <string>
#include <vector>

using namespace std;

class my_graph
{
private:
	vector<vector<int> > adj_matr;
	int size;

	int solve_size(string filename);
	void read_matrix(string filename, vector<vector<int> >& adj_matr, int size);
	bool check_adj_matr_symm(vector<vector<int> >& adj_matr, int size);

public:
	my_graph(string filename);

	void print();
};

