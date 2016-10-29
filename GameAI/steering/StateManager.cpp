#include "StateManager.h"
#include <fstream>
#include <string>
#include <cctype>

//save current weights in correct format to the save file
void StateManager::saveData() const
{
	std::ofstream file;
	file.open("save_data.txt");

	file << mAlignmentWeight << std::endl
		<< mCohesionWeight << std::endl
		<< mSeperationWeight;

	file.close();
}

//loads data from text file and validates input
void StateManager::loadData()
{
	std::ifstream file("save_data.txt");
	std::string tmp;

	//each input from text file is validated to see if it is a float
	//if input from text file isn't a valid format default values are used
	//otherwise the values from text file are used
	if (file.is_open())
	{
		std::getline(file, tmp);		
		if (isFloat(tmp))
			mAlignmentWeight = std::stof(tmp);

		std::getline(file, tmp);
		if (isFloat(tmp))
			mCohesionWeight = std::stof(tmp);

		std::getline(file, tmp);
		if (isFloat(tmp))
			mSeperationWeight = std::stof(tmp);

		file.close();
	}
}

//checks if given string is a float
//this definition of float just checks is all characters are either a number or a .
bool StateManager::isFloat(const std::string& str) const
{
	for (size_t i = 0; i < str.size(); ++i)
	{
		if (str[i] != '.' && !isdigit(str[i])) return false;
	}
	return true;
}