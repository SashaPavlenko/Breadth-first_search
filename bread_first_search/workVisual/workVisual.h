#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_workVisual.h"
#include <string>
#include <vector>
#include <iostream>
#include "boost/graph/graphviz.hpp"
#include "boost/graph/sequential_vertex_coloring.hpp"
#include "../bread_first_search/my_graph.h"


typedef std::pair<int, int> Edge;
typedef boost::adjacency_list< boost::vecS, boost::vecS, boost::undirectedS,
    boost::property< boost::vertex_color_t, boost::default_color_type >,
    boost::property< boost::edge_weight_t, int >
> Graph;
typedef boost::graph_traits<Graph>::vertex_descriptor vertex_descriptor;
typedef boost::graph_traits<Graph>::vertices_size_type vertices_size_type;
typedef boost::property_map<Graph, boost::vertex_index_t>::const_type vertex_index_map;



class workVisual : public QMainWindow
{
    Q_OBJECT

public:
    workVisual(my_graph _graph, QWidget *parent = Q_NULLPTR);

    void makeDots();

    void setImageLabel(const std::string& img);

public slots:
    void next_img();

    void prev_img();

private:
    Ui::workVisualClass ui;
    std::vector<std::vector<int>> adj_matr;
    std::vector<int> order;
    std::vector<std::pair<int, int>> edges;
    int curr;

    std::vector<Edge> getPairs(std::vector<std::vector<int>> adj_matr);
};

//  define a property writer to color the edges as required
class vertex_color_writer {
public:

    // constructor - needs reference to graph we are coloring
    vertex_color_writer(Graph& g, const std::vector<int>& _whatColor) : myGraph(g), whatColor(_whatColor) {}

    // functor that does the coloring
    template <class VertexOrEdge>
    void operator()(std::ostream& out, const VertexOrEdge& e) const {

        // check if this is the edge we want to color red

        typedef boost::property_map<Graph, boost::vertex_index_t>::type IndexMap;
        IndexMap index = get(boost::vertex_index, myGraph);
        for (auto i : whatColor) {
            if (i == index[e]) {
                out << "[color=red]";
            }
        }
    }
private:
    Graph& myGraph;
    std::vector<int> whatColor;
};

class edge_color_writer {
public:

    // constructor - needs reference to graph we are coloring
    edge_color_writer(Graph& g, const std::vector<std::pair<int, int>>& _whatColor) : myGraph(g), whatColor(_whatColor) {}

    // functor that does the coloring
    template <class VertexOrEdge>
    void operator()(std::ostream& out, const VertexOrEdge& e) const {

        // check if this is the edge we want to color red
        int color_ = 0;
        for (auto i : whatColor) {
            if (boost::target(e, myGraph) == i.first && boost::source(e, myGraph) == i.second ||
                boost::target(e, myGraph) == i.second && boost::source(e, myGraph) == i.first)
                out << "[color=red]";
        }
    }
private:
    Graph& myGraph;
    std::vector<std::pair<int, int>> whatColor;
};
