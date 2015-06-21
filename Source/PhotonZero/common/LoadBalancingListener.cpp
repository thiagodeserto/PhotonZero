
#include "PhotonZero.h"
#include "LoadBalancingListener.h"
#include "DemoConstants.h"
using namespace ExitGames::Common;
using namespace ExitGames::LoadBalancing;

const char* PeerStatesStr[] = {
"Uninitialized",
"PeerCreated",
"ConnectingToNameserver",
"ConnectedToNameserver",
"DisconnectingFromNameserver",
"Connecting",
"Connected",
"WaitingForCustomAuthenticationNextStepCall",
"Authenticated",
"JoinedLobby",
"DisconnectingFromMasterserver",
"ConnectingToGameserver",
"ConnectedToGameserver",
"AuthenticatedOnGameServer",
"Joining",
"Joined",
"Leaving",
"Left",
"DisconnectingFromGameserver",
"ConnectingToMasterserver",
"ConnectedComingFromGameserver",
"AuthenticatedComingFromGameserver",
"Disconnecting",
"Disconnected"
};

// TODO: update PeerStatesStr when PeerStates changes
// Checker below checks count match only
class PeerStatesStrChecker{
public:
	PeerStatesStrChecker()
	{
		assert(sizeof(PeerStatesStr)/sizeof(const char*) == PeerStates::Disconnected + 1);
	}
} checker;

LocalPlayer::LocalPlayer() : x(0), y(0), z(0), a(0), b(0), c(0), lastUpdateTime(0) {}

LoadBalancingListener::LoadBalancingListener(BaseView* view): 
	lbc(NULL), 
	view(view), 
	localPlayerNr(0),
	map(DEFAULT_MAP), 
	automove(false)
{}

void LoadBalancingListener::debugReturn(const JString& string)
{
    view->info(string.UTF8Representation().cstr());
}

void LoadBalancingListener::debugReturn(DebugLevel::DebugLevel debugLevel, const JString& string)
{
	const char* s = string.UTF8Representation().cstr();
	switch (debugLevel)
	{
	case DebugLevel::ERRORS:
		view->error(s); break;
	case DebugLevel::WARNINGS:
		view->warn(s); break;
	default:
		view->info(s); break;
	}
    
}

void LoadBalancingListener::connectionErrorReturn(int errorCode)
{
    view->warn("connection failed with error %d", errorCode);
	updateState();
	// reconnect on error
//	connect();
}

void LoadBalancingListener::clientErrorReturn(int errorCode)
{
    view->warn("received error %d from client", errorCode);
	updateState();
}

void LoadBalancingListener::warningReturn(int warningCode)
{
    view->warn("received warning %d from client", warningCode);
}

void LoadBalancingListener::serverErrorReturn(int errorCode)
{
    view->warn("received error %d from server", errorCode);
	updateState();
}

void LoadBalancingListener::joinRoomEventAction(int playerNr, const JVector<int>& playernrs, const Player& player)
{
	view->info("player %d %s has joined the game", playerNr, player.getName().UTF8Representation().cstr());
	view->addPlayer(playerNr, player.getName().UTF8Representation().cstr(), player.getNumber() == lbc->getLocalPlayer().getNumber());
}

void LoadBalancingListener::leaveRoomEventAction(int playerNr, bool isInactive)
{    
	if(isInactive)
		view->info( "player %d has suspended the game", playerNr);		
	else
	{
		view->info( "player %d has abandoned the game", playerNr);
		view->removePlayer(playerNr);
	}
}

void LoadBalancingListener::disconnectEventAction(int playerNr)
{
	view->info( "player %d has disconnected", playerNr);
}

