#pragma once
#include "Meeting.h"
#include "participant.h"
#include <ctime>
using namespace std;
vector<Meetings> g_Meets; 
//vector<Employees> g_EmpArr;
vector<Participants> g_participants;

//dateFormater format the string into date structure
date dateFormater(std::string dateString) {
    date dStruct;
    dStruct.day = stoi(dateString.substr(0, 2));
    dStruct.month = stoi(dateString.substr(2, 2));
    dStruct.year = stoi(dateString.substr(4, 4));
    return dStruct;
}

//This function verify that input date format is correct
bool verifyDateFormat(std::string inputDate, std::string out)
{
    size_t size = inputDate.size();
    out = "";
    date d = dateFormater(inputDate);

    if (size != 8) out = "\nWrong date format!!";
    if (d.day > 31) out = "\nDate cannot be greater than 31";
    if (d.day > 12) out = "\nMonth cannot be greater than 12";
    if (d.day < 2022) out = "\nYear cannot be less than 2022";

    if (out == "")
        return true;
    else
        return false;
}

string Meeting::writeline() {

    string line = "";
    for (auto i : g_Meets) {
        line.append(to_string(i.meetID));
        line.append(",");
        line.append(to_string(i.orgEmpID));
        line.append(","); 
        line.append(i.desc);
        line.append(",");
        line.append(i.date);
        line.append(",");
        line.append(to_string(i.duration));
        line.append(",");
        line.push_back(i.status);
        line.append(",");
        line.append(i.location);
        //line.append(to_string(i.response)); 
        line.append(",");
        line.append(to_string(i.participants) + "\n");
    }
    return line;
}
bool Meeting::writeMeets() {
    
    char filename[] = "meetings.txt";
    fstream appendFileToWorkWith;

    appendFileToWorkWith.open(filename, std::fstream::in | std::fstream::out);


    // If file does not exist, Create new file
    if (!appendFileToWorkWith)
    {
        cout << "Cannot open file, file does not exist. Creating new file..";

        appendFileToWorkWith.open(filename, fstream::in | fstream::out | fstream::trunc);
        appendFileToWorkWith << writeline();
        appendFileToWorkWith.close();

    }
    else
    {    // use existing file
        cout << "success " << filename << " found. \n";
        cout << "\n Appending writing and working with existing file" << "\n---\n";

        appendFileToWorkWith << writeline();
        appendFileToWorkWith.close();
        cout << "\n ";
    }
    return true;
}
bool Meeting::readMeets() {
    
    if (!g_Meets.empty())
        return true;
        fstream newfile;
        //newfile.open("employees.txt", ios::out);  // open a file to perform write operation using file object
        //if (newfile.is_open()) //checking whether the file is open
        //{
        //    newfile << "Tutorials point \n";   //inserting text
        //    newfile.close();    //close the file object
        //}
        newfile.open("meetings.txt", std::ios::in);
        if (newfile.is_open()) {

            std::string tp;
            while (getline(newfile, tp)) {
                Meetings etemp;
                vector<std::string> v;
                stringstream ss(tp);

                if (tp.empty())
                    break;

                while (ss.good()) {
                    std::string substr;
                    getline(ss, substr, ',');
                    v.push_back(substr);
                }
                etemp.meetID= std::stoi(v[0]);
                etemp.orgEmpID = std::stoi(v[1]);
                etemp.desc = v[2];
                etemp.date = v[3];
                etemp.duration = std::stoi(v[4]);
                etemp.status = v[5][0];
                etemp.location = v[6];
                etemp.participants = std::stoi(v[7]);

                g_Meets.push_back(etemp);
            }
            newfile.close(); //close the file object.
        }
        else {
            outMsg = "No Scheduled Meeting";
            return false;
        }
        sort(g_Meets.begin(), g_Meets.end(), [](Meetings a, Meetings b) {
            return a.meetID < b.meetID;
            });
        return true;
}

//Schedules Meeting
bool Meeting::schedMeet() {
    Meetings temp;
    int meetID;
    //auto increments Meeting ID
    if (g_Meets.empty())
        meetID = 0001;
    else
        meetID = g_Meets.back().meetID + 1;
    cout << "\n Meeting ID: " << meetID;
    temp.meetID = meetID;
    cout << "\n Organizer Employee ID: " << m_empID;
    temp.orgEmpID = m_empID;
    cout << "\n Enter Description: ";
    
    //As description can contain spaces and other symbols
    //cin cannot capture all the characters
    //Solution: get the whole line using geline()
    cin.ignore();
    getline(cin, temp.desc);

    cout << "Enter Date(DDYYYYYY): ";
    cin >> temp.date;
    {
        string out;
        if (!verifyDateFormat(temp.date, out))
        {
            cout << out;
            return false;
        }
    }

    cout << "Enter duration of meeting in hrs: ";
    cin >> temp.duration;
    temp.status = 'S';//Default value 'S' for scheduled
    {
        cout << "\n \tLocations available: ";
        for (int i = 1 ; i <= g_locations.size(); i++)
            cout << "\n \t" << i << ". " << g_locations[i-1];

        cout << "\n\n Enter location index: ";
        int index;
        cin >> index;
        temp.location = g_locations[index-1];
    }

    //takes particpants number
    cout << "\n Enter no. of participants: ";
    int participantsNo;
    cin >> participantsNo;
    temp.participants = participantsNo;
    g_Meets.push_back(temp);
    writeMeets();

    //getting particpants details one by one
    std::cout << "\n Participants Details: \n\nAvailable Participants:\n\n\tEmployee ID\tName";
    for (auto i : g_EmpArr) {
        cout << "\n \t\t" << i.eID << "\t" << i.Name;
    }

    
    for (int i = 0; i < participantsNo; i++) {
        cout << i+1 << "\n\n Attendee No. " << i + 1;
        Participants part;
        part.meetID = meetID;
        cout << "\n Enter attending employees id: ";
        cin >> part.empID;

        //Pushing new participants in the list
        g_participants.push_back(part);
    }

    //writing updated g_participants in file
    participant obj;
    obj.writeParticipants(g_participants);
    cout << "\n Participants recorded successfully ";
    return true;
}

