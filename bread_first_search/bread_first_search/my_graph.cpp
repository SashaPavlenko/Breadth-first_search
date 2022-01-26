#include "my_graph.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "MyFileExceptions.h"

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

my_graph::my_graph(string filename)
{
	cout << this->solve_size(filename);
}
