#include "notification.h"
#include "participant.h"
std::vector<Notifications> g_notifications;
using namespace std;
void notification::readNotifications() {

	std::fstream newfile;
	newfile.open("notifications.txt", std::ios::in);
	if (newfile.is_open()) {

		std::string tp;
		while (getline(newfile, tp)) {
			Notifications etemp;
			std::vector<std::string> v;
			std::stringstream ss(tp);

			if (tp.empty())
				break;

			while (ss.good()) {
				std::string substr;
				getline(ss, substr, ',');
				v.push_back(substr);
			}
			etemp.meetID = stoi(v[0]);
			etemp.notificationID = stoi(v[1]);
			etemp.sendEmpID = stoi(v[2]);
			etemp.recEmpID = stoi(v[3]);
			etemp.text = v[4];

			g_notifications.push_back(etemp);
		}
		newfile.close(); //close the file object.
	}
}

void notification::writeNotifications(std::vector<Notifications> list) {
	char filename[] = "notifications.txt";
	std::fstream appendFileToWorkWith;

	appendFileToWorkWith.open(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);


	// If file does not exist, Create new file
	if (!appendFileToWorkWith)
	{
		std::cout << "Cannot open file, file does not exist. Creating new file..";

		appendFileToWorkWith.open(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);
		appendFileToWorkWith << writeline(list);
		appendFileToWorkWith.close();

	}
	else
	{    // use existing file
		//cout << "success " << filename << " found. \n";
		//cout << "\n Appending writing and working with existing file" << "\n---\n";

		appendFileToWorkWith << writeline(list);
		appendFileToWorkWith.close();
		std::cout << "\n ";
	}
}

std::string notification::writeline(std::vector<Notifications> list) {

	std::string line = "";
	for (auto i : list) {
		line.append(std::to_string(i.meetID));
		line.append(",");
		line.append(std::to_string(i.notificationID));
		line.append(",");
		line.append(std::to_string(i.sendEmpID));
		line.append(",");
		line.append(std::to_string(i.recEmpID));
		line.append(",");
		line.append(i.text + "\n");
	}
	return line;
}

//Sends notification to employees choosen by organizer of the meeting
void notification::sendNotifications() {
	
	//meets contains the meeting which has not been notified yet
	vector<Meetings> meets;
	for (auto i : g_Meets) {
		if (i.orgEmpID == m_empID) {
			for (auto j : g_participants) {
				if (i.meetID == j.meetID && j.notified == 'N')
					meets.push_back(i);

			}
		}
	}

	//If no meeting is there to notified, function returns
	if (meets.empty()) {
		cout << "\n \tNo Meetigs to send notification for.";
		return;
	}
	{
		//this block is serves as removing duplicate entries in meets variables
		vector<Meetings> temp;
		temp.push_back(meets[0]);
		for (auto i : meets) {
			bool flag = false;
			for (auto j : temp) {
				if (j.meetID == i.meetID)
				{
					flag = true;
					break;
				}
			}
			if (!flag)
				temp.push_back(i);
		}
		meets.clear();
		meets = temp;
	}

	cout << "\n Meetings Not Notified yet\n\n\tMeeting ID\tDescription";
	for (auto i : meets)
		cout << "\n \t" << i.meetID << "\t\t " << i.desc;

	cout << "\n\n Enter Meet ID from above list to send notification: ";
	int meetid;
	cin >> meetid;
	{
		//checks if meetid input is correct or not
		bool flag = false;
		for (auto i : meets)
		{
			if (i.meetID == meetid)
			{
				flag = true;
				break;
			}
		}
		if (!flag)
		{
			cout << "\n \tEnter correct meeting id.";
			return;
		}
	}

	//Push notification entry in the g_notification variable
	//and then write it in the file
	Notifications notify;
	notify.meetID = meetid;
	
	//auto increament notification ID
	if (g_notifications.empty())
		notify.notificationID = 0001;
	else
		notify.notificationID = g_notifications[g_notifications.size() - 1].notificationID + 1;

	//sendEmpID, is notification senders ID, which is the login user/meeting organizer
	notify.sendEmpID = m_empID;

	//Now getting the employee id of who will receive the notification
	int employeeid;
	{
		cout << "\n Enter Employee ID from list to send notification to: \n\n\tEmployee ID ";
		for (auto i : g_participants) {
			if (i.meetID == meetid && i.notified == 'N')
				cout << "\n \t" << i.empID;
		}
		cout << "\n Enter Employee ID: ";
		cin >> employeeid;
		notify.recEmpID = employeeid;
	}

	//Text field in notification record which contains
	//data in from <meeting id>-<date of meeting>-<location of meeting>
	notify.text = to_string(meetid) + "-";
	for (auto i : g_Meets) {
		if (i.meetID == meetid) {
			notify.text.append(i.date + "-" + i.location);
			break;
		}
	}
	g_notifications.push_back(notify);
	writeNotifications(g_notifications);

	{
		//this block changes in participants notified from 'N' to 'Y'
		vector<Participants> temp;
		for (auto i : g_participants) {
			if (i.meetID == meetid && i.empID == employeeid) {
				i.notified = 'Y';
			}
			temp.push_back(i);
		}
		g_participants.clear();
		g_participants = temp;
	}
	{
		participant part;
		part.writeParticipants(g_participants);
	}

	cout << "\n\n Notification sent!";

}


void notification::sendReply() {

	vector<Notifications> temp;
	
	//collects notification which is received but not replied
	for (auto i : g_notifications) {
		if (i.recEmpID == m_empID) {
			for (auto j : g_participants) {
				if (j.empID == m_empID && j.notified == 'Y' && j.response == 'N') {
					temp.push_back(i);
				}
			}
		}
	}

	//unique(temp.begin(), temp.end());
	if (temp.empty()) {
		cout << "\n No Notification to send reply.";
		return;
	}
	
	//Displays all notification
	displayNotifications();

	cout << "\n\n Enter Notification ID to reply: ";
	int notifyID;
	cin >> notifyID;
	//apply input check
	Notifications singleNoti;
	for (auto i : temp) {
		if (i.notificationID == notifyID) {
			singleNoti = i;
			break;
		}
	}

	string reply;

	cout << "\n Enter reply for  " << singleNoti.meetID << " to " << singleNoti.sendEmpID << "(Attend/Reject/Maybe): ";
	cin >> reply;
	{
		vector<Participants> tem;
		for (auto i : g_participants) {
			if (i.meetID == singleNoti.meetID && i.empID == m_empID) {
				i.response = 'Y';
				i.responseType = reply;
			}
			tem.push_back(i);
		}
		g_participants.clear();
		g_participants = tem;

		participant part;
		part.writeParticipants(g_participants);
	}
	{
		vector<Notifications> temp1;

		for (int i = 0; i < g_notifications.size(); i++) {
			if (g_notifications[i].notificationID != notifyID)
				temp1.push_back(g_notifications[i]);
		}
		g_notifications.clear();
		g_notifications = temp1;

	}

	writeNotifications(g_notifications);

}

void notification::displayNotifications() {
	/*if (g_notifications.empty()) {
		cout << "\n No Notifications";
		return;
	}*/
	vector<Notifications> temp;
	for (auto i : g_notifications) {
		if (i.recEmpID == m_empID) {
			temp.push_back(i);
		}
	}
	if (temp.empty()) {
		cout << "\n No Notifications";
		return;
	}

	cout << "\n\n Notifications:\nID\tFrom\tDescription(MeetID-Date-Location)";
	for (auto i : temp) {
		cout << "\n " << i.notificationID << "\t" << i.sendEmpID << "\t" << i.text;
	}

}