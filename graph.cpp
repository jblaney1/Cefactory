/*
 * Copyright the Refactory Group LLC 2026
 *
 * Author(s):
 * Version:
 * Date:
 *
 * Description:
 *
 *
 * Dependencies
 *
 *
 * Classes:
 *
 *
 * Functions:
 *
*/

#include "graph.h"

bool find_element(const std::vector<std::string>& vec, const std::string element){
    return std::find(vec.begin(), vec.end(), element) != vec.end();
}

Graph::Graph(std::string graph_name, std::string path, std::string file) : name(graph_name), base_path(path), base_file(file){}

void Graph::populate_graph(){
    this->nodes.push_back(this->populate_graph_recursive(this->base_path + this->base_file));
}

/*
 * Graph::populate_graph_recursive()
 * A function in that recursively builds a call graph by gathering all nodes
 * connected to the current node down until there are no more available
 * connected nodes that the program can find. Then when processing back up
 * the call graph, the computational complexity of the previously returned
 * analyzer reports in conjunction with the current functions complexity.
 * 
 * 1. Create and populate a new analyzer object for this call
 * 2. Get the next node and path to the file
 * 3. If there are more nodes, make another recursive call
 * 4. Compute the complexity for the current node
 * 5. Return the report of the current node
 * 
 * inputs:
 *  - node:
 *  - path:
 * outputs:
 *  - Node: 
*/
Node Graph::populate_graph_recursive(const std::string node_name){
    auto analyzer = get_analyzer_type(node_name);
    analyzer->load_code();
    analyzer->analyze_code();

    //for (auto& dependency : analyzer->get_dependencies()){
    //   if (~find_element(this->node_names, dependency)){
    //        this->node_names.push_back(dependency);
    //        this->nodes.push_back(this->populate_graph_recursive(dependency));
    //    }
    //}

    analyzer->compute_complexity();
    for (auto& entry : analyzer->get_node().sl_comments){
        std::cout << entry << std::endl;
    }

    return analyzer->get_node();
}

void Graph::save_report(){
    try{
        std::string message;
        std::ofstream file(this->name + ".txt");

        if (file.is_open()) {
            message = "Name: " + this->name + "\n";
            message += "Path: " + this->base_path + "\n";
            message += "File: " + this->base_file + "\n";
            

            file << message;
            file.close();
        }
    }
    catch (const std::exception& error){
        std::string message = "";
    }
}