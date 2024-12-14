cmake_minimum_required(VERSION 3.15...3.28)

project(scrollspace VERSION 0.2.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_STANDARD_REQUIRED YES)
set(CMAKE_CXX_EXTENSIONS NO)
set(CMAKE_CXXFLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra")

add_executable(scrspace scrspace.cc)

find_library(MATH_LIBRARY m)
if(MATH_LIBRARY)
    target_link_libraries(scrspace PUBLIC ${MATH_LIBRARY})
endif()

set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory(libSDL2pp)
target_link_libraries(scrspace PRIVATE SDL2pp::SDL2pp)
