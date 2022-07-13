#include "participant.h"
//#include "common.h"
using namespace std;

string participant::writeline(vector<Participants> list) {

    string line = "";
    for (auto i : list) {
        line.append(to_string(i.meetID));
        line.append(",");
        line.append(to_string(i.empID));
        line.append(",");
        line.push_back(i.notified);
        //line.append(1,i.notified);
        line.append(",");
        line.push_back(i.response);
        //line.append(to_string(i.response)); 
        line.append("," );
        line.append(i.responseType + "\n");
    }
    return line;
}

void participant::writeParticipants(vector<Participants> list) {
    char filename[] = "participants.txt";
    fstream appendFileToWorkWith;

    appendFileToWorkWith.open(filename, std::fstream::in | std::fstream::out | std::fstream::trunc);


    // If file does not exist, Create new file
    if (!appendFileToWorkWith)
    {
        cout << "Cannot open file, file does not exist. Creating new file..";

        appendFileToWorkWith.open(filename, fstream::in | fstream::out | fstream::trunc);
        appendFileToWorkWith << writeline(list);
        appendFileToWorkWith.close();

    }
    else
    {    // use existing file
        //cout << "success " << filename << " found. \n";
        //cout << "\n Appending writing and working with existing file" << "\n---\n";

        appendFileToWorkWith << writeline(list);
        appendFileToWorkWith.close();
        cout << "\n ";
    }
}

void participant::readParticipants() {

    fstream newfile;
    newfile.open("participants.txt", std::ios::in);
    if (newfile.is_open()) {

        std::string tp;
        while (getline(newfile, tp)) {
            Participants etemp;
            vector<std::string> v;
            stringstream ss(tp);
            
            if (tp.empty())
                break;

            while (ss.good()) {
                std::string substr;
                getline(ss, substr, ',');
                v.push_back(substr);
            }
            etemp.meetID = stoi(v[0]);
            etemp.empID = stoi(v[1]);
            etemp.notified = v[2][0];
            etemp.response = v[3][0];
            etemp.responseType = v[4];

            g_participants.push_back(etemp);
        }
        newfile.close(); //close the file object.
    }
    
}