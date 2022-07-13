#pragma once
#include "common.h"
class Meeting
{
private:
	std::string outMsg;
	int m_empID;
public:
	bool schedMeet();
	bool cancelMeet();
	bool readMeets();
	bool writeMeets();
	void displayMeets();
	void displayMeets(std::string startDate, std::string endDate);
	std::string writeline();
	Meeting(std::string msg, int empID) {
		outMsg = msg;
		m_empID = empID;
	}
};