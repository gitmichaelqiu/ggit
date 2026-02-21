#pragma once
#include <vector>
#include <filesystem>

std::vector<char> compress_file(const std::filesystem::path& file_path);