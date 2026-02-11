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

#include "common.h"
#include "analyzers.h"

int main() {
    std::string project_name = "test";
    Python_Analyzer python_analzyer(project_name);
    python_analzyer.set_nodes();
    python_analzyer.save_report();

    return 0;
}