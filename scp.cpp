#include <iostream>    
#include <fstream>     
#include <string>      
#include <vector>      
#include <filesystem> 


namespace fs = std::filesystem;

void scan_directory(const std::string& path) {
    try {
        for (const auto& dir_entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
            std::cout << dir_entry.path() << std::endl;
        }
    }
    catch (...) {
        ;
    }
}

int main() {
    const char* home = std::getenv("HOME");

    scan_directory(home);
    return 0;
}