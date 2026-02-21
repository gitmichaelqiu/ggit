#include "hash_engine.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <sqlite3.h>

namespace fs = std::filesystem;

void init_sqlite_index(const fs::path& db_path) {
    sqlite3* db;
    char* errmsg = nullptr;

    int rc = sqlite3_open(db_path.c_str(), &db);

    if (rc != SQLITE_OK) {
        std::cerr << "Error: Cannot open database.";
        sqlite3_close(db);
        return;
    }

    const char* sql = "CREATE TABLE IF NOT EXISTS staging_area(path TEXT PRIMARY KEY, hash TEXT NOT NULL, size INTEGER, modified_time INTEGER);";

    rc = sqlite3_exec(db, sql, nullptr, nullptr, &errmsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL Error: " << errmsg << "\n";
        sqlite3_free(errmsg);
    }

    sqlite3_close(db);
}

void ggit_init() {
    fs::path repo = fs::current_path() / ".ggit";
    if (fs::exists(repo)) {
        std::cout << "Repo is already initialized.\n";
        return;
    }

    try {
        fs::create_directories(repo);
        fs::create_directories(repo / "objects");
        fs::create_directories(repo / "refs/heads");
        fs::create_directories(repo / "refs/tags");

        std::ofstream file(repo / "HEAD");
        if (file.is_open()) {
            file << "ref: refs/heads/main\n";
            file.close();
        } else {
            std::cerr << "Error: Could not create HEAD file. Check permissions.\n";
        }

        init_sqlite_index(repo / "index.db");

        std::cout << "Initialized empty ggit repository in " << repo << "\n";
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Filesystem Error: " << e.what() << "\n";
    }
}

int main() {
    ggit_init();

    std::string my_hash = generate_sha256("test.txt");
    std::cout << "The hash is: " << my_hash << "\n";

    return 0;
}
