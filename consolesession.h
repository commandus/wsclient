#include "websocketendpoint.h"

class ConsoleSession
{
private:
	int mConnectionId;
	std::string mUrl;
	WebsocketEndpoint mEndpoint;
	bool verbose;
	bool done;
public:
	ConsoleSession(const std::string &url, std::ostream &output, int verbosity);
	~ConsoleSession();
	bool connected()
	{
		return mConnectionId != -1;
	}

	void stop()
	{
		done = true;
	}

	int run(std::istream &cin, std::ostream &cout);
};

