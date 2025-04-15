#include "Anigma.h"
#include <sstream>
#include <fstream>


Anigma::Anigma()
{
	this->_rotorAmount = DEFAULT_AMOUNT;
	_filePath = "settings//rotor.ang";
	for (int i = 0; i < LETTERS; i++)
	{
		char let = static_cast<char>('a' + i);
		_plugBoard[let] = let;
	}
	for (int i = 0; i < _rotorAmount; i++)
	{
		_rotors.emplace_back(new Rotor(_filePath, static_cast<char>(i)));
	}
}

Anigma::Anigma(const std::string& filePath)
{
	std::fstream file(filePath);
	std::string settings = "";
	this->_filePath = filePath;
	this->_rotorAmount = DEFAULT_AMOUNT;
	for (int i = 0; i < _rotorAmount; i++)
	{
		_rotors.emplace_back(new Rotor(_filePath, static_cast<char>(i)));
	}
	while (std::getline(file, settings))
	{
		if (settings[0] == ('~'))
			break;
	}
	for (int i = 0; i < LETTERS; i++)
	{
		char let = static_cast<char>('a' + i);
		std::string finder = "";
		finder += let;
		finder += ':';
		char result = settings[settings.find(finder) + finder.length()];
		_plugBoard[let] = result;
	}
	file.close();
}

void Anigma::start()
{
	std::cout << "start getting the text to encrypt.\n write \"finish\" to stop writing\n";
	std::string text = "";
	std::string resultText = "";
	while (text != "finish")
	{
		resultText += parser(text);
		std::getline(std::cin, text);
	}
	//std::cout << "the plane text: " << text << std::endl;
	//std::cout << "the encrypted text: " << resultText << std::endl;
}

std::string Anigma::parser(const std::string& inputString)
{
	std::string result = "";
	for (const char& letter : inputString)
	{
		result += this->encryptCharacter(std::tolower(letter));
	}
	std::cout << result;
	return result;
}

char Anigma::encryptCharacter(char let)
{
	if (let < 'a' or let > 'z')
		return let; ///check if char is a letter that needs encryption or a regular char.

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

Anigma::~Anigma()
{
	std::string plugBoardSettings = getPlugBoardSettings();
	for (auto& rotor : _rotors)
	{
		delete rotor;
	}
	_plugBoard.clear();
	std::fstream file(_filePath);
	file << plugBoardSettings;
	file.close();
}

std::string Anigma::getPlugBoardSettings()
{
	std::stringstream settingStream;
	settingStream << "~{";
	for (const auto& pair : this->_plugBoard)
	{
		if(pair.first != 'z')
		{
			settingStream << pair.first << ":" << pair.second << ", ";
			continue;
		}
		settingStream << pair.first << ":" << pair.second << "}\n";
	}
	return settingStream.str();
}


int main()
{
	Anigma* anigma = new Anigma();
	anigma->start();
}
