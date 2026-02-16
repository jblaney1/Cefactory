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

#include "common.h"
#include "analyzers.h"

std::unique_ptr<Analyzer> get_analyzer_type(const std::string& file_name){
    std::string file_extension = get_extension(file_name);

    if (file_extension == "py"){
        return std::make_unique<Python_Analyzer>(file_name);
    }
    else{
        return nullptr;
    }
}

std::string get_extension(const std::string& file_name){
    std::string extension = "";

    for (int i = file_name.size() - 1; i > 0; i--){
        if (file_name[i] == '.') { break; }
        else{ extension = file_name[i] + extension; }
    }

    return extension;
}

Node Analyzer::get_node(){
    return this->node;
}

void Analyzer::load_code(){
    try{
        std::string line;
        std::ifstream file(this->node.name);
        while (std::getline(file, line)){
            this->code.push_back(line);
        }
        file.close();
    }
    catch (const std::exception& error){
        log_error("load_code", error.what());
    }
}

void Analyzer::save_report(){
    try{
        std::string message;
        std::string connections;
        std::ofstream file(this->node.name + ".txt");

        if (file.is_open()) {
            message = "Name: " + this->node.name + "\n";
            message += "Connections: " + this->save_report_helper(this->node.connections) + "\n";
            message += "Dependencies: " + this->save_report_helper(this->node.dependecies) + "\n";

            file << message;
            file.close();
        }
    }
    catch (const std::exception& error){
        log_error("load_code", error.what());
    }
}

std::string Analyzer::save_report_helper(const std::vector<std::string> vec){
    std::string line = "";

    for (auto& entry : vec) {
        line += entry + " | ";
    }

    return line;
}


/*

*/

Python_Analyzer::Python_Analyzer(std::string name) { this->node.name = name; }

void Python_Analyzer::analyze_code(){
    for (int j = 10; j < 100; j++) {
        this->node.dependecies.push_back(std::to_string(j));
    }

    for (int j = 10; j < 200; j++) {
        this->node.connections.push_back(std::to_string(j));
    }
}

void Python_Analyzer::compute_complexity(){

}