#pragma once]
#include <iostream>
#include <string>

#define LETTERS 26

class Gear
{
public:
	Gear();
	Gear(const std::string& filePath);
	~Gear();
	const std::string close();
	void rotate();
private:
	char interface[26][2];
};

