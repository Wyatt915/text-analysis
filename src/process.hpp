#pragma once

#include <array>
#include <string>
#include <vector>

template <class T, unsigned I, unsigned J>
using Matrix = std::array<std::array<T, J>, I>;

std::vector<std::string> parse(std::string message);
void alpha_only(std::string& in);
void capitalize(std::string& in);
void print_list(const std::vector<std::string>& in);
void remove_p(std::string& in);
void print2d(const Matrix<int, 26, 26>& in);
