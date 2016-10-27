#include "StateManager.h"
#include <fstream>

void StateManager::saveData()
{
	std::ofstream file;
	file.open("save_data.txt");

	file << mAlignmentWeight << std::endl
		<< mCohesionWeight << std::endl
		<< mSeperationWeight;

	file.close();
}

void StateManager::loadData()
{
	std::ifstream file("save_data.txt");

	if (file.is_open())
	{
		file >> mAlignmentWeight
			>> mCohesionWeight
			>> mSeperationWeight;

		file.close();
	}
}