void LoadBalancingListener::customEventAction(int playerNr, nByte eventCode, const Object& eventContentObj)
{
    //local playerObj = scene.getTaggedObject ( application.getCurrentUserScene ( ), "" .. playerNr )    
//	view->info("event %d: %s", eventCode, eventContent.toString(true).UTF8Representation().cstr());
	ExitGames::Common::Hashtable eventContent = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContentObj).getDataCopy();
    if(eventCode == 1)
	{
		Object const* obj = eventContent.getValue("1");
		if(obj == NULL) obj = eventContent.getValue((nByte)1);
		if(obj == NULL) obj = eventContent.getValue(1);
		if(obj == NULL) obj = eventContent.getValue(1.0);
		if(obj) 
		{
			int color = (int)(obj->getType() == 'd' ?  ((ValueObject<double>*)obj)->getDataCopy() : ((ValueObject<int>*)obj)->getDataCopy());
		}
		else 
		{
			view->warn( "bad color event");
		}
	}
    else if(eventCode == 6)
	{
		Object const* obj = eventContent.getValue("1");
		if(obj == NULL) obj = eventContent.getValue((nByte)1);
		if(obj == NULL) obj = eventContent.getValue(1);
		if(obj == NULL) obj = eventContent.getValue(1.0);
        if(obj && obj->getDimensions() == 1 && obj->getSizes()[0] == 6) 
		{
			int x = 0; int y = 0; int z = 0;
			int a = 0; int b = 0; int c = 0;
			if(obj->getType() == 'd') 
			{
				double* data = ((ValueObject<double*>*)obj)->getDataCopy();
				x = (int)data[0];
				y = (int)data[1];
				z = (int)data[2];
				a = (int)data[3];
				b = (int)data[4];
				c = (int)data[5];
			}
			if(obj->getType() == 'i') 
			{
				int* data = ((ValueObject<int*>*)obj)->getDataCopy();
				x = (int)data[0];
				y = (int)data[1];
				z = (int)data[2];
				a = (int)data[3];
				b = (int)data[4];
				c = (int)data[5];
			}
			else if(obj->getType() == 'b') 
			{
				nByte* data = ((ValueObject<nByte*>*)obj)->getDataCopy();
				x = (int)data[0];
				y = (int)data[1];
				z = (int)data[2];
				a = (int)data[3];
				b = (int)data[4];
				c = (int)data[5];
			}
			else if(obj->getType() == 'z') 
			{
				Object* data = ((ValueObject<Object*>*)obj)->getDataCopy();
				if(data[0].getType() == 'i') 
				{
					x = ((ValueObject<int>*)(data + 0))->getDataCopy();
					y = ((ValueObject<int>*)(data + 1))->getDataCopy();
					z = ((ValueObject<int>*)(data + 2))->getDataCopy();
					a = ((ValueObject<int>*)(data + 3))->getDataCopy();
					b = ((ValueObject<int>*)(data + 4))->getDataCopy();
					c = ((ValueObject<int>*)(data + 5))->getDataCopy();
				}
				else 
				{
					x = (int)((ValueObject<double>*)(data + 0))->getDataCopy();
					y = (int)((ValueObject<double>*)(data + 1))->getDataCopy();
					z = (int)((ValueObject<double>*)(data + 2))->getDataCopy();
					a = (int)((ValueObject<double>*)(data + 3))->getDataCopy();
					b = (int)((ValueObject<double>*)(data + 4))->getDataCopy();
					c = (int)((ValueObject<double>*)(data + 5))->getDataCopy();
				}
			}
			view->changePlayerPos(playerNr, x, y, z, a, b, c);
		}
		else 
		{
            view->warn( "Bad position event");
		}
	}
}

void LoadBalancingListener::connectReturn(int errorCode, const JString& errorString)
{
	updateState();
    if(errorCode == ErrorCode::OK)
	{
		view->info("connected");
		lbc->opJoinRandomRoom();
	}
	else
		view->error("Warn: connect failed %d %s", errorCode, errorString.UTF8Representation().cstr());
}

void LoadBalancingListener::disconnectReturn(void)
{
	updateState();
    view->info("disconnected");
	view->initPlayers();
}

void LoadBalancingListener::createRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if(errorCode == ErrorCode::OK)
	{
        view->info("room has been created");
        afterRoomJoined(localPlayerNr);
	}
	else
		view->error("Warn: opCreateRoom() failed: %s", errorString.UTF8Representation().cstr() );
}

void LoadBalancingListener::joinRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if(errorCode == ErrorCode::OK)
	{
		view->info("game room has been successfully joined");
        afterRoomJoined(localPlayerNr);
	}
	else
		view->error("opJoinRoom() failed: %s", errorString.UTF8Representation().cstr());
}

void LoadBalancingListener::joinRandomRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if(errorCode == ErrorCode::NO_MATCH_FOUND)
	{
        createRoom();
	}
    else if(errorCode == ErrorCode::OK)
	{
		view->info("game room has been successfully joined");
        afterRoomJoined(localPlayerNr);
	}
	else
		view->error("opJoinRandomRoom() failed: %s", errorString.UTF8Representation().cstr());
}

void LoadBalancingListener::leaveRoomReturn(int errorCode, const JString& errorString)
{
	updateState();
    if(errorCode == ErrorCode::OK)
        view->info("game room has been successfully left");
	else
		view->error("opLeaveRoom() failed: %s", errorString.UTF8Representation().cstr());
	view->initPlayers();
}

void LoadBalancingListener::gotQueuedReturn(void)
{
	updateState();
}

void LoadBalancingListener::joinLobbyReturn(void)
{
    view->info("joined lobby");
	updateState();
	lbc->opJoinRandomRoom();
}

void LoadBalancingListener::leaveLobbyReturn(void)
{
    view->info("left lobby");
	updateState();
}

