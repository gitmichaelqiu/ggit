#include "compress_engine.h"
#include <zstd.h>
#include <fstream>
#include <iostream>

std::vector<char> compress_file(const std::filesystem::path& file_path) {
    std::ifstream file(file_path, std::ios::binary | std::ios::ate);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for compression: " << file_path << "\n";
        return {};
    }

    // Get file size, then rewind to the beginning
    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    // Read the uncompressed data into a vector
    std::vector<char> file_buffer(size);
    if (!file.read(file_buffer.data(), size)) {
        std::cerr << "Error: Could not read file data.\n";
        return {};
    }

    size_t const compressed_bound = ZSTD_compressBound(file_buffer.size());
    std::vector<char> compressed_buffer(compressed_bound);

    // Compress at Level 3
    size_t const compressed_size = ZSTD_compress(
        compressed_buffer.data(), compressed_buffer.size(),
        file_buffer.data(), file_buffer.size(),
        3 
    );

    if (ZSTD_isError(compressed_size)) {
        std::cerr << "Zstd Compression error: " << ZSTD_getErrorName(compressed_size) << "\n";
        return {};
    }

    // ZSTD_compressBound gives the worst-case size. We want the vector to only hold the exact compressed bytes.
    compressed_buffer.resize(compressed_size);

    return compressed_buffer;
}