#include "Cryption.hpp"
#include "../processes/Task.hpp"
#include "../fileHandling/ReadEnv.cpp"

int executeCryption(const std::string& taskData){
    try{
        Task task = Task::fromString(taskData);
        ReadEnv env;
        std::string envkey = env.getenv();
        int key = std::stoi(envkey);

        if(task.action == Action::Encrypt){
            char ch;
            while(task.fileStream.get(ch)){
                ch = (ch+key) % 256;
                task.fileStream.seekp(-1, std::ios::cur);
                task.fileStream.put(ch);
            }
            return 0; // Success
        }else if(task.action == Action::Decrypt){
            char ch;
            while(task.fileStream.get(ch)){
                ch = (ch - key + 256) % 256;
                task.fileStream.seekp(-1, std::ios::cur);
                task.fileStream.put(ch);
            }
            task.fileStream.close();
            return 0;
        }else{
            return -2;
        }
    }catch(const std::exception& e){
        std::cerr<<"Error executing cryption: "<<e.what()<<std::endl;
        return -1;
    }
}