void LoadBalancingListener::onLobbyStatsUpdate(const JVector<LobbyStats>& res)
{
	view->info("===================== lobby stats update");
	for(unsigned int i = 0;i < res.getSize();++i) 
	{
		view->info(res[i].toString().UTF8Representation().cstr());
	}

	// lobby stats request test
	JVector<LobbyStats> ls;
	ls.addElement(LobbyStats());
	ls.addElement(LobbyStats(L"AAA"));
	ls.addElement(LobbyStats(L"BBB"));
	ls.addElement(LobbyStats(L"CCC", LobbyType::DEFAULT));
	ls.addElement(LobbyStats(L"AAA", LobbyType::SQL_LOBBY));
	lbc->opLobbyStats(ls);
//	lbc->opLobbyStats();
}

void LoadBalancingListener::onLobbyStatsResponse(const ExitGames::Common::JVector<LobbyStats>& res)
{
	view->info("===================== lobby stats response");
	for(unsigned int i = 0;i < res.getSize();++i) 
	{
		view->info(res[i].toString().UTF8Representation().cstr());
	}
}

void LoadBalancingListener::onRoomListUpdate()
{	
	const JVector<Room*>& rooms = lbc->getRoomList();
	const char** names = MemoryManagement::allocateArray<const char*>(rooms.getSize());
	for(unsigned int i = 0; i < rooms.getSize();++i) 
	{
		const Room* r = rooms.getElementAt(i);
		UTF8String u = r->getName();
		const char* name = u.cstr();
		char* tmp = MemoryManagement::allocateArray<char>(strlen(name) + 1);
		strcpy(tmp, name);
		names[i] = tmp;
	}
	view->updateRoomList(names, rooms.getSize());
	for(unsigned int i = 0; i < rooms.getSize();++i) 
	{
		MemoryManagement::deallocateArray(names[i]);
	}
	MemoryManagement::deallocateArray(names);
}

void LoadBalancingListener::onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes) 
{

}

void LoadBalancingListener::updateState() 
{
	int state = lbc->getState();
	view->updateState(state, PeerStatesStr[state], 
		state == PeerStates::Joined ? lbc->getCurrentlyJoinedRoom().getName().UTF8Representation().cstr() : NULL);
}

void LoadBalancingListener::afterRoomJoined(int localPlayerNr)
{
	view->info( "afterRoomJoined: localPlayerNr=", localPlayerNr );
	this->localPlayerNr = localPlayerNr;
    MutableRoom& myRoom = lbc->getCurrentlyJoinedRoom();
	Hashtable props = myRoom.getCustomProperties();
	if(props.contains("m"))
		map = ((ValueObject<JString>*)props.getValue("m"))->getDataCopy();
    
    view->initPlayers();
             
	const JVector<Player*>& players = myRoom.getPlayers();
	for(unsigned int i = 0;i < players.getSize();++i)
	{
		const Player* p = players[i];
		view->addPlayer(p->getNumber(), p->getName().UTF8Representation().cstr(), p->getNumber() == lbc->getLocalPlayer().getNumber());
	}
}

void LoadBalancingListener::createRoom() 
{
	char name[16];
	sprintf(name, "UE-%d",rand() % 100 );
	Hashtable props;
	props.put("m", map);
	if(lbc->opCreateRoom(name, true, true, 0, props))
		view->info( "Creating room %s", name );
	else
		view->error("Can't create room in current state");
}

void LoadBalancingListener::leave()
{
	if (!lbc->opLeaveRoom()) 
	{
		view->error("Not in room currently");
	}
}

void LoadBalancingListener::service()
{
	
	unsigned long t = GETTIMEMS();
	if((t - localPlayer.lastUpdateTime) > PLAYER_UPDATE_INTERVAL_MS) 
	{
		localPlayer.lastUpdateTime = t;
		if(lbc->getState() == PeerStates::Joined && automove) 
		{
			//moveLocalPlayer();
		}
	}
}

bool LoadBalancingListener::setLocalPlayerPos(int x, int y, int z, int a, int b, int c)
{
	localPlayer.x = x;
	localPlayer.y = y;
	localPlayer.z = z;
	localPlayer.a = a;
	localPlayer.b = b;
	localPlayer.c = c;
	Hashtable data;
	int coords[] = { localPlayer.x, localPlayer.y, localPlayer.z, localPlayer.a, localPlayer.b, localPlayer.c };
	data.put((nByte)1, coords, 6);

	lbc->opRaiseEvent(false, data, 6);

	view->changePlayerPos(localPlayerNr, localPlayer.x, localPlayer.y, localPlayer.z, localPlayer.a, localPlayer.b, localPlayer.c);
	return true;
	
}