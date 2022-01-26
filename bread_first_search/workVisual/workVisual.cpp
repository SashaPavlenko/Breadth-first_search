#include "workVisual.h"

workVisual::workVisual(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void workVisual::makeDot()
{
    std::vector<std::vector<int>> matr = {
        {1, 0, 1, 1, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {1, 0, 1, 0, 1}
    };
    std::vector<Edge> used_by = getPairs(matr);
    std::vector<std::string> name;
    for (int i = 0; i < matr.size(); i++) {
        name.push_back(std::to_string(i + 1));
    }
    
    const int nedges = used_by.size();
    int weights[1000];
    std::fill(weights, weights + nedges, 1);


    typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS,
        boost::property< boost::vertex_color_t, boost::default_color_type >,
        boost::property< boost::edge_weight_t, int >
    > Graph;
    Graph g(used_by.begin(), used_by.end(), weights, matr.size());
    std::ofstream file("out.dot");
    boost::write_graphviz(file, g, boost::make_label_writer(name.data()));
    file.close();
}

std::vector<Edge> workVisual::getPairs(std::vector<std::vector<int>> adj_matr)
{
    std::vector<Edge> pairs;
    for (int i = 0; i < adj_matr.size(); i++) {
        for (int j = i; j < adj_matr.size(); j++) {
            if (i != j && adj_matr[i][j] == 1) {
                pairs.push_back(Edge(i, j));
            }
        }
    }
    return pairs;
}
