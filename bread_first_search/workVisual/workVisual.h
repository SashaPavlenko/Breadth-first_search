#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_workVisual.h"
#include <string>
#include <vector>

typedef std::pair<int, int> Edge;

#include "boost/graph/graphviz.hpp"

class workVisual : public QMainWindow
{
    Q_OBJECT

public:
    workVisual(QWidget *parent = Q_NULLPTR);

    void makeDot();

private:
    Ui::workVisualClass ui;

    std::vector<Edge> getPairs(std::vector<std::vector<int>> adj_matr);
};
