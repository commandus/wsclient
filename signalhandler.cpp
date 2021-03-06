#include "signalhandler.h"
#include <csignal>

static onStopHandler mOnStop(NULL);
static std::ostream *mcerr(NULL);

void SignalHandler::signal_SIGABRT_handler(int signum)
{
	*mcerr << "Signal abort " << signum << std::endl;
	signal(signum, SIG_DFL);
	abort();
}

void SignalHandler::signal_SIGFPE_handler(int signum)
{
	*mcerr << "Signal floating point exception " << signum << std::endl;
	signal(signum, SIG_DFL);
	exit(signum);
}

void SignalHandler::signal_SIGILL_handler(int signum)
{
	*mcerr << "Signal illegal instruction " << signum << std::endl;
	signal(signum, SIG_DFL);
	exit(signum);
}

/**
TODO intercept -9 and other signals.
Note, -9 signal is not intercept here for unknown reason.
*/
void SignalHandler::signal_SIGINT_handler(int signum)
{
	*mcerr << "Signal inrerrupt " << signum << std::endl;
	signal(signum, SIG_DFL);

	if (signum == 2)
	{
		*mcerr << "Terminated.";
		if (mOnStop)
			mOnStop(signum);
	}
	else
		exit(signum);
}

void SignalHandler::signal_SIGSEGV_handler(int signum)
{
	*mcerr << "Signal segmentation fault " << signum << std::endl;
	signal(signum, SIG_DFL);
	exit(signum);
}

void SignalHandler::signal_SIGTERM_handler(int signum)
{
	*mcerr << "Signal terminatt " << signum << std::endl;
	signal(signum, SIG_DFL);
	exit(signum);
}

SignalHandler::SignalHandler(std::ostream &cerr, onStopHandler onStop)
{
	mcerr = &cerr;
	mOnStop = onStop;
	std::signal(SIGABRT, signal_SIGABRT_handler);
	std::signal(SIGFPE, signal_SIGFPE_handler);
	std::signal(SIGILL, signal_SIGILL_handler);
	std::signal(SIGINT, signal_SIGINT_handler);
	std::signal(SIGSEGV, signal_SIGSEGV_handler);
	std::signal(SIGTERM, signal_SIGTERM_handler);
}


SignalHandler::~SignalHandler()
{
}
