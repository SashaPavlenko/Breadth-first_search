#include <queue>
#include <iostream>
#include <string>
#include "bread_first_search/my_graph.h"
#include "bread_first_search/MyFileExceptions.h"

const int PEAKS = 5;

int main() {
    // ������ �����.
    try
    {
        // �������������.
        std::string str{ "test_adj_matrix.txt" };
        my_graph t(str);
        
        // ������ �� �����.
        t.print();
        cout << endl;

        // ������ ������.
        auto peaks = t.bread_first_search();
        for (auto i : peaks) {
            cout << i+1 << " ";
        }
    }
    catch (MyFileExceprion& exception) {
        cerr << "Exception: " << exception.what() << endl;
    }
    catch (const std::exception& exception) {

        std::cerr << "Standard exception: " << exception.what() << endl;
    }
    //*/

    return 0;
}