#include "location.h"
//#include "common.h"
using namespace std;
vector<string> g_locations;
void location::readLocations() {
	char filename[] = "locations.txt";
	fstream newFile;

	newFile.open(filename, std::fstream::in | std::fstream::out);


	// If file does not exist, Create new file
	if (!newFile)
	{
		//if file does not exists, this block will create file with some default values

		newFile.open(filename, fstream::in | fstream::out | fstream::trunc);
		newFile << "Conference Room 1\nConference Room 2\nMini Conference Room\nTown Hall";
		g_locations.push_back("Conference Room 1");
		g_locations.push_back("Conference Room 2");
		g_locations.push_back("Mini Conference Room");
		g_locations.push_back("Town Hall");
		newFile.close();
		return;
	}

	if (newFile.is_open()) {

		//newFile.open(filename, std::fstream::in | std::fstream::out);
		std::string tp;
		while (getline(newFile, tp)) {
			if(tp!="")
				g_locations.push_back(tp);
		}
		newFile.close(); //close the file object.
	}

}
void location::readLocationsVerify() {
	vector<string> temp;
	for (auto i : g_locations) {
		if (!i.size()!=0)
			temp.push_back(i);
	}
	g_locations.clear();
	g_locations = temp;
}