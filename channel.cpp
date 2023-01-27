# include "channel.hpp"

Channel::~Channel(void)	{}

Channel::Channel(Server *server, Client *creator, std::string & name): _name(name[0] == '#'? name : "#" + name), _server(server)	{
//			if (nameOk(_name))	{
				_chops.push_back(creator);
				_users.push_back(creator);
				_topic = "KOL KAS TIK DEL TESTAVIMO";
//			}
}

std::string const	Channel::getName(void) const{
	return (_name);
}	

//		broadcast(std::string const message);

std::vector<Client * > & Channel::getChops(void)	{
	return (_chops);
}

std::vector<Client * > & Channel::getUsers(void)	{
	return (_users);
}

void	Channel::addUser(Client	*user)	{
	if (!getClientByNick(_users, (*user).get_nick_name()))	{
		//if user not already there 
		_users.push_back(user);
//		user->reply(
	}
}
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

void	Channel::newUser(Client	*client)	{
	if (getClientByNick(_users, client->get_nick_name()))
		return ;
	_users.push_back(client);
	std::string msg = client->fullID();
	msg += " JOIN " + _name + "\r\n";
	std::cout << msg << std::endl;
	broadcast(msg);
	if (!_topic.empty())	{
		msg = ":" + _server->getName() + " 332 " + client->get_nick_name();
		msg += " " + _name + " :" + _topic + "\r\n";
		send(client->get_fd(), msg.c_str(), msg.length(), 0);
	}
}

void	Channel::broadcast(std::string msg)	{
	std::cout << "broadcast\n";
	for (int i = 0; i < _users.size(); i++)	{
		send(_users[i]->get_fd(), msg.c_str(), msg.length(), 0);
	}
}

/*void	Channel::broadcast(Client *sender, std::vector<std::string> args)	{
	std::cout << "broadcast\n";
	std::string	msg;
//	if (isChanOp(sender))	{
//		msg = ":@" + sender->get_nick_name();
//		std::string t;
//		t = sender->get_user_name();
//		if (!t.empty())
//			msg += "!" + t;
//		t = sender->get_ip();
//		if (!t.empty())
//			msg += t;
//		msg += " " + args[0] + " " + args[1] + " " + args[2] + "\r\n";
//		std::cout << msg << std::endl;
//	}
//	else	{
		msg = " " + args[0] + " " + args[1];
		msg = sender->sendMsg(msg + " :" + args[2]);
//	}
	for (int i = 0; i < _users.size(); i++)	{
		send(_users[i]->get_fd(), msg.c_str(), msg.length(), 0);
	}
}*/
