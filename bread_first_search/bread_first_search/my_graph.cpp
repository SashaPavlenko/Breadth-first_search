#include "my_graph.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include "MyFileExceptions.h"

int my_graph::solve_size(string filename)
{
	int k{ 0 };
	string str;

	ifstream fin(filename);
	

	// Ошибка: не открыт файл.
	if (!fin.is_open())
		throw MyFileExceprion("File is not open!");

	getline(fin, str);
	k = count(begin(str), end(str), ' ');

	fin.close();
	return k;
}

my_graph::my_graph(string filename)
{
	cout << this->solve_size(filename);
}
