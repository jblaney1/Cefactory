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

#include <iostream>
#include <fstream>
#include <string>


#include "common.h"
#include "analyzers.h"

void Analyzer::compute_complexity(){

}

void Analyzer::get_next_node(){

}

void Analyzer::load_code(std::string file_name){
    try{
        std::string line;
        std::ifstream file(file_name);
        while (std::getline(file, line)){
            this->code.push_back(line);
        }
        file.close();
    }
    catch (const std::exception& error){
        log_error("load_code", error.what());
    }
}

std::string Analyzer::save_report_helper(const std::unordered_map<std::string, std::vector<std::string>>& map){
    std::string line = "";
    std::string lines = "";

    for (auto& [key, values] : map) {
        line = key + ": ";
        for (auto& value : values){
            line = line + value + ", ";
        }
        lines = lines + line + "\n";
    }

    return lines;
}

void Analyzer::save_report(){
    try{
        std::string stats = "";
        std::ofstream file("C:\\Users\\RadBo\\Documents\\Repositories\\Cefactory\\" + this->report.name + ".txt");

        if (file.is_open()) {
            for (auto& [key, value] : this->report.stats) {
                stats = stats + key + ": " + std::to_string(value) + "\n";
            }

            file << stats;
            file << this->save_report_helper(this->report.keys);
            file << this->save_report_helper(this->report.connections);
            file.close();
        }
    }
    catch (const std::exception& error){
        log_error("load_code", error.what());
    }
}

void Analyzer::set_nodes(){
    std::vector<int> stats;
    std::vector<std::string> keys;
    std::vector<std::string> connections;

    for (int j = 1; j < 2000; j++) {
        this->report.stats[std::to_string(j)] = 2*j;
    }

    for (int j = 10; j < 100; j++) {
        for (int i = j * 2; i < 5000; i++) { keys.push_back(std::to_string(i)); }
        this->report.keys[std::to_string(j)] = keys;
        keys.clear();
    }

    for (int j = 10; j < 200; j++) {
        for (int i = j * 3; i < 6000; i++) { connections.push_back(std::to_string(i)); }
        this->report.connections[std::to_string(j)] = connections;
        connections.clear();
    }
}

/*

*/
Python_Analyzer::Python_Analyzer(std::string name) { this->report.name = name; }
void Python_Analyzer::compute_complexity_helper(){

}

void Python_Analyzer::get_next_node_helper(){

}

void Python_Analyzer::set_nodes_helper(){

}