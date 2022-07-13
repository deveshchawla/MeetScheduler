// MyCalendar.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#pragma once
#include "common.h"
#include <Windows.h>
#include "Login.h"
#include "Meeting.h"
#include "participant.h"
#include "location.h"
#include "notification.h"
//#define TEST

using std::cout;
using std::cin;

//Global Employee ID variable used throughtout the program
int g_empID;

//once login is successfull, readData(std::string msg) will read all files and initialize gloabal variables
void readData(std::string msg){
    
    //initializing g_Meets
    Meeting meet(msg, g_empID);
    if (!meet.readMeets()) {
        cout << msg;
    }
    //initializing g_participants
    participant part;
    part.readParticipants();

    //initializing g_locations
    location loc;
    loc.readLocations();
    loc.readLocationsVerify();

    //initializing g_notifications
    notification noti(g_empID);
    noti.readNotifications();
    noti.displayNotifications();
}
date dateFormater(std::string dateString);
bool verifyDateFormat(std::string inputDate, std::string out);

int main()
{
    std::string msg;//to get error messages from functions, if any
#ifdef TEST
    Login login;
    if (!login.readFile()) {
        //cout << "Error reading file";
        //goto quit;
        return 0;
    }
    readData(msg);
    /*Meeting meet(msg, 1001);
    meet.displayMeets("02022022", "04032023");*/
    notification notify(1002);
    //notify.sendNotifications();
    notify.sendReply();
    notify.displayNotifications();
    _getch();
    return 0;
#else // TEST

    //Login class, where data is read from employee.txt, verify logging details
    Login login;
 
    if (!login.readFile()) {
        cout << "****Error reading employees.txt file****\n\nThe file may be missing or corrupted.";
        _getch();
        goto quit;
    }
    {
        std::string pswd, empID;
        bool success = false;
        while (!success) {
            cout << "\n -----------------------------------------------------------";
            cout << "\n \t\t\tMeetScheduler";
            cout << "\n -----------------------------------------------------------\n\n";
            cout << "\n -----------------------Login Screen------------------------\n";
            cout << "Enter Employee ID: ";
            cin >> empID;
            cout << "Enter Password: ";
            pswd.clear();
            char ch;
            while (true) {
                ch = _getch();
                if (ch == 13)//ASCII value of Enter Key
                    break;
                pswd.push_back(ch);
            }
            if(!login.infoValid(empID, pswd)){
                system("CLS");
                cout << "\n Login Failed: invalid username or password. Try Again\n";
                continue;
            }
            success = true;
            cout << "\n\n \t\tLogin Successful!";
            g_empID = stoi(empID);
        }
    }
    
    readData(msg);
    while (true) {
        // Options to choose an action
        cout << "\n\n --------------------------Menu---------------------------";
        cout << "\n ";
        cout << "\n \t1. Schedule Meeting";
        cout << "\n \t2. Send Notifications";
        cout << "\n \t3. Send Reply";
        cout << "\n \t4. Display Calender";
        cout << "\n \t5. Display Meeting";
        cout << "\n \t6. Cancel Meeting";
        cout << "\n \t0. Quit";
        cout << "\n ";
        cout << "\n\n    Enter your option: ";

        // Taking the action input
        int choice;
        std::cin >> choice;
        // Calling relevant function as per choice
        switch (choice) {
        case 0://Exit
            goto quit;
            break;
        case 1://Schedule Meeting
        {
            Meeting meet(msg, g_empID);
            meet.schedMeet();
        }
            break;
        case 2://Send Notifications
        {
            notification notify(g_empID);
            notify.sendNotifications();
        }
            break;
        case 3://Send Reply
        {
            notification notify(g_empID);
            notify.sendReply();
        }
            break;
        case 4://Display Calender
        {
            std::string start, end;
            cout << "\n \t Enter Start Date in format (DDMMYYYY): ";
            cin >> start;
            {
                std::string out;
                if (!verifyDateFormat(start, out))
                {
                    cout << out;
                    break;
                }
            }
            cout << "\n \t Enter End Date in format (DDMMYYYY): ";
            cin >> end;
            {
                std::string out;
                if (!verifyDateFormat(end, out))
                {
                    cout << out;
                    break;
                }
            }
            Meeting meet(msg, g_empID);
            meet.displayMeets(start, end);
        }
            break;
        case 5://Display Meetings
        {
            Meeting meet(msg, g_empID);
            meet.displayMeets();

        }
            break;
        case 6://Cancel Meeting
        {
            Meeting meet(msg, g_empID);
            meet.cancelMeet();
        }
        break;
        default:
            cout << "\n  Wrong Input! \n";
            break;
        }
        //system("cls");
    }
quit:
    //system("CLS");
    cout << "\n\n MeetScheduler - Meetings Management System";
    Sleep(10);
    return 0;
#endif
}