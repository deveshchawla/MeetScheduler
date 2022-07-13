# MeetScheduler 
A command line Meeting Management System which allows user to create, manage and notify meetings to other users of the system. 

This mini project implements various OOPS concepts. The application uses info stored in specific format in various txt files.

Features:
1. Schedule a Meeting.
2. Notify other participants of the meeting using there employee ID
3. Display all the future meetings of the logeed in user.
4. Cancel a meeting, only the organizer can cancel the meet.

# Instructions
To run the application, first compile all the files in the repository using following command

1. g++ MeetScheduler.cpp common.h location.cpp location.h Login.h Login.cpp Meeting.cpp notification.cpp notification.h participant.h participant.cpp ./Meet.exe

2. Open Meet.exe to run the application.

Note: Some precompiled header files will be created during the compilation process, which does affect any other files.
