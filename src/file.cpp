#include "file.hpp"

#include <fstream>
#include <sstream>

std::string read(std::string filename){
    std::string line;
    std::stringstream data;
    std::ifstream infile(filename.c_str());
    if(infile.is_open()){
        while(std::getline(infile,line)){
            data << line;
        }
        infile.close();
    }
    return data.str();
}

void write(std::string filename, std::string data){
    std::ofstream outfile (filename, std::ios::out);
    if(outfile.is_open()) {
        outfile << data;
        outfile.close();
    }
}
