#pragma once

#include "Rotor.h"
#include <map>
#include <vector>

#define DEFAULT_AMOUNT 3

class Enigma
{
public:
	Enigma();
	Enigma(const std::string& filePath);
	//Enigma(const std::string& filePath,int rotorAmount);
	void start();
	std::string parser(const std::string& inputString);
	char encryptCharacter(char let);
	void move();
	~Enigma();

private:
	std::map<char, char> _reflector;
	std::map<char, char> _plugBoard;
	std::vector<Rotor*> _rotors;
	int _rotorAmount;
	std::string _filePath;
	const std::string getPlugBoardSettings();
	const std::string getReflectorSettings();
	std::map<char, char> generateRandomMapping();
	void setPlugBoardMapping(const std::string settings);
	void setReflectorMapping(const std::string settings);
};