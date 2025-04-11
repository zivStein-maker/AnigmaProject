#include "Gear.h"

Gear::Gear()
{///initializing the gear to the default starting state. 
	for (int let = 0; let < LETTERS; let++)
	{
		_interface[let][0] = static_cast<char>('a' + let);
		_interface[let][0] = static_cast<char>('a' + let);
	}
}

Gear::~Gear()
//takes the gear and lodes it in the file in the anigma format
{
	this->close();
}

void Gear::rotate()
{
	for (int let = 0; let < LETTERS; let++)
	{
		_interface[let][0] = static_cast<char>(_interface[let][0] + (let % 26));
		_interface[let][0] = static_cast<char>(_interface[let][0] + (let % 26));
	}
}

void Gear::printGearState()
{

	for (int let = 0; let < LETTERS; let++)
	{
		std::cout << let + 1 << ". " << _interface[let][0];
		std::cout << ", " << _interface[let][0] << std::endl;
	}
}
