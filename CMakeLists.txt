cmake_minimum_required(VERSION 3.10)

if(NOT EXISTS "/usr/bin/ffmpeg")
    message(FATAL_ERROR "ffmpeg executable not found")
else()
    execute_process(
        COMMAND /usr/bin/ffmpeg -version
        OUTPUT_VARIABLE ffmpegOut
    )
    string(REGEX MATCH "[0-9]+\.[-0-9]+\.[0-9]+" ffmpegVersion "${ffmpegOut}")
    message("using ffmpeg v${ffmpegVersion}")
endif()

project(ffmpegaudioextractor LANGUAGES C)

add_executable(ffmpegaudioextractor main.c)

install(TARGETS ffmpegaudioextractor RUNTIME DESTINATION bin)
