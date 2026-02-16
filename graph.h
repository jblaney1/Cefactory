#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <memory>
#include <vector>
#include <fstream>

#include "analyzers.h"

std::string get_extension(const std::string& file_name);
bool find_element(const std::vector<std::string>& vec, const std::string& element);

class Graph{
private:
    std::string name;
    std::string base_file;
    std::string base_path;
    std::vector<Node> nodes;
    std::vector<std::string> node_names;

    Node populate_graph_recursive(std::string node_name);
    
public:
    Graph(std::string graph_name, std::string path, std::string file);
    void populate_graph();
    void save_report();
};

#endif