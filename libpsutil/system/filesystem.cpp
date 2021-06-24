#include <cell/cell_fs.h>

#include "system/filesystem.hpp"

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

        bool write_file(const std::string& file_name, void* data, size_t size)
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

        int64_t get_file_size(const std::string& file_name)
        {
            struct CellFsStat s;

            if (cellFsStat(file_name.data(), &s) == CELL_FS_SUCCEEDED)
            {
                return static_cast<int64_t>(s.st_size);
            }

            return -1;
        }
    }
}