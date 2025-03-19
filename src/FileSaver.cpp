#include "FileSaver.h"

#include <fstream>
#include <ios>


void FileSaver::Save(const std::string& path, const std::vector<int>& data, 
                     const unsigned short width, const unsigned short height)
{
	const std::vector<unsigned short> fileHeader = {
        0x0000, 0x0002, 0x0000, 0x0000, 0x0000, 0x0000,
        width, height,
        0x0820
    };

    std::fstream file(path, std::ios::out | std::ios::binary);

    // Write header
	file.write(reinterpret_cast<const char*>(fileHeader.data()), 
        fileHeader.size() * sizeof(unsigned short));
    // Write pixel data
    file.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(int));
    file.close();
}
