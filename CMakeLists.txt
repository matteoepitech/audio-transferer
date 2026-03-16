cmake_minimum_required(VERSION 3.10)

project(audiotr)

file(GLOB_RECURSE AUDIOTR_SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(audiotr ${AUDIOTR_SRC})

find_package(portaudio CONFIG REQUIRED)
if(TARGET portaudio_static)
    target_link_libraries(audiotr PRIVATE portaudio_static)
elseif(TARGET portaudio)
    target_link_libraries(audiotr PRIVATE portaudio)
else()
    message(FATAL_ERROR "Unsupported PortAudio package: no CMake target exported")
endif()
