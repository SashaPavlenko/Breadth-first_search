#include "my_graph.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "MyFileExceptions.h"
#include <vector>

int my_graph::solve_size(string filename)
{
	int columns{ 0 };
	string str;

	ifstream fin(filename, ios_base::in);
	

	// Ошибка: не открыт файл.
	if (!fin.is_open())
		throw MyFileExceprion("File is not open!");

	getline(fin, str);
	columns = count(begin(str), end(str), ' ');
	++columns;
	
	int rows{ 1 };
	while (getline(fin, str)) {
		rows++;
	}
	
	fin.close();

	// Ошибка: некорректно задана матрица смежности
	if (columns != rows) {
		throw MyFileExceprion("IncorrectMatrix");
	}

	return columns;
}

void my_graph::read_matrix(string filename, vector<vector<int>	>& adj_matr, int size)
{
	ifstream fin(filename);

	int index{ 0 };
	while (!fin.eof()) {
		adj_matr.push_back(vector<int>(size));
		copy_n(istream_iterator<int>(fin), size, begin(adj_matr[index]));
		
		++index;
	}

	// Ошибка: матрица симметричности не удовлетворяет условию симметричности и диагонали из нулевых элементов.
	if (!this->check_adj_matr_symm(adj_matr, size)) {
		throw MyFileExceprion("IncorrectDataFile");
	}
}

bool my_graph::check_adj_matr_symm(vector<vector<int>>& adj_matr, int size)
{
	bool flag{ true };

	int i{ 0 }, j;
	while (flag && i < size-1)
	{
		j = i + 1;
		while (flag && j < size) {
			flag = adj_matr[i][j] == adj_matr[j][i];
			++j;
		}

		++i;
	}

	i = 0;
	while (flag && i < size) {
		flag = adj_matr[i][i] == 0;
		++i;
	}

	return flag;
}

my_graph::my_graph(string filename)
{
	this->size = this->solve_size(filename);
	this->read_matrix(filename, this->adj_matr, this->size);
}

void my_graph::print()
{
	for (int i = 0; i < this->size; ++i) {
		for (int j = 0; j < this->size; ++j) {
			cout << adj_matr[i][j] << " ";
		}
		cout << endl;
	}
}
