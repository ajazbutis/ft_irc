### ***mini #Irc server***
>_reference clients - Textual & KVIrc_

#### _Supported commands:_
```
NICK <newnick>
PRIVMSG <nick/channel> <msg>
NOTICE <nick/channel> <msg>
LIST
NAMES <channel>
JOIN <channel>/,<channel>'s
PART <channel>
TOPIC <channel> /<newTopic>
MODE <channel> <+/-o> <nick>
KICK <channel> <nick> 
OPER <adminName> <adminPass> {
  KILL <nick>
  WALL
  SQUIT
}
QUIT

Responds to:
 WHO
 ISON
 PING
 ```
 #### ***loveBot***
 _this lovely tiny bot, when run, joins a given server, creates/joins #Jokes, tries to change the topic and welcomes newly_
 _to the channel joined users and, depending on the interaction, entertains the user by telling a joke or flirting._
