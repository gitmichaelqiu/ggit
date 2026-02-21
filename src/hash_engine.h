#pragma once
#include <string>
#include <filesystem>

std::string generate_sha256(const std::filesystem::path& file_path);