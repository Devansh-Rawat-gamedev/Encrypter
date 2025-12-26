#include "ProcessManagement.hpp"
#include <memory>
#include "../encryptDecrypt/Cryption.hpp"

ProcessManagement:: ProcessManagement(){}

bool ProcessManagement::submitToQueue(std::unique_ptr<Task> task){
    if(task){
        taskQueue.push(std::move(task));
        return true;
    }
    return false;
}

void ProcessManagement::executeTasks(){
    while(!taskQueue.empty()){
        std::unique_ptr<Task> task = std::move(taskQueue.front());
        if(task){
            std::cout<<"Executing Task: "<<task->toString()<<std::endl;
        }
        taskQueue.pop();
        executeCryption(task->toString());
    }
}