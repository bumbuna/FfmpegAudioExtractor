## FFFMPEG AUDIO EXTRACTOR
A small utility program to extract audio streams from video files.

## BUILD
The build process is managed by CMake.
### Requirements
- CMAKE 3.0+.
- Unix system.
- ffmpeg command line utility.
```bash
$ git clone https://github.com/bumbuna/ffmpegaudioextractor
$ cd ffmpegaudioextractor
$ cmake -B build
$ cmake --build build
# optional command
$ cmake --install build #may require superuser privilege.
```

## USAGE
```bash
$ ffmpegaudioextractor <directory>
```
> The directory should contain video files that are to be converted.

## LIMITATIONS
This program currently works on mkv and mp4 files only and outputs the audio stream in mp3 format.

