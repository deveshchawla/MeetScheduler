#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <sstream>
#include <algorithm>
//extern string g_empID;

struct Employees
{
	int eID;//4
	std::string pwd;//10
	std::string Name;//50
	std::string Dept;//10
	std::string Mobile;//10
	std::string email;//30
	std::string skypeID;//20
};

extern std::vector<Employees> g_EmpArr;

struct Meetings
{
	int meetID;
	int orgEmpID;
	std::string desc;
	std::string date;
	int duration;
	char status = 'S';//'S'=Scheduled
	std::string location;//selected from locations.txt
	int participants;
};

extern std::vector<Meetings> g_Meets;

struct Participants
{
	int meetID;
	int empID;
	char notified = 'N';
	char response = 'N';
	std::string responseType = "None";//�None� initially, values = Attend, Reject, Maybe
};

extern std::vector<Participants> g_participants;

struct Notifications
{
	int meetID;
	int notificationID;
	int sendEmpID;
	int recEmpID;
	std::string text;
};

extern std::vector<Notifications> g_notifications;

extern std::vector<std::string> g_locations;

struct date {
	int day;
	int month;
	int year;
};



