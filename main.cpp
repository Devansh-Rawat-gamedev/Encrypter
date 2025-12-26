#include <iostream>
#include <filesystem>
#include <string>
#include "./src/app/processes/ProcessManagement.hpp"
#include "./src/app/processes/Task.hpp"
namespace fs = std::filesystem;

int main(int argc, char* argv[]){
    std::string directory;
    std::string action;
    std::cout<<"Enter directory path: "<<std::endl;
    std::getline(std::cin,action);

    try{
        if(fs::exists(directory) && fs::is_directory(directory)){
            ProcessManagement pm;
            for(const auto& entry : fs::recursive_directory_iterator(directory)){
                if(entry.is_regular_file()){
                    std::string filePath = entry.path().string();
                    IO io(filePath);
                    std::fstream file_stream = std::move(io.getFileStream());
                    if(file_stream.is_open()){
                        Action act = action == "Encrypt" ? Action::Encrypt : Action::Decrypt;
                        auto task = std::make_unique<Task>(std::move(file_stream), filePath, act);
                        pm.submitToQueue(std::move(task));
                    }else{
                        std::cerr<<"Failed to open file: "<<filePath<<std::endl;
                    }
                }
            }
            pm.executeTasks();
        }else{
            std::cout<<"Invalid directory path."<<std::endl;
        }
    }catch(const fs::filesystem_error& e){
        std::cerr<<"Filesystem error: "<<e.what()<<std::endl;
        return 1;
    }
}