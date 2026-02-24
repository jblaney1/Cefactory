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
#include <filesystem>

#include "graph.h"

std::vector<std::string> get_included_files(std::string base_path){
    std::vector<std::string> file_list;

    for (auto& entry : std::filesystem::recursive_directory_iterator(base_path)){
        if (std::filesystem::is_regular_file(entry.path())){
            file_list.push_back(entry.path().string());
        }
    }
    
    return file_list;
}

int main() {
    std::string name = "test";
    std::string path = "../Refactory/";
    std::string file = "graph.py";
    //std::string path = "../An-Evaluation-of-Deep-Learning-Models-for-Classifying-Individual-Data-Instances-in-Time-Series/";
    //std::string file = "ann_tester.py";
    std::vector<std::string> file_list;

    file_list = get_included_files(path);

    Graph graph(name, path, file, file_list);
    graph.populate_graph();
    //graph.save_report();

    return 0;
}