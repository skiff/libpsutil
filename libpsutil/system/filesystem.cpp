#include <cell/cell_fs.h>

#include "system/filesystem.hpp"
#include "string.hpp"

namespace libpsutil
{
    namespace filesystem
    {
        bool read_file(const std::string& file_name, void* data, size_t size)
        {
            int fd = 0;
            uint64_t pos = 0;
            uint64_t nread = 0;

            if (cellFsOpen(file_name.data(), 0, &fd, NULL, 0) == CELL_FS_SUCCEEDED)
            {
                cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
                cellFsRead(fd, data, size, &nread);
                cellFsClose(fd);

                return true;
            }

            return false;
        }

        std::string read_file(const std::string& file_name)
        {
            auto size = get_file_size(file_name);
            if (size != -1)
            {
                auto* data = new char[size + 1];
                read_file(file_name, data, size);

                std::string output;
                output.resize(size + 1);
                memcpy(const_cast<char*>(output.data()), data, static_cast<size_t>(size));
                return output;
            }

            return {};
        }

        bool write_file(const std::string& file_name, const void* data, size_t size)
        {
            int fd = 0;
            uint64_t pos = 0, nwrite = 0;

            if (cellFsOpen(file_name.data(), CELL_FS_O_WRONLY | CELL_FS_O_CREAT | CELL_FS_O_TRUNC, &fd, NULL, 0) == CELL_FS_SUCCEEDED)
            {
                cellFsLseek(fd, 0, CELL_FS_SEEK_SET, &pos);
                cellFsWrite(fd, data, size, &nwrite);
                cellFsClose(fd);

                return true;
            }

            return false;
        }

        bool write_file(const std::string& file_name, const std::string& data)
        {
            return write_file(file_name, data.data(), data.length());
        }

        int64_t get_file_size(const std::string& file_name)
        {
            struct CellFsStat s;

            if (cellFsStat(file_name.data(), &s) == CELL_FS_SUCCEEDED)
            {
                return static_cast<int64_t>(s.st_size);
            }

            return -1;
        }

        bool directory_exists(const std::string& directory_name)
        {
            struct CellFsStat s;

            if (cellFsStat(directory_name.data(), &s) == CELL_FS_SUCCEEDED)
            {
                return ((s.st_mode & CELL_FS_S_IFDIR) != 0);
            }

            return false;
        }

        bool file_exists(const std::string& file_name)
        {
            struct CellFsStat s;

            if (cellFsStat(file_name.data(), &s) == CELL_FS_SUCCEEDED)
            {
                return ((s.st_mode & CELL_FS_S_IFREG) != 0);
            }

            return false;
        }

        void create_directory(const std::string& directory_name)
        {
            if (!directory_exists(directory_name.data()))
            {
                cellFsMkdir(directory_name.data(), 0777);
            }
        }

        std::vector<std::string> list_files(const std::string& directory_name, bool recursive)
        {
            std::vector<std::string> files;

            std::string directory_name_ = directory_name;
            if (!libpsutil::string::ends_with(directory_name, "/"))
            {
                directory_name_.append("/");
            }

            int fd;
            if (cellFsOpendir(directory_name_.data(), &fd) != CELL_FS_OK) { return files; }

            uint64_t nread;
            CellFsDirent dent;

            while (cellFsReaddir(fd, &dent, &nread) == CELL_FS_OK)
            {
                if (nread == 0) { break; }

                if (dent.d_name[0] != '.')
                {
                    struct CellFsStat st;
                    auto file = directory_name_ + dent.d_name;

                    if (cellFsStat(file.data(), &st) == CELL_FS_SUCCEEDED)
                    {
                        if ((st.st_mode & CELL_FS_S_IFDIR) != 0)
                        {
                            if (recursive)
                            {
                                auto sub_directory = list_files(file, recursive);
                                for (auto& sub_file : sub_directory)
                                {
                                    files.push_back(sub_file);
                                }
                            }
                        }
                        else
                        {
                            files.push_back(file);
                        }
                    }
                }
            }

            cellFsClosedir(fd);

            return files;
        }
    }
}