//Display all meetings organized by login user
void Meeting::displayMeets() {
    vector<Meetings> temps;
    for (auto i : g_Meets) {
        if (i.orgEmpID == m_empID)
            temps.push_back(i);
    }
    if (temps.empty())
        cout << "\n No meetings scheduled";
    else {
        cout << "\n\n Meetings: Meeting ID\n ";
        for (int i = 1; i <= temps.size(); i++) {
            cout << "\t\t" << temps[i - 1].meetID << endl;
        }
        cout << "\n Enter meeting ID from above list to view details: ";
        int index;
        cin >> index;
        for (auto i : temps) {
            if (i.meetID == index) {
                cout << "\n \tMeeting ID: " << i.meetID;
                cout << "\n \tOrganizer Employee ID: " << i.orgEmpID;
                cout << "\n \tDate: " << i.date;
                cout << "\n \tDescription: " << i.desc;
                cout << "\n \tMeeting Duration: " << i.duration;
                cout << "\n \tParticipants: " << i.participants;
            }
        }

        //printing participants details
        {
            
            if (!g_participants.empty()) {
                for (auto i : g_participants) {
                    if (i.meetID == temps[index - 1].meetID) {
                        cout << "\n\n Employee ID: " << i.empID;
                        //if(g_EmpArr.)
                        //cout << "\n Employee Name: " << ;
                        cout << "\n Notified: " << i.notified;
                        cout << "\n Response: " << i.response;
                        cout << "\n Response Type: " << i.responseType;
                    }

                }
            }

        }
    }
}

bool Meeting::cancelMeet()
{
    vector<Meetings> temp;
    for (auto i : g_Meets) {
        if (i.orgEmpID == m_empID)
            temp.push_back(i);
    }
    if (temp.empty()) {
        cout << "\n No meeting to cancel" << endl;
        return false;
    }

    cout << "\n Meetings organized by " << m_empID << ": \n";
    cout << "\n Meeting ID\tDescription\n";
    for (auto i : temp) {
        cout << i.meetID << "\t\t" << i.desc<<endl;
    }
    cout << "\n Enter Meeting ID to cancel: ";
    int meet2cancel;
    cin >> meet2cancel;
    cout << "\n\n Are you sure you want to cancel " << meet2cancel << " meeting?(Y/N): ";
    char ch = _getch();

    if(ch == 'n' || ch == 'N')
	{

		vector<Meetings> new_meets;
		for (auto i : g_Meets) {
			if (i.meetID != meet2cancel)
				new_meets.push_back(i);
		}
		g_Meets = new_meets;
		writeMeets();


		vector<Participants> new_participants;
		for (auto i : g_participants) {
			if (i.meetID != meet2cancel)
				new_participants.push_back(i);
		}
		g_participants = new_participants;
		participant part;
		part.writeParticipants(g_participants);

		cout << "\n\n Meeting " << meet2cancel << " cancelled.";

	}
    return true;
}


void Meeting::displayMeets(std::string startDate, std::string endDate) {
    
    if (startDate.size() != 8 || endDate.size() != 8) {
        cout << "\n\n \tEnter Dates in correct format!!";
        return;
    }

    date start = dateFormater(startDate); 
    date end = dateFormater(endDate);


    std::vector<Meetings> meets;

    for (auto i : g_Meets) {
        date d = dateFormater(i.date);
        /*if (i.orgEmpID == m_empID) {
            if (start.year == d.year && d.year == end.year) {
                if (start.month == d.month && d.month == end.month) {
                    if (start.day <= d.day && d.day <= end.day) {
                        meets.push_back(i);
                    }
                }
                else if (start.month <= d.month && d.month < end.month || start.month < d.month && d.month <= end.month){
                    meets.push_back(i);
                }
            }
            else if (start.year <= d.year && d.year < end.year || start.year < d.year && d.year <= end.year) {
                meets.push_back(i);
                
            }
        }*/
        if (d.year > start.year && d.year < end.year)
        {
            meets.push_back(i);
        }
        else if (d.year == start.year)
        {
            if (d.month > start.month)
            {
                meets.push_back(i);
            }
            else if (d.month == start.month)
            {
                if (d.day >= start.day)
                {
                    meets.push_back(i);
                }
            }
        }
        else if (d.year == end.year)
        {
            if (d.month < end.month)
            {
                meets.push_back(i);
            }
            else if (d.month == end.month)
            {
                if (d.day <= end.day)
                {
                    meets.push_back(i);
                }
            }
        }
    }
    
    std::cout << "\n Meetings between " << start.day << "/" << start.month << "/" << start.year << " and " << end.day << "/" << end.month << "/" << end.year << ": ";
    std::cout << "\n\n";
    for (auto i : meets) {
        date d = dateFormater(i.date);
        std::cout << "\n \tMeeting Date\t" << d.day<<"/"<<d.month<<"/"<<d.year<<endl
            << "\n\tMeeting ID\t" << i.meetID
            <<"\n\tDescription\t" << i.desc 
            << "\n\tLocation\t" << i.location;
    }
}