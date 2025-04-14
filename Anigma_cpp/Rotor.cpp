#include "Rotor.h"
#include <sstream>
#include <fstream>



Rotor::Rotor(const std::string& filePath, char type)
{///initializing the Rotor to the default starting state. 
	this->_type = type;
	this->settingsFile = filePath;
	for (int let = 0; let < LETTERS; let++)
	{
		_interface[let][0] = static_cast<char>('a' + let);
		_interface[let][1] = static_cast<char>('a' + let);
	}
}

Rotor::Rotor(const std::string& filePath, const std::string& password, char type)
{
	//const std::string settings = decryptSettings(password);
	this->_type = type;
	this->settingsFile = filePath;
	std::fstream file(filePath);
	std::string settings = "";
	while (std::getline(file, settings))
	{
		if (settings[0] == (type))
			break;
	}
	for (int i = 0; i < LETTERS; i++)
	{
		std::string finder = "";
		finder += static_cast<char>('a' + i);
		finder += ':';
		this->_interface[i][0] = static_cast<char>('a' + i);
		this->_interface[i][1] = settings[settings.find(finder) + finder.length()];
	}
}

Rotor::~Rotor()
//takes the Rotor and lodes it in the file in my anigma format
{
	const std::string rotorSettings = getRotorSettings();
	std::fstream file(this->settingsFile);
	file << rotorSettings;
	file.close();
}

char Rotor::getFirstOutput(char let) const
{
	for (int i = 0; i < LETTERS; i++)
	{
		if (_interface[i][0] == let)
			return _interface[i][1];
	}
	return let;
}

char Rotor::getSecondOutput(char let) const
{
	for (int i = 0; i < LETTERS; i++)
	{
		if (_interface[i][1] == let)
			return _interface[i][0];
	}
	return let;
}

bool Rotor::rotate()
{
	for (int let = 0; let < LETTERS; let++)
	{
		_interface[let][1] = (_interface[let][1] - 'a' + 1) % 26 + 'a';
	}
	return _interface[0][0] == _interface[0][1];
}

void Rotor::printRotorState()
{

	for (int let = 0; let < LETTERS; let++)
	{
		std::cout << let + 1 << ". " << _interface[let][0];
		std::cout << ", " << _interface[let][1] << std::endl;
	}
}

const std::string Rotor::encryptSettings(const std::string& password)
{
	const std::string planeSettings = getRotorSettings();
	return std::string();
}

const std::string Rotor::decryptSettings(const std::string& password)
{
	return std::string();
}

const std::string Rotor::getRotorSettings()
{
	std::stringstream settingsStream;
	settingsStream << _type << "{";
	for (int i = 0; i < LETTERS; i++)
	{
		if (i != LETTERS - 1)
		{
			settingsStream << _interface[i][0] << ":" << _interface[i][1] << ", ";
			continue;
		}
		settingsStream << _interface[i][0] << ":" << _interface[i][1] << "}\n";
	}
	return settingsStream.str();
}

