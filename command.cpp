
#include "command.hpp"

command::command(){
}
std::string command::open_terminal(){
    std::string result;
    FILE* fp = popen("terminator","r");
    if(!fp){
        return "faild";
    }
    char buffer[128];
    while ((fgets(buffer,sizeof(buffer),fp)) != nullptr){
        result += buffer;
    }
    pclose(fp);
    return result;
    
}


std::string command::open_calculator(){
    std::string result;
    FILE* fp = popen("gnome-calculator","r");
    if(!fp){
        return "faild";

    }
    char buffer[128];
    while ((fgets(buffer,sizeof(buffer),fp)) != nullptr){
        result += buffer;

    }
    pclose(fp);
    return result;
    
}
std::string command::open_firefox(){
    std::string result;
    FILE* fp = popen("firefox","r");
    if(!fp){
        return "faild";
    }
    char buffer[128];
    while ((fgets(buffer,sizeof(buffer),fp)) != nullptr){

        result += buffer;
        
    }
    pclose(fp);
    return result;
    
}