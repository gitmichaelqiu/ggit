#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem;

void ggit_init() {
    fs::path repo = fs::current_path() / ".ggit";
    if (fs::exists(repo)) {
        std::cout << "Repo is already initialized.\n";
        return;
    }

    fs::create_directories(repo);
    fs::create_directories(repo / "objects");
    fs::create_directories(repo / "refs/heads");
    fs::create_directories(repo / "refs/tags");

    std::ofstream file(repo / "HEAD");
    file << "ref: refs/heads/main\n";
    file.close();

    std::cout << "Repo is initialized.\n";
}

int main() {
    ggit_init();

    return 0;
}
