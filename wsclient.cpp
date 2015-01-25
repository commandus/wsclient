#include "wsclient.h"
#include "consolelocale.h"

const char* progname = "wsclient";

ConsoleSession *session;

void onStop(int signal)
{
	session->stop();
	exit(signal);
}

int main(int argc, char* argv[])
{
	struct arg_str  *a_url = arg_strn(NULL, NULL, "<url>", 1, 0, "e.g. ws://localhost:8084/");
	struct arg_lit  *a_verbose = arg_lit0("v", "verbose", "connection messages to stderr");
	struct arg_str  *a_locale = arg_str0("l", "locale", "<locale>", "e.g. russian_russia.1251, ru_RU.UTF-8");
#ifdef WIN32
	struct arg_lit  *a_locale_utf8 = arg_lit0("u", "utf8", "locale use UTF-8");
#endif
	struct arg_lit  *a_help = arg_lit0("h", "help", "print this help and exit");
	struct arg_end  *a_end = arg_end(20);
	void* argtable[] = { a_url, a_verbose,
		a_locale, 
#ifdef WIN32
		a_locale_utf8,
#endif
		a_help, a_end };
	int nerrors;
	/* verify the argtable[] entries were allocated sucessfully */
	if (arg_nullcheck(argtable) != 0)
	{
		std::cerr << "insufficient memory" << std::endl;
		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
		return 1;
	}
	/* Parse the command line as defined by argtable[] */
	nerrors = arg_parse(argc, argv, argtable);

	/* special case: '--help' takes precedence over error reporting */
	if ((a_help->count > 0) || (a_url->count == 0))
	{
		std::cout << "Usage " << progname << std::endl;
		arg_print_syntax(stdout, argtable, "\n");
		std::cout << "websocket CLI client" << std::endl;
		arg_print_glossary(stdout, argtable, "  %-25s %s\n");
		arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
		return 0;
	}
	if (a_locale->count > 0) 
	{
		bool utf8 = false;
#ifdef WIN32
		utf8 = a_locale_utf8->count > 0;
#endif
		ConsoleLocale(std::string(*a_locale->sval), utf8);
	}
	int verbosity = a_verbose->count;
	std::string url(*a_url->sval);
	arg_freetable(argtable, sizeof(argtable) / sizeof(argtable[0]));
	
	session = new ConsoleSession(url, std::cerr, verbosity);
	if (!session->connected())
	{
		std::cerr << "Error connect to " << url << std::endl;
		return 2;
	}

	SignalHandler sh(std::cerr, onStop);

	int r = session->run(std::cin, std::cout);
	delete session;
	if (verbosity)
		std::cout << "Done" << std::endl;
}

