#pragma once
#include "common.h"
class notification
{
private:
	std::string writeline(std::vector<Notifications> list);
	int m_empID;
public:
	void writeNotifications(std::vector<Notifications> list);
	void readNotifications();
	void sendNotifications();
	void sendReply();
	notification(int gempID) {
		m_empID = gempID;
	}
	void displayNotifications();
};