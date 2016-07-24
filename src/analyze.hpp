#pragma once

#include <array>
#include <string>
#include <vector>

#include "process.hpp"

Matrix<int, 26, 26> count_digrams(std::vector<std::string> in);
Matrix<int, 26, 26> count_digrams(std::string in);
