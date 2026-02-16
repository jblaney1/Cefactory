#ifndef ANALYZERS_H
#define ANALYZERS_H

#include <memory>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Node {
    std::string name;
    std::vector<int> sl_comments;
    std::vector<int> ml_comments;
    std::vector<std::string> connections;
    std::vector<std::string> dependecies;
    std::vector<std::string> complexities;
};

class Analyzer {
    public:
        Node node;
        std::vector<std::string> code;

        Analyzer() = default;

        Node get_node();
        std::vector<std::string> get_connections();
        std::vector<std::string> get_dependencies();
        std::vector<std::string> get_complexities();

        void load_code();
        void save_report();
        std::string save_report_helper(const std::vector<std::string> vec);

        virtual void analyze_code() = 0;
        virtual void compute_complexity() = 0;

        virtual ~Analyzer() = default;
};

class Python_Analyzer : public Analyzer {
    public:
        Python_Analyzer(std::string name);

        void analyze_code() override;
        void compute_complexity() override;

        ~Python_Analyzer() = default;
};

class HTML_Analyzer : public Analyzer {
    public:
        HTML_Analyzer(std::string name);

        void analyze_code() override;
        void compute_complexity() override;

        ~HTML_Analyzer() = default;
};

std::unique_ptr<Analyzer> get_analyzer_type(const std::string file_name);

#endif