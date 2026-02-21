#include "hash_engine.h"
#include <openssl/evp.h>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

std::string generate_sha256(const std::filesystem::path& file_path) {
    std::ifstream file(file_path, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file to hash: " << file_path << "\n";
        return "";
    }

    EVP_MD_CTX* context = EVP_MD_CTX_new();
    if (context == nullptr) return "";

    EVP_DigestInit_ex(context, EVP_sha256(), nullptr);

    char buffer[4096];
    while (file.good()) {
        file.read(buffer, sizeof(buffer));
        std::streamsize bytes_read = file.gcount();
        if (bytes_read > 0) {
            EVP_DigestUpdate(context, buffer, bytes_read);
        }
    }

    unsigned char hash_result[EVP_MAX_MD_SIZE];
    unsigned int hash_length = 0;
    EVP_DigestFinal_ex(context, hash_result, &hash_length);

    EVP_MD_CTX_free(context);

    std::stringstream hex_stream;
    for (unsigned int i = 0; i < hash_length; ++i) {
        hex_stream << std::hex << std::setw(2) << std::setfill('0') << (int)hash_result[i];
    }

    return hex_stream.str();
}