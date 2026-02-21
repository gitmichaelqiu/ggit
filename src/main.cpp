#include <iostream>
#include <openssl/opensslv.h>
#include <zlib.h>
#include <filesystem>

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
    std::cout << "--- ggit Build Verification ---" << std::endl;
    
    std::cout << "Command invoked: " << argv[0] << std::endl;
    std::cout << "Total arguments: " << argc << std::endl;
    std::cout << "Current path: " << fs::current_path() << std::endl;
    std::cout << "OpenSSL Version: " << OPENSSL_VERSION_TEXT << std::endl;
    std::cout << "zlib Version: " << ZLIB_VERSION << std::endl;

    return 0;
}