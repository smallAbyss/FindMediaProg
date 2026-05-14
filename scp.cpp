#include <iostream>    
#include <fstream>     
#include <string>      
#include <vector>      
#include <filesystem> 
#include <algorithm>
#include <set>


namespace fs = std::filesystem;

bool isMedia(const fs::path& path) {
     std::string ext = path.extension().string();
      // std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    
    static const std::set<std::string> extensions = {
        ".jpg", ".jpeg", ".png", ".gif", ".bmp",   // картинки
        ".mp4", ".avi", ".mkv", ".mov",            // видео
        ".mp3", ".wav", ".flac", ".ogg",           // аудио
        ".cpp"                                     //i dont have media..
    };
    
    return extensions.find(ext) != extensions.end();
}


std::vector<std::string> scanDirectory(const std::string& path) {
    std::vector<std::string> files;
    try {
        for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
            if (entry.is_regular_file() && isMedia(entry.path())) {
                files.push_back(entry.path().string());
                std::cout << entry.path() << std::endl;

            }
        }
    }
    catch (...) {
        ;
    }
    return files;
}

void saveToJson(const std::vector<std::string>& files, const std::string& output_file) {
    std::ofstream file(output_file);
    
    // creating JSOn
    file << "{\n" << "\"audio\":[\n";
    for (size_t i = 0; i < files.size(); ++i) {
        file << "    \"" << files[i] << "\"";
        
        if (i < files.size() - 1) {
            file << ",";
        }
        file << "\n";
    }
    file << "  ]\n";
    file << "}\n";
    file.close();
}


int main() {
    const char* home = std::getenv("HOME");

    std::vector<std::string> media_files = scanDirectory(home);
    
    saveToJson(media_files, "media_files.json");
    
    std::cout << "Found: " << media_files.size() << "\n";
    
    return 0;
}