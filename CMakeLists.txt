cmake_minimum_required(VERSION 3.20)
project(uin-campus CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-Wall -Wextra -Wpedantic)

add_library(uincampus src/moyenne.cpp src/statistiques.cpp src/regles.cpp src/saisie.cpp)
target_include_directories(uincampus PUBLIC include)

add_executable(uin-campus app/main.cpp)
target_link_libraries(uin-campus PRIVATE uincampus)

add_executable(uin-campus-stats app/statistiques.cpp)
target_link_libraries(uin-campus-stats PRIVATE uincampus)
