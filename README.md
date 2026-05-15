# Media Scanner

## Describtion
Recursive media file scanner for Linux. Finds images, videos, and audio files in a directory and saves them to a structured JSON file.

## Features

- Recursive directory scanning
- Detects images (`.jpg`, `.jpeg`, `.png`, `.bmp`, `.webp`)
- Detects videos (`.mp4`, `.avi`, `.mkv`, `.mov`, `.flv`, `.webm`)
- Detects audio (`.mp3`, `.wav`, `.flac`, `.ogg`)
- Outputs grouped JSON
- Optional periodic scanning with `-t` flag
- Customizable search directory via `-d` flag

## Requirements

- Linux
- C++17 compiler
- CMake 3.10+ (or `g++`)

## Quick Start

### Build with CMake

```bash
cmake -B build -S . -G Ninja
cmake --build build
./build/scanner
```

### Build with g++

```bash
g++ -std=c++17 scp.cpp -o scanner -lstdc++fs -pthread
./scanner
```

## Flags

- `-t <time>` - rescan every `<time>` seconds;
- `-d <path>` - scan the specified directory (`.` by default).

## Output
The output JSON would be created in the `.` with name `media_files.json` 

`media_files.json (example):`
```JSON
{
  "videos": [
    "/home/user/videos/demo.mp4"
  ],
  "images": [
    "/home/user/pictures/photo.jpg",
    "/home/user/pictures/icon.png"
  ],
  "audios": [
    "/home/user/music/song.mp3"
  ]
}
```