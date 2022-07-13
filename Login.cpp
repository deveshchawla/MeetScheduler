#pragma once
#include "Login.h"
//using namespace std;
std::vector<Employees> g_EmpArr;

bool Login::readFile() {
		
        std::ifstream myfile("employees.txt");
        std::string mystring;

        if (myfile.is_open()) {
            std::fstream newfile;
            //newfile.open("employees.txt", ios::out);  // open a file to perform write operation using file object
            //if (newfile.is_open()) //checking whether the file is open
            //{
            //    newfile << "Tutorials point \n";   //inserting text
            //    newfile.close();    //close the file object
            //}
            newfile.open("employees.txt", std::ios::in);
            if (newfile.is_open()) {  
                
                std::string tp;
                while (getline(newfile, tp)) { 
                    Employees etemp;
                    std::vector<std::string> v;
                    std::stringstream ss(tp);

                    if (tp.empty())
                        break;

                    while (ss.good()) {
                        std::string substr;
                        getline(ss, substr, ',');
                        v.push_back(substr);
                    }
                    etemp.eID = std::stoi(v[0]);
                    etemp.pwd = v[1];
                    etemp.Name = v[2];
                    etemp.Dept = v[3];
                    etemp.Mobile = v[4];
                    etemp.email = v[5];
                    etemp.skypeID = v[6];

                    g_EmpArr.push_back(etemp);
                }
                newfile.close(); //close the file object.
            }
            
            return true;
        }
        else
            return false;
	}

    //return true if user found
    //return false if either eid or pwd is wrong 
bool Login::infoValid(std::string empID, std::string pwd) {
    for (auto i : g_EmpArr) {
            if (i.eID == std::stoi(empID)) {
                if (i.pwd == pwd)
                    return true;
            }
        }
        return false;
    }
