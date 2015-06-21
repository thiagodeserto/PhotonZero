/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Photon-cpp/inc/PhotonPeer.h"
#include "Photon-cpp/inc/Enums/EventCode.h"
#include "Photon-cpp/inc/Enums/EventCache.h"
#include "Photon-cpp/inc/Enums/EventKey.h"
#include "Photon-cpp/inc/Enums/OperationCode.h"
#include "Photon-cpp/inc/Enums/ParameterCode.h"
#include "Photon-cpp/inc/Enums/ReceiverGroup.h"
#include "Photon-cpp/inc/Enums/ConnectionProtocol.h"
#include "LoadBalancing-cpp/inc/Enums/ErrorCode.h"
#include "LoadBalancing-cpp/inc/Enums/PeerStates.h"
#include "LoadBalancing-cpp/inc/Enums/LobbyType.h"
#include "LoadBalancing-cpp/inc/Enums/MatchmakingMode.h"
#include "LoadBalancing-cpp/inc/AuthenticationValues.h"
#include "LoadBalancing-cpp/inc/LobbyStats.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		class Peer : public Photon::PhotonPeer
		{
		public:
			Peer(Photon::PhotonListener& listener, nByte connectionProtocol=Photon::ConnectionProtocol::UDP);
			virtual ~Peer(void);

			virtual bool opJoinLobby(const Common::JString& lobbyName=Common::JString(), nByte lobbyType=LobbyType::DEFAULT);
			virtual bool opLeaveLobby(void);
			virtual bool opCreateRoom(const Common::JString& gameID, bool isVisible=true, bool isOpen=true, nByte maxPlayers=0, const Common::Hashtable& customRoomProperties=Common::Hashtable(), const Common::Hashtable& customLocalPlayerProperties=Common::Hashtable(), const Common::JVector<Common::JString>& propsListedInLobby=Common::JVector<Common::JString>(), const Common::JString& lobbyName=Common::JString(), nByte lobbyType=LobbyType::DEFAULT, int playerTtl=0, int emptyRoomTtl=0);
			virtual bool opJoinRoom(const Common::JString& gameID, const Common::Hashtable& customLocalPlayerProperties=Common::Hashtable(), bool createIfNotExists=false, int playerNumber=0, int cacheSliceIndex=0, int playerTtl=0, int emptyRoomTtl=0);
			virtual bool opJoinRandomRoom(const Common::Hashtable& customRoomProperties=Common::Hashtable(), nByte maxPlayers=0, nByte matchmakingMode=MatchmakingMode::FILL_ROOM, const Common::JString& lobbyName=Common::JString(), nByte lobbyType=LobbyType::DEFAULT, const Common::JString& sqlLobbyFilter=Common::JString());
			virtual bool opLeaveRoom(void);
			template<typename Ftype> typename Common::Helpers::EnableIf<!Common::Helpers::ConfirmAllowed<Ftype>::dimensions, bool>::type opRaiseEvent(bool reliable, Ftype parameters, nByte eventCode, nByte channelID=0, nByte eventCaching=Lite::EventCache::DO_NOT_CACHE, const int* targetPlayers=NULL, short numTargetPlayers=0, nByte receiverGroup=Lite::ReceiverGroup::OTHERS, nByte interestGroup=0, bool forwardToWebhook=false, int cacheSliceIndex=0)
			{
				return opRaiseEvent(reliable, Common::Helpers::ValueToObject::get(parameters), eventCode, channelID, eventCaching, targetPlayers, numTargetPlayers, receiverGroup, interestGroup, forwardToWebhook, cacheSliceIndex);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<Common::Helpers::ConfirmAllowed<Ftype>::dimensions==1, bool>::type opRaiseEvent(bool reliable, Ftype pParameterArray, short arrSize, nByte eventCode, nByte channelID=0, nByte eventCaching=Lite::EventCache::DO_NOT_CACHE, const int* targetPlayers=NULL, short numTargetPlayers=0, nByte receiverGroup=Lite::ReceiverGroup::OTHERS, nByte interestGroup=0, bool forwardToWebhook=false, int cacheSliceIndex=0)
			{
				return opRaiseEvent(reliable, Common::Helpers::ValueToObject::get(pParameterArray, arrSize), eventCode, channelID, eventCaching, targetPlayers, numTargetPlayers, receiverGroup, interestGroup, forwardToWebhook, cacheSliceIndex);
			}
			template<typename Ftype> typename Common::Helpers::EnableIf<(Common::Helpers::ConfirmAllowed<Ftype>::dimensions>1), bool>::type opRaiseEvent(bool reliable, Ftype pParameterArray, const short* pArrSizes, nByte eventCode, nByte channelID=0, nByte eventCaching=Lite::EventCache::DO_NOT_CACHE, const int* targetPlayers=NULL, short numTargetPlayers=0, nByte receiverGroup=Lite::ReceiverGroup::OTHERS, nByte interestGroup=0, bool forwardToWebhook=false, int cacheSliceIndex=0)
			{
				return opRaiseEvent(reliable, Common::Helpers::ValueToObject::get(pParameterArray, pArrSizes), eventCode, channelID, eventCaching, targetPlayers, numTargetPlayers, receiverGroup, interestGroup, forwardToWebhook, cacheSliceIndex);
			}
			virtual bool opAuthenticate(const Common::JString& appID, const Common::JString& appVersion, bool encrypted, const Common::JString& userID=Common::JString(), const AuthenticationValues& authenticationValues=AuthenticationValues(), bool lobbyStats=false, const Common::JString& regionCode=Common::JString());
			virtual bool opFindFriends(const Common::JString* friendsToFind, short numFriendsToFind);
			virtual bool opLobbyStats(const Common::JVector<LoadBalancing::LobbyStats>& lobbiesToQuery=Common::JVector<LoadBalancing::LobbyStats>());
			virtual bool opChangeGroups(const Common::JVector<nByte>* groupsToRemove, const Common::JVector<nByte>* groupsToAdd);
		protected:
			virtual bool opGetRegions(bool encrypted, const Common::JString& appID);
			virtual bool opWebRpc(const Common::JString& uriPath, const Common::Object& parameters);
			virtual bool opSetPropertiesOfPlayer(int playerNr, const Common::Hashtable& properties);
			virtual bool opSetPropertiesOfRoom(const Common::Hashtable& properties, bool webForward = false);
			Photon::OperationRequestParameters opCreateRoomImplementation(const Common::JString& gameID, bool isVisible, bool isOpen, nByte maxPlayers, const Common::Hashtable& customRoomProperties, const Common::Hashtable& customLocalPlayerProperties, const Common::JVector<Common::JString>& propsListedInLobby, const Common::JString& lobbyName, nByte lobbyType, int playerTtl, int emptyRoomTtl);
			Photon::OperationRequestParameters opJoinRoomImplementation(const Common::JString& gameID, const Common::Hashtable& customLocalPlayerProperties, bool createIfNotExists, int playerNumber, int cacheSliceIndex, int playerTtl, int emptyRoomTtl);
			virtual bool opRaiseEvent(bool reliable, const Common::Object& parameters, nByte eventCode, nByte channelID, nByte eventCaching, const int* targetPlayers, short numTargetPlayers, nByte receiverGroup, nByte interestGroup, bool forwardToWebhook, int cacheSliceIndex);
		private:
			typedef PhotonPeer super;

			friend class MutablePlayer;
			friend class MutableRoom;
		};
	}
}