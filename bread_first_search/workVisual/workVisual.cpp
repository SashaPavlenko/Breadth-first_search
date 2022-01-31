#include "workVisual.h"

workVisual::workVisual(my_graph _graph, QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    adj_matr = _graph.get_adj_matr();
    order = _graph.bread_first_search();
    edges = _graph.get_edges();
    curr = 0;
}

void workVisual::makeDots()
{
    std::vector<std::vector<int>> matr = adj_matr;
    std::vector<int> was = order;
    std::vector<Edge> used_by = getPairs(matr);
    std::vector<std::string> name;
    for (int i = 0; i < matr.size(); i++) {
        name.push_back(std::to_string(i + 1));
    }
    
    const int nedges = used_by.size();
    int weights[1000];
    std::fill(weights, weights + nedges, 1);

    Graph g(used_by.begin(), used_by.end(), weights, matr.size());
    std::vector<int> color;
    std::vector<std::pair<int, int>> color_edge;
    for (int i = 0; i < was.size(); i++) {
        if (i != 0) {
            color_edge.push_back(edges[i - 1]);
        }
        std::string num = std::to_string(i);
        color.push_back(was[i]);
        std::ofstream file("out" + num + ".dot");
        boost::write_graphviz(file, g, vertex_color_writer(g, color), edge_color_writer(g, color_edge));
        file.close();
        num = "dot -Tpng out" + num + ".dot -o output" + num + ".png";
        std::cout << system(num.c_str());
    }

}

void workVisual::setImageLabel(const std::string& img)
{
    QPixmap pixmap(img.c_str());
    ui.imageLabel->setPixmap(pixmap);
    ui.imageLabel->show();
}

void workVisual::next_img()
{
    if (curr == order.size() - 1) {
        return;
    }
    curr++;
    setImageLabel("output" + std::to_string(curr) + ".png");
}

void workVisual::prev_img()
{
    if (curr == 0) {
        return;
    }
    curr--;
    setImageLabel("output" + std::to_string(curr) + ".png");
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
