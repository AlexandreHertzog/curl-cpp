cmake_minimum_required(VERSION 3.15)
project(curlcpp)

include(libs/cmake-conan/conan.cmake)

conan_cmake_run(CONANFILE conanfile.txt
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

add_library(curlcpp src/curlcpp/curl.cpp include/curlcpp/curl.hpp)
target_link_libraries(curlcpp PRIVATE CONAN_PKG::libcurl)
target_include_directories(curlcpp PUBLIC include PRIVATE include/curlcpp src/curlcpp)

add_subdirectory(test)
