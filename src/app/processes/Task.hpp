#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include "../fileHandling/IO.hpp"

enum class Action{
    Encrypt,
    Decrypt,

};

struct Task{
    std::string filePath;
    std::fstream fileStream;
    Action action;
    Task(std::fstream&& stream, const std::string& path, Action act)
        : fileStream(std::move(stream)), filePath(path), action(act) {}

    std::string toString(){
        std::ostringstream oss;
        oss<<filePath<<","<<(action ==Action::Encrypt ? "Encrypt" :"Decrypt");
            return oss.str();
    }

    static Task fromString(const std::string& taskData){
        std::istringstream iss(taskData);
        std::string filePath;
        std::string actionStr;
        std::getline(iss, filePath, ',');
        std::getline(iss, actionStr);
        
        if(std::getline(iss,filePath,',') && std::getline(iss,actionStr)){
            Action action = actionStr == "Encrypt" ? Action::Encrypt :
                actionStr == "Decrypt" ? Action::Decrypt : Action::Encrypt;

                IO io(filePath);
                std::fstream file_stream = std::move(io.getFileStream());
                if(file_stream.is_open()){
                    return Task(std::move(file_stream), filePath, action);
                }else{
                    throw std::runtime_error("Failed to open file: " + filePath);
                }

        }else{
            throw std::runtime_error("Invalid task data: " + taskData);
        }
    }
};