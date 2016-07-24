#include "process.hpp"

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>

void alpha_only(std::string& in){
    remove_p(in);
    auto new_end = std::remove_if(begin(in), end(in), [] (const char& c) { return !(std::isalpha(c)); });
    in.erase(new_end, end(in));
}

void capitalize(std::string& in){
    for (size_t i = 0; i < in.length(); i++){
        if (in[i] >= 'a' && in[i] <= 'z'){
            in[i] = (in[i] - 'a') + 'A';	//to upper case
        }
    }
}

//remove punctuation
void remove_p(std::string& in){
    capitalize(in);
    std::remove_if(begin(in), end(in), [](const char& c) { return c == '\''; });
    std::replace_if(begin(in), end(in),
        [] (const char& c) { return std::ispunct(c); }, ' ');
}

bool consecutive_spaces(char lhs, char rhs){ return (lhs == rhs) && (lhs == ' '); }

std::vector<std::string> parse(std::string message){
    remove_p(message);
    //remove consecutive spaces
    auto new_end = std::unique(message.begin(), message.end(), consecutive_spaces);
    message.erase(new_end, message.end());

    std::vector<std::string> out;
    std::string temp;
    std::stringstream sst(message);
    while (sst >> temp){
        //each word is its own array element.
        out.push_back(temp);
    }
    return out;
}

void print_list(const std::vector<std::string>& in){
    for (std::string elem : in){
        std::cout << elem << ' ';
    }
    std::cout << std::endl;
}

//[row][col]
void print2d(const Matrix<int, 26, 26>& in){
    for (size_t i = 0; i < 26; i++) {
        for (size_t j = 0; j < 26; j++) {
            in[i][j] == 0 ? std::cout << "  " : std::cout << in[i][j] << ' ';
        }
        std::cout << std::endl;
    }
}
