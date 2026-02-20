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

std::unordered_map<std::string, std::string> Analyzer::get_complexities(){
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
        this->node.code_length = this->code.size();
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
            message += "Complexities: " + this->save_report_helper(this->node.complexities) + "\n";

            message += "Length of Code: " + std::to_string(this->node.code_length) + "\n";
            message += "Single Line Comments: "  + this->save_report_helper(this->node.sl_comments) + "\n";
            message += "Multi Line Comments: "  + this->save_report_helper(this->node.ml_comments) + "\n"; 

            file << message;
            file.close();
        }
    }
    catch (const std::exception& error){
        std::cout << "An error occurred";
    }
}

std::string Analyzer::save_report_helper(const std::vector<int>& vec){
    std::string line = "";

    for (auto& entry : vec) {
        line += std::to_string(entry) + " | ";
    }

    return line;
}

std::string Analyzer::save_report_helper(const std::vector<std::string>& vec){
    std::string line = "";

    for (auto& entry : vec) {
        line += entry + " | ";
    }

    return line;
}

std::string Analyzer::save_report_helper(const std::unordered_map<std::string, std::string>& vec){
    std::string line = "\n";

    line += "\t key \t|\t entry \n";
    for (auto& [key, entry] : vec) {
        line += "\t" + key + " \t|\t " + entry + "\n";
    }

    return line;
}

std::string convert_extension(const std::string file_name){
    auto pos = file_name.find_last_of('.');
    return (pos != std::string::npos) ? file_name.substr(pos+1) : file_name;
}

bool find_element(const std::vector<std::string>& vec, const std::string element){
    return std::find(vec.begin(), vec.end(), element) != vec.end();
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

/*

*/

Python_Analyzer::Python_Analyzer(std::string name) { this->node.name = name; }

void Python_Analyzer::analyze_code(std::vector<std::string>& included_files){
    size_t from_pos, import_pos, as_pos;
    int index = 1;
    bool in_comment = false;
    std::string file_name;
    std::unordered_map<std::string, std::string> aliases;

    for (std::string& line : this->code){
        if (line.find_first_of("\"\"\"") != std::string::npos) {
            in_comment != in_comment;
            this->node.ml_comments.push_back(index);
        }

        if (~in_comment){
            if (line.find_first_of('#') != std::string::npos) {
                this->node.sl_comments.push_back(index);
            }
            else{
                as_pos = line.find_first_of("as");
                from_pos = line.find_first_of("from");
                import_pos = line.find_first_of("import");

                if (from_pos != std::string::npos){
                    file_name = line.substr(from_pos+1, import_pos-1) + '\\' + line.substr(import_pos+1, as_pos-1) + ".py";
                    if (find_element(included_files, file_name)){
                        this->node.connections.push_back(file_name);
                        (as_pos != std::string::npos) ? aliases[file_name] = line.substr(as_pos+1) : aliases[file_name] = file_name;
                    }
                }
                else if (import_pos != std::string::npos){
                    file_name = line.substr(import_pos+1, as_pos-1) + ".py";
                    if (find_element(included_files, file_name)){
                        this->node.connections.push_back(file_name);
                        (as_pos != std::string::npos) ? aliases[file_name] = line.substr(as_pos+1) : aliases[file_name] = file_name;
                    }
                }
                else{
                    for (auto& [connection, alias] : aliases){
                        if (line.find_first_of(alias)){
                            this->node.dependecies.push_back(connection);
                        }
                    }
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

void HTML_Analyzer::analyze_code(std::vector<std::string>& included_files){

}

void HTML_Analyzer::compute_complexity(){

}