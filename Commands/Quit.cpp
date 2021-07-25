#include "Quit.hpp"
#include "Server.h"
#include <unistd.h>
Quit::Quit()
{
}

Quit::~Quit()
{
}

Quit::Quit(const std::string & full_command, const std::vector<std::string> & arguments): RegisteredCommand(full_command, "QUIT", arguments)
{
	
}

Quit *Quit::create(const std::string & full_command, const std::vector<std::string> & arguments)
{
	return new Quit(full_command, arguments);
}

bool Quit::execute(Server & server, Client & client)
{
	if (RegisteredCommand::execute(server, client))
		return(true);
	std::set<SharedPtr<Client> > releted_users;
			for (std::map<std::string, Channel *>::iterator it_ch = client._channels.begin(); it_ch != client._channels.end(); it_ch++)
				for (std::map<std::string, std::pair<SharedPtr<Client>, std::set<char> > >::iterator it = server._channels[(*it_ch).first].users.begin(); it != server._channels[(*it_ch).first].users.end(); it++)
						releted_users.insert(server._users[(*it).first]);
			for (std::set<SharedPtr<Client> >::iterator it = releted_users.begin(); it != releted_users.end(); it++)
				(*it)->_received_msgs.push(notification(client, this));
	server._to_delete.push_back(server._users.find(client.get_nickname()));
	for (std::map<std::string, Channel>::iterator it = server._channels.begin() ; it != server._channels.end(); it++)
		(*it).second.users.erase(client.get_nickname());
	//close(client.getFd()); // ТаК??
	std::cout << "Quit works!" << std::endl;
	return true;
}

// std::string Quit::getCommandName() 
// {
// 	return ("QUIT");
// }