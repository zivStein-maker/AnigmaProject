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

Gear::Gear(const std::string& filePath, const std::string& password, gearType type)
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
		_interface[let][1] = (_interface[let][1] - 'a' + 1) % 26 + 'a';
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
	return std::string();
}

const std::string Gear::decryptSettings(const std::string& password)
{
	return std::string();
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

int main()
{
	std::string path = "C:\\Users\\Cyber_User\\Desktop\\magsimim\\free_time_projects\\c_or_c++\\AnigmaProject\\Anigma_cpp\\settings.ang\\gear.ang";
	Gear* g1 = new Gear(path, "d", gearType::first);
	Gear* g2 = new Gear(path, "d", gearType::second);
	Gear* g3 = new Gear(path, "d", gearType::third);
	g1->printGearState();
	std::cout << std::endl << std::endl;
	g2->printGearState();
	std::cout << std::endl << std::endl;
	g3->printGearState();
}