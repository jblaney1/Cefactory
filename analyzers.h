#ifndef ANALYZERS_H
#define ANALYZERS_H

#include <string>
#include <unordered_map>

struct Report {
    std::string name;
    std::unordered_map<std::string, int> stats;
    std::unordered_map<std::string, std::vector<std::string>> keys;
    std::unordered_map<std::string, std::vector<std::string>> connections;
};

class Analyzer {
    public:
        Analyzer() = default;

        void virtual compute_complexity_helper() = 0;
        void virtual get_next_node_helper() = 0;
        void virtual set_nodes_helper() = 0;

        void compute_complexity();
        void get_next_node();
        void load_code(std::string file_name);
        std::string save_report_helper(const std::unordered_map<std::string, std::vector<std::string>>& map);
        void save_report();
        void set_nodes();

        Report report;
        std::vector<std::string> code;
};

class Python_Analyzer : public Analyzer {
    public:
        Python_Analyzer(std::string name);
        void compute_complexity_helper() override;
        void get_next_node_helper() override;
        void set_nodes_helper() override;
};

#endif