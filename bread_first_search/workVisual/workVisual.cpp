#include "workVisual.h"

workVisual::workVisual(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
}

void workVisual::makeDots()
{
    std::vector<std::vector<int>> matr = {
        {1, 0, 1, 1, 1},
        {0, 1, 0, 1, 0},
        {1, 0, 1, 0, 1},
        {1, 1, 0, 1, 0},
        {1, 0, 1, 0, 1}
    };
    std::vector<int> was = { 2, 1, 0, 4, 3 };
    order = was;
    std::vector<Edge> used_by = getPairs(matr);
    curr = 0;
    std::vector<std::string> name;
    for (int i = 0; i < matr.size(); i++) {
        name.push_back(std::to_string(i + 1));
    }
    
    const int nedges = used_by.size();
    int weights[1000];
    std::fill(weights, weights + nedges, 1);

    Graph g(used_by.begin(), used_by.end(), weights, matr.size());
    std::vector<int> color;
    for (int i = 0; i < was.size(); i++) {
        std::string num = std::to_string(i);
        color.push_back(was[i]);
        std::ofstream file("out" + num + ".dot");
        boost::write_graphviz(file, g, vertex_color_writer(g, color), edge_color_writer(g, color));
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
