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

#include "analyzers.h"

std::vector<std::string> Analyzer::get_complexities(){
    return this->node.complexities;
}

std::vector<std::string> Analyzer::get_connections(){
    return this->node.connections;
}

std::vector<std::string> Analyzer::get_dependencies(){
    return this->node.dependecies;
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
        std::cout << "An error occurred";
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
        std::cout << "An error occurred";
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
    size_t pos;
    int index = 1;
    bool in_comment = false;
    for (std::string_view line : this->code){
        if (line.find_first_of("\"\"\"") != std::string::npos) {
            in_comment != in_comment;
            this->node.ml_comments.push_back(index);
        }

        if (~in_comment){
            if (line.find_first_of('#') != std::string::npos) {
                this->node.sl_comments.push_back(index);
            }
            else{
                pos = line.find_first_of("from");
                if (pos != std::string::npos){

                }
                else{
                    
                }
            }
        }

        index += 1;
    }
}

void Python_Analyzer::compute_complexity(){

}


/*

*/

HTML_Analyzer::HTML_Analyzer(std::string name) { this->node.name = name; }

void HTML_Analyzer::analyze_code(){

}

void HTML_Analyzer::compute_complexity(){

}

std::string convert_extension(const std::string file_name){
    auto pos = file_name.find_last_of('.');
    return (pos != std::string::npos) ? file_name.substr(pos+1) : file_name;
}

std::unique_ptr<Analyzer> get_analyzer_type(const std::string file_name){
    std::string file_extension = convert_extension(file_name);
    
    if (file_extension == "py"){
        return std::make_unique<Python_Analyzer>(file_name);
    }
    else if (file_extension == "html"){
        return std::make_unique<HTML_Analyzer>(file_name);
    }
    else{
        throw std::invalid_argument("Unknown Analyzer Type: " + file_extension);
    }
}