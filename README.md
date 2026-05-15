# Media Scanner

Recursive media file scanner for Linux. Finds images, videos, and audio files in a directory and saves them to a structured JSON file.

## Features

- Recursive directory scanning
- Detects images (`.jpg`, `.png`, `.bmp`, `.webp`)
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

### Periodic scan

```bash
./build/scanner -t 3600
```

### Selection of director

```bash
./build/scanner -d /home 
```

## Output

```JSON
{
  "videos": [
    "/home/user/Videos/demo.mp4"
  ],
  "images": [
    "/home/user/Pictures/photo.jpg",
    "/home/user/Pictures/icon.png"
  ],
  "audios": [
    "/home/user/Music/song.mp3"
  ]
}
```