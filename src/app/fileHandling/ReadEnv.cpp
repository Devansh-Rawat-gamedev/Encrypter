#include <iostream>
#include <string>
#include <fstream>
#include "IO.hpp"
#include <sstream>

class ReadEnv{
    public:
    std::string getenv(){
        std::string env_path =".env";
        IO io(env_path);
        std::fstream file_stream = io.getFileStream();
        std::stringstream buffer;
        buffer <<file_stream.rdbuf();
        std::string content = buffer.str();
        return content;
    }
};