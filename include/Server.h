#pragma once

#include "Parser.h"
#include "Cgi.h"
#include "Client.h"
#include "SharedPtr.h"
#include <stdexcept>
#include <cstring>

typedef int fd_type;

class Server {
 public:
	explicit Server(const std::vector<ServConfig> &servers);

	Server(int port, const std::string& host_ip);

	void initSocket();
	void checkClients();
	void checkSockets();
	int Select();
	int getMaxSockFd() const;
	void newClient(int indexServer);

	class Error : public std::runtime_error {
	 private:
		Error();
	 public:
		explicit Error(const std::string &msg) :
		std::runtime_error("Error: " + msg + ": " + strerror(errno)) {};
	};
 private:
	Server();
	Server(const Server &);
	void operator=(const Server &);

	std::vector<ServConfig> _servers;
	size_t _amountServers;
	std::vector<SharedPtr<Client> > _clients;
	fd_set _readFds;
	fd_set _writeFds;

	fd_type _socket_fd;
	int _port;
	std::string _host_ip;
	sockaddr_in _sockaddr;
	void reloadFdSets();
	const std::vector<SharedPtr<Client> > &getClients() const;
};