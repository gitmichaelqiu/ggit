cmake_minimum_required(VERSION 3.14)

project(ggit CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(OpenSSL REQUIRED)
find_package(SQLite3 REQUIRED)

find_path(ZSTD_INCLUDE_DIR zstd.h REQUIRED)
find_library(ZSTD_LIBRARY zstd REQUIRED)

find_library(ZSTD_LIBRARY zstd REQUIRED)

add_executable(ggit src/main.cpp src/hash_engine.cpp src/compress_engine.cpp)

target_include_directories(ggit PRIVATE ${ZSTD_INCLUDE_DIR})

target_link_libraries(ggit PRIVATE 
    OpenSSL::Crypto 
    SQLite::SQLite3
    ${ZSTD_LIBRARY}
)
