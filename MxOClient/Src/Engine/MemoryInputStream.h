#pragma once
#include <istream>
#include <vector>

/*
 * Rewrite to not use memorybuffer, and istream
 */
class MemoryInputStream : private std::istream
{
public:
	MemoryInputStream(char* aData, size_t aLength) :
		std::istream(&m_buffer),
		m_buffer(aData, aLength)
	{
		ptr = 0;
		totalSize = aLength;
		rdbuf(&m_buffer); // reset the buffer after it has been properly constructed
	}

	void get(int& val)
	{
		const auto value_buffer = new char[4];
		read(value_buffer, 4);
		ptr += 4;

		val = *reinterpret_cast<int*>(value_buffer);
		delete[] value_buffer;
	}

	void get(float& val)
	{
		const auto value_buffer = new char[4];
		read(value_buffer, 4);
		ptr += 4;

		val = *reinterpret_cast<float*>(value_buffer);
		delete[] value_buffer;
	}

	void get(short& val)
	{
		const auto value_buffer = new char[2];
		read(value_buffer, 2);
		ptr += 2;

		val = *reinterpret_cast<short*>(value_buffer);

		delete[] value_buffer;
	}

	void get(char& val)
	{
		const auto value_buffer = new char[1];
		read(value_buffer, 1);
		ptr += 1;

		val = *reinterpret_cast<char*>(value_buffer);
		delete[] value_buffer;
	}

	void get(char*& val, const int count)
	{
		const auto value_buffer = new char[count];
		for (int i = 0; i < count; ++i)
		{
			get(value_buffer[i]);
		}

		val = value_buffer;
	}

	/* Read null terminated string */
	void get(std::string& outString)
	{
		std::vector<char> characters;

		while (true)
		{
			char currentChar;
			get(currentChar);
			
			characters.push_back(currentChar);

			if (currentChar == '\0') {
				outString = std::string(characters.begin(), characters.end());
				ptr += outString.length();
				return;
			}
		}
	}

	bool Eof()
	{
		if (ptr >= totalSize)
			return true;

		return false;
	}

	int GetPtr()
	{
		return ptr;
	}
private:
	class MemoryBuffer : public std::basic_streambuf<char>
	{
	public:
		MemoryBuffer(char* aData, size_t aLength)
		{
			setg(aData, aData, aData + aLength);
		}
	};

	MemoryBuffer m_buffer;
	int ptr;
	int totalSize;
};
