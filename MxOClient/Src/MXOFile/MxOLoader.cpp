#include "MxOLoader.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "../Engine/MemoryInputStream.h"


void MxOLoader::initialize(const std::string& game_path)
{
	MxOClient = game_path;


	std::ifstream stream;
	stream.open(MxOClient + "/rezmap.ltb", std::ios::in | std::ios::binary);
	stream.seekg(0, std::ios::end);
	int size = stream.tellg();
	stream.seekg(0, std::ios::beg);
	char* dataBuffer = new char[size];

	stream.read(dataBuffer, size);

	MemoryInputStream reader(dataBuffer, size);
	char* header;
	reader.get(header, 20);

	int value = 0;
	reader.get(value);
	int packmapNameSize = 0;
	reader.get(packmapNameSize);
	int resourcesSize = 0;
	reader.get(resourcesSize);


	int* v3 = new int[value / 4];
	for (int i = 0; i < value / 4; ++i)
	{
		reader.get(v3[i]);
	}

	std::vector<std::string> packNames;

	char* buffer;
	reader.get(buffer, packmapNameSize);

	MemoryInputStream strings(buffer, packmapNameSize);

	while (strings.GetPtr() < packmapNameSize)
	{
		std::string temp;
		strings.get(temp);
		packNames.push_back(temp);
	}

	char* v7;
	reader.get(v7, 8192);

	for (int i = 0; i < resourcesSize / 56; ++i)
	{
		int itemId = 0;
		int unk = 0;
		int packNamesOffset = 0;
		char* unk8;
		int type = 0;
		int offset = 0;
		int length = 0;

		reader.get(itemId);
		reader.get(unk);
		reader.get(packNamesOffset);
		reader.get(unk8, 32);
		delete[] unk8;

		reader.get(type);
		reader.get(offset);
		reader.get(length);

		FileIndex fi;
		fi.Length = length;
		fi.Offset = offset;
		fi.ItemId = itemId;
		if (packNames.size() >= packNamesOffset - 1)
			fi.RealPath = "packmaps/" + packNames[packNamesOffset - 1];
		else
			fi.RealPath = "NOPATH";


		fileIndices.push_back(fi);
	}

	delete[]v7;
	delete[]v3;
	delete[]header;
	delete[]dataBuffer;
}

bool MxOLoader::get_file(unsigned long itemId, unsigned long* dataSize, char*& data)
{
	for (auto file_index : fileIndices)
	{
		if (file_index.ItemId == itemId)
		{
			auto path = MxOClient + "/" + file_index.RealPath;
			std::ifstream file(path, std::ios::in | std::ios::binary);
			file.seekg(file_index.Offset);

			char* temp_data = new char[file_index.Length];

			if (file.read(temp_data, file_index.Length))
			{
				*dataSize = file_index.Length;
				data = temp_data;
				return true;
			}
		}
	}

	return false;
}


