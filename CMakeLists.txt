cmake_minimum_required(VERSION 3.5)

project(audiotr)

file(GLOB_RECURSE AUDIOTR_SRC ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_executable(audiotr ${AUDIOTR_SRC})

find_package(portaudio CONFIG REQUIRED)
target_link_libraries(audiotr PRIVATE portaudio)
