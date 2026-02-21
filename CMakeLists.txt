cmake_minimum_required(VERSION 3.10)
project(ggit CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)

add_executable(ggit src/main.cpp)

target_link_libraries(ggit PRIVATE 
    OpenSSL::Crypto 
    ZLIB::ZLIB
)
