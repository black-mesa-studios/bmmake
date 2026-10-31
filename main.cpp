#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include "upl.h"

namespace fs = std::filesystem;
using string = std::string;

inline void printerr(const string &str) {
    std::cout << Colour::Red << "[ERROR]" << Colour::White << " " << str;
}

inline void create_file(const string &path) {
    std::ofstream f(path);
    f.close();
}

struct ConfigData {
    std::vector<string> call;
    std::vector<string> cmd;
};

int main(int argc, char **argv)
{
    std::vector<string> args;
    for(int i = 0; i < argc; i++) {
        args.push_back(argv[i]); // Transferring arguments to a vector, will be useful later.
    }

    if(args.size() <= 1) {
        printerr("Please input arguments.\n");
        return 1;
    }

    if(args[1] == "init") {
        if(fs::exists(".bmmake")) {
            printerr("the \".bmmake\" directory already exists!\n");
            return 1;
        }
        fs::create_directory(".bmmake");
        create_file(".bmmake/config");
        return 0;
    }

     if(!fs::exists(".bmmake/config")) {
        printerr("Config file not found! Have you tried \"bmmake init\"?\n");
        return 1;
     }

    ConfigData configdata;
    string __tmp_call, __tmp_cmd;
    std::ifstream config(".bmmake/config");
    while(config >> __tmp_call >> __tmp_cmd) {
        configdata.call.push_back(__tmp_call);
        configdata.cmd.push_back(__tmp_cmd);
    }
    config.close();

    if(configdata.cmd.empty() || configdata.call.empty()) {
        printerr("Invalid config format!\n");
        return 1;
    }

    for(int i = 0; i < configdata.call.size(); i++) {
        if(args[1] == configdata.call[i]) {
            std::cout << Colour::Cyan << "> " << Colour::White << configdata.cmd[i] << "\n";
            system(configdata.cmd[i].c_str());
        }
    }

    return 0;
}