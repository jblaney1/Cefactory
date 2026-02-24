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

std::unordered_map<std::string, std::vector<std::string>> Analyzer::get_complexities(){
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

std::string Analyzer::save_report_helper(const std::unordered_map<std::string, std::vector<std::string>>& map){
    std::string line = "\n\t file \n\t\t entry : complexity \n";

    for (auto& [file, vec] : map) {
        line += "\n\t" + file;
        for (auto& entry : vec){
            line += "\n\t\t" + entry + "\n";
        }
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

int find_index(const std::vector<std::string>& vec, const std::string element){
    return std::distance(vec.begin(), std::find(vec.begin(), vec.end(), element));
}

std::vector<std::string> split_string(const std::string line, const std::string delimitor){
    std::vector<std::string> words;
    size_t it_current = 0, it_previous = 0;

    if (line.find(delimitor) != std::string::npos){
        while((it_current = line.find(delimitor, it_current+1)) != std::string::npos){
            words.push_back(line.substr(it_previous, it_current-it_previous));
            it_previous = it_current+1;
        }
        words.push_back(line.substr(it_previous, it_current-it_previous));
    }
    else{
        words.push_back(line);
    }

    return words;
}

std::vector<std::string> process_white_space(const std::string line){
    std::vector<std::string> words;

    words = split_string(line, " ");
    if (words.back().find("\n") != std::string::npos){
        if (words.back() == "\n"){
            words.pop_back();
        }
        else {
            words.back() = words.back().substr(0, words.back().size()-3);
        }
    }

    return words;
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

void Python_Analyzer::analyze_code(const std::string base_path, const std::vector<std::string>& included_files){
    int index = 1;
    std::string file_name;
    bool in_comment = false;
    std::vector<std::string> words;
    size_t from_pos, import_pos, as_pos, alias_pos;
    std::unordered_map<std::string, std::string> aliases;

    for (std::string& line : this->code){
        if (line.find("\"\"\"") != std::string::npos) {
            in_comment = !in_comment;
            this->node.ml_comments.push_back(index);
        }
        else if (!in_comment && !line.empty()){
            words = process_white_space(line);
            if (words[0] == "#") {
                this->node.sl_comments.push_back(index);
            }
            else{
                if (line.find('#') != std::string::npos) {
                    this->node.sl_comments.push_back(index);
                }

                as_pos = (find_element(words, "as")) ? find_index(words, "as") : std::string::npos;
                from_pos = (find_element(words, "from")) ? find_index(words, "from") : std::string::npos;
                import_pos = (find_element(words, "import")) ? find_index(words, "import") : std::string::npos;
                

                if (from_pos != std::string::npos){
                    file_name = words[from_pos + 1] + '/' + words[import_pos + 1];
                    this->node.connections.push_back(file_name);
                    file_name = base_path + file_name + ".py";

                    if (find_element(included_files, file_name)){
                        aliases[file_name] = (as_pos != std::string::npos) ? words[as_pos + 1] : words[import_pos + 1];
                    }
                }
                else if (import_pos != std::string::npos){
                    file_name = words[import_pos + 1];
                    this->node.connections.push_back(file_name);
                    file_name = base_path + file_name + ".py";
                    std::cout << file_name << std::endl;
                    if (find_element(included_files, file_name)){
                        aliases[file_name] = (as_pos != std::string::npos) ? words[as_pos + 1] : words[import_pos + 1];                    
                    }
                }
                else{
                    for (auto& [key, alias] : aliases){
                        if (find_element(words, alias)){
                            if (!find_element(this->node.dependecies, key)){
                                this->node.dependecies.push_back(key);
                                this->node.complexities[key] = std::vector<std::string>(); 
                            }
                            alias_pos = find_index(words, alias);
                            if (!find_element(this->node.complexities[key], words[])){
                                this->node.complexities[key].push_back(words[]);
                            }
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

void HTML_Analyzer::analyze_code(const std::string base_path, const std::vector<std::string>& included_files){

}

void HTML_Analyzer::compute_complexity(){

}