# include "channel.hpp"

Channel::~Channel(void)	{}

Channel::Channel(Server *server, Client *creator, std::string & name): _name(name), _server(server)	{
//			if (nameOk(_name))	{
	if (_name[0] != '#')
		_name = "#" + _name;
	_name = _name.substr(0, _name.find_first_of(WHITESPACES));
	
				_chops.push_back(creator);
//				_users.push_back(creator);
				_topic = "KOL KAS TIK DEL TESTAVIMO";
//			}
}

std::string const	Channel::getName(void) const{
	return (_name);
}	

std::string	Channel::getTopic(void)	{
	return (_topic);
}

std::vector<Client * > & Channel::getChops(void)	{
	return (_chops);
}

std::vector<Client * > & Channel::getUsers(void)	{
	return (_users);
}

std::string	Channel::getNamesList(void)	{
	std::string ret = " :";
	std::vector<Client *>::iterator it;
	for (it = _users.begin(); it != _users.end(); it++)	{
		std::string	nick = (*it)->get_nick_name();
		if (isChanOp(*it))
			ret += "@";
		ret += nick;
		if (it + 1 != _users.end())
			ret += " ";
	}
	std::cout << ret << "nameLISt\n";
	return (ret + "\r\n");
}

/*void	Channel::update(Client *user)	{
	msg = ":" + client->fullID() + " 353 " + client->get_nick_name();
	msg += " = " + _name + getNamesList();
	send(client->get_fd(), msg.c_str(), msg.length(), 0);
	msg = ":" + client->fullID() + " 366 " + client->get_nick_name();
	msg += " " + _name + " :End of NAMES list\r\n";
	send(client->get_fd(), msg.c_str(), msg.length(), 0);*/

/*bool	Channel::nameOk(std::string	name)	{
	if (name.length() > 50 || name.find_first_of(" ,") != std::string::npos)
		return (false)
	for (int i = 0; i < name.length(); i++)	{
		if (!std::isprint(name[i]))
			return (false)
	}
	return (true);
}*/
bool	Channel::isChanOp(Client *client) {
	if (getClientByNick(_chops, (*client).get_nick_name()))
		return (true);
	return (false);
}

bool	Channel::isOnChan(Client *client) {
	if (getClientByNick(_users, (*client).get_nick_name()))
		return (true);
	return (false);
}

void	Channel::newUser(Client	*client)	{
	if (getClientByNick(_users, client->get_nick_name()))
		return ;
	_users.push_back(client);
	std::string msg = ":" + client->fullID();
	msg += " JOIN :" + _name + "\r\n";
	std::cout << msg << std::endl;
	broadcast(msg);
	if (!_topic.empty())	{
		msg = ":" + /* client->fullID()*/ _server->getName() + " 332 " + client->get_nick_name();
		msg += " " + _name + " :" + _topic + "\r\n";
		send(client->get_fd(), msg.c_str(), msg.length(), 0);
	}
	msg = ":" + client->fullID() + " 353 " + client->get_nick_name();
	msg += " = " + _name + getNamesList();
	send(client->get_fd(), msg.c_str(), msg.length(), 0);
	msg = ":" + client->fullID() + " 366 " + client->get_nick_name();
	msg += " " + _name + " :End of NAMES list\r\n";
	send(client->get_fd(), msg.c_str(), msg.length(), 0);
}

void	Channel::broadcast(std::string msg)	{
	std::cout << "broadcast visiems kanale\n";
	for (unsigned int i = 0; i < _users.size(); i++)	{
		send(_users[i]->get_fd(), msg.c_str(), msg.length(), 0);
	}
}

void	Channel::broadcast(Client *client, std::string msg)	{
	std::cout << "broadcast\n";
	int fd = client->get_fd();
	for (unsigned int i = 0; i < _users.size(); i++)	{
		if (_users[i]->get_fd() == fd) 
			continue ;
		send(_users[i]->get_fd(), msg.c_str(), msg.length(), 0);
	}
}
void	Channel::depart(Client *client)	{
	std::vector<Client *>::iterator	it;
	std::string	name;
	name = client->get_nick_name();
	for (it = _chops.begin(); it < _chops.end(); it++)	{
		if ((*it)->get_nick_name() == name)	{
			std::cout << (*it)->get_nick_name() << std::endl;
			_chops.erase(it);
			break ;
		}
	}
	std::string msg = ":" + client->fullID();
	msg += " PART :" + _name + "\r\n";
	std::cout << msg << std::endl;
	broadcast(msg);
	for (it = _users.begin(); it < _users.end(); it++)	{
		if ((*it)->get_nick_name() == name)	{
			_users.erase(it);
			break ;
		}
	}
	if (_users.empty())	{
		std::vector<Channel *>::iterator it;
		for (it = _server->getChannels().begin(); it < _server->getChannels().end(); it++)	{
			if (*it == this)
				delete *it;
				_server->getChannels().erase(it);
			break ;
		}
	}
	else	{
		if (_chops.empty())
			_chops.push_back(client);
		std::string	msg;
		for (unsigned int i = 0; i < _users.size(); i++)	{
			_users[i]->reply(" 353 " + _users[i]->get_nick_name() + " = " + _name + getNamesList());
			_users[i]->reply(" 366 " + _users[i]->get_nick_name() + _name + ":End of NAMES list\r\n");
//	msg = ":" + client->fullID() + " 353 " + client->get_nick_name();
//	msg += " = " + _name + getNamesList();
//	send(client->get_fd(), msg.c_str(), msg.length(), 0);
//	msg = ":" + client->fullID() + " 366 " + client->get_nick_name();
//	msg += " " + _name + " :End of NAMES list\r\n";
		}
	}
}
