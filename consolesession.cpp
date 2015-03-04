#include "consolesession.h"


ConsoleSession::ConsoleSession(const std::string &url, std::ostream &output, int verbosity) : mUrl(url), verbose(verbosity > 0), done(false), mEndpoint(output)
{
	mConnectionId = mEndpoint.connect(mUrl);
}

ConsoleSession::~ConsoleSession()
{
	mEndpoint.close(mConnectionId, 1, "exit");
}

int ConsoleSession::run(std::istream &cin, std::ostream &cout)
{
	ConnectionMetadata::ptr m = mEndpoint.getMetadata(mConnectionId);
	websocketpp::connection_hdl h = m->getHandler();
	
	std::string input;
	while (!done) {
		if (cin.eof())
			break;
		std::getline(cin, input);

		try
		{
			mEndpoint.mEndpoint.send(h, input, websocketpp::frame::opcode::text);
		}
		catch (websocketpp::exception &ex)
		{
			std::cerr << "Error " << ex.code() << std::endl;
		}
		
	}
	return 0;

}