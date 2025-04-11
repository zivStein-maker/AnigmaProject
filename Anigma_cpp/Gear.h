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
	//26 rows for the 26 letters first colom is input and second in output.
	char _interface[26][2];
	void printGearState();///private function to help debuging.
};

