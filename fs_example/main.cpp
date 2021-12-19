#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

// take all headers files from manager.h and check what the problem
#include <sys/socket.h>
#include <netinet/in.h>
#include <malloc.h>
#include <cstring>
#include <unistd.h>
#include "../../../sniffer/network_counter/manager.h"



namespace fs = std::filesystem;

int main(int argc, char** argv)
{
    fs::path filename;
    if (argc != 2) {
        filename = "text.txt";
    } else {
        filename = std::string(argv[1]);
    }

    std::ifstream readStream(filename);

    if (!readStream.is_open()) 
    {
        std::cerr << "Could not open the file " << filename << std::endl;
        return 1;
    }

    for (std::string line; std::getline(readStream, line); )
    {
        std::cout << line << '\n';
    }

    return 0;
}

