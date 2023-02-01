#include "server.hpp"
#include "signal.h"

static void nichtGut(std::string msg)	{
	std::cout << msg << std::endl;
}


/*static void	check(void)	{
	system ("leaks ircserv");
}*/

int main(int argc, char **argv)
{
//	atexit(check);
	if (argc != 3)	{
		nichtGut("Usage: <ircserv> <port> <password>");
		return (0);
	}
	for (int i = 0; argv[1][i] != '\0'; i++)	{
		if (!isdigit(argv[1][i]))	{
			nichtGut("Sorry, the port doesn't feel right");
			return (0);
		}
	}
	int port = atoi(argv[1]);
	if (port < 1000 || port > 65535)	{
		nichtGut("It feels like the port is a bit of range");
		return (0);
	}
	for (int i = 0; argv[2][i] != '\0'; i++)	{
		if (!isprint(argv[2][i]))	{
			nichtGut("Unacceptable password format");
			return (0);
		}
	}
	try {
		Server srv(port, argv[2]);
		signal(SIGINT, Server::turnOff);
		srv.run_server();
		return (0);
	}
	catch (std::exception &e)	{
		std::cerr << e.what() << std::endl;
		return (1);
	}
}
