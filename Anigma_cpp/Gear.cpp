#include "Gear.h"
#include <sstream>
#include <fstream>



Gear::Gear(const std::string& filePath, gearType type)
{///initializing the gear to the default starting state. 
	this->_type = type;
	this->settingsFile = filePath;
	for (int let = 0; let < LETTERS; let++)
	{
		_interface[let][0] = static_cast<char>('a' + let);
		_interface[let][1] = static_cast<char>('a' + let);
	}
}

Gear::Gear(const std::string& filePath, const std::string& password)
{
	//const std::string settings = decryptSettings(password);

}

Gear::~Gear()
//takes the gear and lodes it in the file in the anigma format
{
	const std::string gearSettings = getGearSettings();
	std::fstream file(this->settingsFile);
	file << gearSettings;
	file.close();
}

void Gear::rotate()
{
	for (int let = 0; let < LETTERS; let++)
	{
		_interface[let][0] = (_interface[let][0] - 'a' + 1) % 26 + 'a';
	}
}

void Gear::printGearState()
{

	for (int let = 0; let < LETTERS; let++)
	{
		std::cout << let + 1 << ". " << _interface[let][0];
		std::cout << ", " << _interface[let][1] << std::endl;
	}
}

const std::string Gear::encryptSettings(const std::string& password)
{
	const std::string planeSettings = getGearSettings();

}

const std::string Gear::decryptSettings(const std::string& password)
{
	
}

const std::string Gear::getGearSettings()
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

