#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "process.hpp"
#include "analyze.hpp"
#include "file.hpp"

int main(int argc, char const *argv[]) {
    std::string filename = std::string(argv[1]);
    std::string raw = read(filename);

    std::vector<std::string> parsed = parse(raw);
    alpha_only(raw);
    //std::cout << raw << std::endl;
    Matrix<int, 26, 26> count;
    count = count_digrams(raw);
    print2d(count);
    std::cout << "----------------------------------------------------" << std::endl;
    count = count_digrams(parsed);
    print2d(count);
    return 0;
}
