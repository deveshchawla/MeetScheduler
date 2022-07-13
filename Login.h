#pragma once
#include "common.h"

class Login
{

public:
	bool readFile();
	bool infoValid(std::string empID, std::string pwd);
};
