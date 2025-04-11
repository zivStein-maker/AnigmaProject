#include "Gear.h"

Gear::Gear()
{
	for (int let = 0; let < LETTERS; let++)
	{
		
	}
}

Gear::~Gear()
//takes the gear and lodes it in the file in the anigma format
{
	this->close();
}
