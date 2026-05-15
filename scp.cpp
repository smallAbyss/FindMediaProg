#include <iostream>    
#include <fstream>     
#include <string>      
#include <vector>      
#include <filesystem> 
#include <algorithm>
#include <set>
#include <tuple>
#include <array>

const unsigned MAGIC_CONST = 3;

namespace fs = std::filesystem;
using VoS = std::vector<std::string>;
using AoVoS = std::array<VoS, MAGIC_CONST>;

const std::set<std::string> IMAGE_EXTS = {
    ".jpg", ".jpeg", ".png", ".bmp", ".webp"
};
const std::set<std::string> VIDEO_EXTS = {
    ".mp4", ".avi", ".mkv", ".mov", ".flv", ".webm"
};
const std::set<std::string> AUDIO_EXTS = {
    ".mp3", ".wav", ".flac", ".ogg"
};



std::string whichMedia(const std::string& ext) {
    if (AUDIO_EXTS.find(ext) != AUDIO_EXTS.end()) return "au";
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
        ".mp3", ".wav", ".flac", ".ogg"           // аудио
    };
    
    return extensions.find(ext) != extensions.end();
}

AoVoS scanDirectory(const std::string& path) {
    VoS images;
    VoS videos;
    VoS audios;
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
            }
        }
    }
    catch (...) {
        ;
    }
    return {videos, images, audios};
}


void saveToJson(const AoVoS& files, const std::string& output_file) {
    std::ofstream file(output_file);
    
    file << "{\n";
    std::array<std::string, MAGIC_CONST> sections = {"videos", "images", "audios"};
    
    for(unsigned i = 0; i < MAGIC_CONST; i++) {
        const VoS& items = files[i];
        file << "  \"" << sections[i] << "\": [\n";
        
        for (unsigned j = 0; j < items.size(); j++) {
            file << "    \"" << items[j] << "\"";
            if (j < items.size() - 1) {
                file << ",";
            }
            file << "\n";
        }
        file << "  ]";
        
        if (i < MAGIC_CONST - 1) {
            file << ",";
        }
        file << "\n";
    }
    file << "}\n";
    file.close();
}

unsigned getSizeOfAovos(const AoVoS& v) {
    unsigned sum = 0;
    for(auto& i : v ) 
        sum += i.size();
    return sum;
}

int main(int argc, char* argv[]) {
    std::string dir = (argc > 1) ? argv[1] : std::getenv("HOME");
    if (!fs::exists(dir)) {
        std::cout << "[Error] path does not exist: " << dir << "\n";
        return 1;
    }
    auto media_files = scanDirectory(dir);
    
    saveToJson(media_files, "media_files.json");

    std::cout << "Found: " << getSizeOfAovos(media_files) << "\n";
    
    return 0;
}
