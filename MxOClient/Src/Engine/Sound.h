#pragma once
#include <string>

class Sound
{
private:
public:
	Sound(const std::string& path);
	void Play();
	void Stop();
};
