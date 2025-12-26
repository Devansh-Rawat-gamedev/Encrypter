#pragma once
#include <fstream>
#include <string>
#include <iostream>

class IO{
    public:
     IO(const std::string& filePath);
     ~IO();
     std::fstream getFileStream();
     private:
     std::fstream file_stream;
};
