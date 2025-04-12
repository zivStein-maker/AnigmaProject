#include "Gear.h"

Gear::Gear(gearType type)
{///initializing the gear to the default starting state. 
	this->_type = type;
	for (int let = 0; let < LETTERS; let++)
	{
		_interface[let][0] = static_cast<char>('a' + let);
		_interface[let][1] = static_cast<char>('a' + let);
	}
}

Gear::Gear(const std::string& filePath, const std::string& password)
{
	const std::string settings = decryptSettings(password);

}

Gear::~Gear()
//takes the gear and lodes it in the file in the anigma format
{
	//this->close();
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
	
}

const std::string Gear::decryptSettings(const std::string& password)
{
	
}

