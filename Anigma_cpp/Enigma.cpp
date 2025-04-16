#include "Enigma.h"
#include <sstream>
#include <fstream>
#include <random>


Enigma::Enigma()
{
	this->_rotorAmount = DEFAULT_AMOUNT;
	_filePath = "../../settings/settings.ang";
	_plugBoard = generateRandomMapping();
	_reflector = generateRandomMapping();

	for (int i = 0; i < _rotorAmount; i++)
	{
		_rotors.emplace_back(new Rotor(_filePath, static_cast<char>(i)));
	}
}

Enigma::Enigma(const std::string& filePath)
{
	std::fstream file(filePath);
	std::string line = "";
	std::string plugBoardSettings = "";
	std::string reflectorSettings = "";
	this->_filePath = filePath;
	this->_rotorAmount = DEFAULT_AMOUNT;

	for (int i = 0; i < _rotorAmount; i++)
	{
		_rotors.emplace_back(new Rotor(_filePath, static_cast<char>(i)));
	}
	while (std::getline(file, line))
	{
		if (line[0] == '~')
			plugBoardSettings = line;

		if (line[0] == '#')
			reflectorSettings = line;
	}
	setPlugBoardMapping(plugBoardSettings);
	setReflectorMapping(reflectorSettings);
	file.close();
}

Enigma::~Enigma()
{
	const std::string plugBoardSettings = getPlugBoardSettings();
	const std::string reflectorSettings = getReflectorSettings();
	for (auto& rotor : _rotors)
	{
		delete rotor;
	}
	_plugBoard.clear();
	std::ofstream file(_filePath);
	file << plugBoardSettings << std::endl;
	file << reflectorSettings << std::endl;
	file.close();
}

void Enigma::start()
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

std::string Enigma::parser(const std::string& inputString)
{
	std::string result = "";
	for (const char& letter : inputString)
	{
		result += this->encryptCharacter(std::tolower(letter));
	}
	std::cout << result << std::endl;
	return result;
}

char Enigma::encryptCharacter(char let)
{
	if (let < 'a' or let > 'z')
		return let; ///check if char is a letter that needs encryption or a regular char.

	this->move();
	char output = _plugBoard.at(let);
	for (auto& rotor : _rotors)
	{
		output = rotor->getFirstOutput(output);
	}
	output = _reflector[output];
	for (int i = _rotors.size() - 1; i >= 0; --i) 
	{
		output = _rotors[i]->getSecondOutput(output);
	}
	return output;
}

void Enigma::move()
{
	for (auto& rotor : _rotors)
	{
		if (!rotor->rotate())
			break;
	}
}

const std::string Enigma::getPlugBoardSettings()
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
		settingStream << pair.first << ":" << pair.second << "}";
	}
	return settingStream.str();
}

const std::string Enigma::getReflectorSettings()
{
	std::stringstream settingStream;
	settingStream << "#{";
	for (const auto& pair : this->_reflector)
	{
		if (pair.first != 'z')
		{
			settingStream << pair.first << ":" << pair.second << ", ";
			continue;
		}
		settingStream << pair.first << ":" << pair.second << "}";
	}
	return settingStream.str();
}

std::map<char, char> Enigma::generateRandomMapping()
{///generate a random symmetrical mapping for the reflector and plugboard
	std::vector<char> letters;
	std::map<char, char> mapping;
	std::random_device rd;
	std::mt19937 g(rd());


	for (char c = 'a'; c <= 'z'; ++c)
		letters.push_back(c);

	std::shuffle(letters.begin(), letters.end(), g);


	for (size_t i = 0; i < letters.size(); i += 2)
	{/// making the mapping symmetrical for the plugborad and reflector.
		char a = letters[i];
		char b = letters[i + 1];
		mapping[a] = b;
		mapping[b] = a;
	}

	return mapping;
}

void Enigma::setPlugBoardMapping(const std::string settings)
{
	for (char let = 'a'; let <= 'z'; let++)
	{
		std::string finder = "";
		finder += let;
		finder += ':';
		char result = settings[settings.find(finder) + finder.length()];
		_plugBoard[let] = result;
	}
}

void Enigma::setReflectorMapping(const std::string settings)
{
	for (char let = 'a'; let <= 'z'; let++)
	{
		std::string finder = "";
		finder += let;
		finder += ':';
		char result = settings[settings.find(finder) + finder.length()];
		_reflector[let] = result;
	}
}


int main()
{
	Enigma* e = new Enigma();
	e->start();
	delete e;
}
