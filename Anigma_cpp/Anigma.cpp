#include "Anigma.h"
#include <ranges>


Anigma::Anigma()
{
	this->_rotorAmount = DEFAULT_AMOUNT;
	for (int i = 0; i < LETTERS; i++)
	{
		char let = static_cast<char>('a' + i);
		_plugBoard.insert(let, let);
	}
	for (int i = 0; i < _rotorAmount; i++)
	{
		const std::string path = "//settings.ang//gear.and";
		_rotors.emplace_back((path, (char)i));
	}
}

Anigma::Anigma(const std::string& filePath)
{
	this->_rotorAmount = DEFAULT_AMOUNT;
	for (int i = 0; i < _rotorAmount; i++)
	{
		const std::string path = "//settings.ang//gear.and";
		_rotors.emplace_back((path, (char)i));
	}
	for (int i = 0; i < LETTERS; i++)
	{
		char let = static_cast<char>('a' + i);
		_plugBoard.insert(let, let);
	}
}

void Anigma::start()
{

}

std::string Anigma::parser(const std::string& inputString)
{
	std::string result = "";
	for (const char& letter : inputString)
	{
		result += this->encryptCharacter(letter);
	}
}

char Anigma::encryptCharacter(char let)
{
	this->move();
	char output = _plugBoard.at(let);
	for (auto& rotor : _rotors)
	{
		output = rotor->getFirstOutput(output);
	}
	for (int i = _rotors.size() - 1; i >= 0; --i) 
	{
		output = _rotors[i]->getSecondOutput(output);
	}
	return output;
}

void Anigma::move()
{
	for (auto& rotor : _rotors)
	{
		if (!rotor->rotate())
			break;
	}
}
