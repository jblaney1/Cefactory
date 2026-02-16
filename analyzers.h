#ifndef ANALYZERS_H
#define ANALYZERS_H

#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::unique_ptr<Analyzer> get_analyzer_type(const std::string& file_name);
std::string get_extension(const std::string& file_name);

struct Node {
    std::string name;
    std::vector<std::string> connections;
    std::vector<std::string> dependecies;
    std::vector<std::string> complexities;
};

class Analyzer {
    public:
        Analyzer() = default;

        Node get_node();
        void load_code();
        void save_report();
        std::string save_report_helper(const std::vector<std::string> vec);

        void virtual analyze_code();
        void virtual compute_complexity();

        Node node;
        std::vector<std::string> code;
};

class Python_Analyzer : public Analyzer {
    public:
        Python_Analyzer(std::string name);

        void analyze_code() override;
        void compute_complexity() override;
};

#endif