#pragma once
#include <iostream>
#include <string>

#define LETTERS 26



class Rotor
{
public:
	Rotor(const std::string& filePath ,char type);
	Rotor(const std::string& filePath, const std::string& password, char type);
	~Rotor();
	char getFirstOutput(char let) const;
	char getSecondOutput(char let) const;
	//const std::string close();
	bool rotate();
	void printRotorState();///function to help debuging delete when every thing works
private:
	//26 rows for the 26 letters first colom is input and second in output.
	std::string settingsFile;
	char _type;
	char _interface[26][2];
	const std::string encryptSettings(const std::string& password);
	const std::string decryptSettings(const std::string& password);
	const std::string getRotorSettings();
};

