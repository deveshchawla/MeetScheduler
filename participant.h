#include "common.h"

class participant
{
private:
	//std::vector<Participants> m_participants;
	std::string m_out;
	std::string writeline(std::vector<Participants> list);

public:
	void writeParticipants(std::vector<Participants> m_participants);
	void readParticipants();
};