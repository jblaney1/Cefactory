#ifndef ANALYZERS_H
#define ANALYZERS_H

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>


struct Node {
    int code_length;
    std::string name;
    std::vector<int> sl_comments;
    std::vector<int> ml_comments;
    std::vector<std::string> connections;
    std::vector<std::string> dependecies;
    std::unordered_map<std::string, std::string> complexities;
};

class Analyzer {
    protected:
        Node node;
        std::vector<std::string> code;

    public:
        Analyzer() = default;

        std::unordered_map<std::string, std::string> get_complexities();
        std::vector<std::string> get_connections();
        std::vector<std::string> get_dependencies();
        Node get_node();

        void load_code();
        void save_report();
        std::string save_report_helper(const std::vector<int>& vec);
        std::string save_report_helper(const std::vector<std::string>& vec);
        std::string save_report_helper(const std::unordered_map<std::string, std::string>& vec);

        virtual void analyze_code(std::vector<std::string>& included_files) = 0;
        virtual void compute_complexity() = 0;

        virtual ~Analyzer() = default;
};

bool find_element(const std::vector<std::string>& vec, const std::string element);
std::unique_ptr<Analyzer> get_analyzer_type(const std::string file_name);

class Python_Analyzer : public Analyzer {
    public:
        Python_Analyzer(std::string name);

        void analyze_code(std::vector<std::string>& included_files) override;
        void compute_complexity() override;

        ~Python_Analyzer() = default;
};

class HTML_Analyzer : public Analyzer {
    public:
        HTML_Analyzer(std::string name);

        void analyze_code(std::vector<std::string>& included_files) override;
        void compute_complexity() override;

        ~HTML_Analyzer() = default;
};

#endif