#pragma once
#include <iostream>
#include <string>

#define LETTERS 26

enum gearType
{
	first, second, third
};

class Gear
{
public:
	Gear(gearType type);
	Gear(const std::string& filePath, const std::string& password);
	~Gear();
	//const std::string close();
	void rotate();
	void printGearState();///function to help debuging delete when every thing works
private:
	//26 rows for the 26 letters first colom is input and second in output.
	gearType _type;
	char _interface[26][2];
	const std::string encryptSettings(const std::string& password);
	const std::string decryptSettings(const std::string& password);
};

