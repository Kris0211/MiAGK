#pragma once
#include <string>
#include <vector>

class FileSaver
{
public:
	static void Save(const std::string& path, const std::vector<int>& data, 
		const unsigned short width, const unsigned short height);
};
