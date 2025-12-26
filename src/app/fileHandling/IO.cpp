#include <fstream>
#include <iostream>
#include "IO.hpp"

IO::IO(const std::string& filePath){
    file_stream.open(filePath, std::ios::in | std::ios::out | std::ios::binary);
    if (!file_stream.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
    }
}

std::fstream IO::getFileStream(){
    return std::move(file_stream);
}

IO::~IO(){
    if (file_stream.is_open()) {
        file_stream.close();
    }
}