#pragma once
#include <string>

class Music
{
private:
public:
	Music();
	Music(const std::string& path);
	void Play();
	void Stop();
	void Loop(bool);
	void Volume(int value);
};
