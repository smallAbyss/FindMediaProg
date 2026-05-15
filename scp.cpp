#include <iostream>    
#include <fstream>     
#include <string>      
#include <vector>      
#include <filesystem> 
#include <algorithm>
#include <set>
#include <tuple>



namespace fs = std::filesystem;
using VoS = std::vector<std::string>;
using ToVoS = std::tuple<VoS, VoS, VoS>;

const std::set<std::string> IMAGE_EXTS = {
    ".jpg", ".jpeg", ".png", ".bmp", ".webp"
};
const std::set<std::string> VIDEO_EXTS = {
    ".mp4", ".avi", ".mkv", ".mov", ".flv", ".webm"
};
const std::set<std::string> AUDIO_EXTS = {
    ".mp3", ".wav", ".flac", ".ogg"
};
const std::set<std::string> C_EXTS = {
    ".c"
};



std::string whichMedia(const std::string& ext) {
    if (AUDIO_EXTS.find(ext) != AUDIO_EXTS.end()) return "au";
    if (C_EXTS.find(ext) != C_EXTS.end()) return "c";
    if (IMAGE_EXTS.find(ext) != IMAGE_EXTS.end()) return "pic";
    if (VIDEO_EXTS.find(ext) != VIDEO_EXTS.end()) return "vid";
    return "idk";
}

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

ToVoS scanDirectory(const std::string& path) {
    std::vector<std::string> images;
    std::vector<std::string> videos;
    std::vector<std::string> audios;
    try {
        for (const auto& entry : fs::recursive_directory_iterator(path, fs::directory_options::skip_permission_denied)) {
            if (entry.is_regular_file() && isMedia(entry.path())) {
                std::string type = whichMedia(entry.path().extension().string()); 
                if (type == "pic") 
                    images.push_back(entry.path().string());
                if (type == "vid")
                    videos.push_back(entry.path().string());
                if (type == "au")
                    audios.push_back(entry.path().string());
                if (type == "c")
                    audios.push_back(entry.path().string());
            }
        }
    }
    catch (...) {
        ;
    }
    return std::make_tuple(videos, images, audios);
}


void saveToJson(const ToVoS& files, const std::string& output_file) {
    std::ofstream file(output_file);
    VoS audios = std::get<2>(files);
    VoS images = std::get<1>(files);
    VoS videos = std::get<0>(files);

    // creating JSOn
    file << "{\n";
    file << "\"audio\":[\n";
    for (size_t i = 0; i < audios.size(); ++i) {
        file << "    \"" << audios[i] << "\"";
        
        if (i < audios.size() - 1) {
            file << ",";
        }
        file << "\n";
    }
    file << "  ],\n";

    file << "\"images\":[\n";
    for (size_t i = 0; i < images.size(); ++i) {
        file << "    \"" << images[i] << "\"";
        
        if (i < images.size() - 1) {
            file << ",";
        }
        file << "\n";
    }
    file << "  ],\n";

    file << "\"videos\":[\n";
    for (size_t i = 0; i < videos.size(); ++i) {
        file << "    \"" << videos[i] << "\"";
        
        if (i < videos.size() - 1) {
            file << ",";
        }
        file << "\n";
    }
    file << "  ]\n";

    file << "}\n";
    file.close();
}


unsigned sizeOfTovos(const ToVoS& var) {
    VoS audios = std::get<2>(var);
    VoS images = std::get<1>(var);
    VoS videos = std::get<0>(var);
}

int main() {
    const char* home = std::getenv("HOME");

    auto media_files = scanDirectory(home);
    
    saveToJson(media_files, "media_files.json");
    

    // std::cout << "Found: " << media_files.size() << "\n";
    
    return 0;
}