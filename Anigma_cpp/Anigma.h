#pragma once

#include "Rotor.h"
#include <map>
#include <vector>

#define DEFAULT_AMOUNT 3

class Anigma
{
public:
	Anigma();
	Anigma(const std::string& filePath);
	//Anigma(const std::string& filePath,int rotorAmount);
	void start();
	std::string parser(const std::string& inputString);
	char encryptCharacter(char let);
	void move();
	~Anigma();

private:
	std::map<char, char> _plugBoard;
	std::vector<Rotor*> _rotors;
	int _rotorAmount;
	std::string _filePath;
	std::string getPlugBoardSettings();
};