#pragma once
#include <string>
#include <vector>

struct FileIndex
{
	unsigned long ItemId;
	unsigned long FileId;

	std::string Path;
	std::string RealPath;

	unsigned long Offset;
	unsigned long Length;
};

class MxOLoader
{
private:
	std::string MxOClient;
	std::vector<FileIndex> fileIndices;

public:
	void initialize(const std::string& path);
	bool get_file(unsigned long item_id, unsigned long* data_size, char*& data);
};
