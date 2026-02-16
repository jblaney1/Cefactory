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

#include <string>

#include "graph.h"

int main() {
    std::string name = "test";
    std::string path = "../Refactory/";
    std::string file = "analyzers.py";

    Graph graph(name, path, file);
    graph.populate_graph();
    //graph.save_report();

    return 0;
}