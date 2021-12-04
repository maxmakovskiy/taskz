#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

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

