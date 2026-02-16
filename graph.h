#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

#include "analyzers.h"

class Graph{
private:
    std::string name;
    std::string base_file;
    std::string base_path;
    std::vector<Node> nodes;
    std::vector<std::string> node_names;

    Node populate_graph_recursive(const std::string node_name);
    
public:
    Graph(std::string graph_name, std::string path, std::string file);
    void populate_graph();
    void save_report();
};

#endif