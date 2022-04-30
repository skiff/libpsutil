#pragma once

#include <string>
#undef vector
#include <vector>

namespace libpsutil
{
    namespace filesystem
    {
        bool read_file(const std::string& file_name, void* data, size_t size);
        std::string read_file(const std::string& file_name);
        bool write_file(const std::string& file_name, void* data, size_t size);
        bool write_file(const std::string& file_name, const std::string& data);
        int64_t get_file_size(const std::string& file_name);

        bool directory_exists(const std::string& directory_name);
        bool file_exists(const std::string& file_name);

        void create_directory(const std::string& directory_name);
        std::vector<std::string> list_files(const std::string& directory_name, bool recursive = false);
    }
}