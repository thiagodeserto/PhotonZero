/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "LoadBalancing-cpp/inc/MutablePlayer.h"
#include "LoadBalancing-cpp/inc/MutableRoom.h"
#include "LoadBalancing-cpp/inc/Listener.h"
#include "LoadBalancing-cpp/inc/FriendInfo.h"
#include "LoadBalancing-cpp/inc/LobbyStats.h"
#include "LoadBalancing-cpp/inc/Enums/LobbyType.h"
#include "LoadBalancing-cpp/inc/Enums/MatchmakingMode.h"
#include "Photon-cpp/inc/Enums/ConnectionProtocol.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		class Client : public Peer, protected Photon::PhotonListener
		{
		public:
			Client(LoadBalancing::Listener& listener, const Common::JString& applicationID, const Common::JString& appVersion, const Common::JString& username, nByte connectionProtocol=Photon::ConnectionProtocol::UDP, AuthenticationValues authenticationValues=AuthenticationValues(), bool autoLobbyStats=false, bool useDefaultRegion=true);
			virtual ~Client(void);

			virtual bool connect(void);
			virtual bool connect(const Common::JString& masterServerAddress);
			virtual void disconnect(void);

			virtual bool opJoinLobby(const Common::JString& lobbyName=Common::JString(), nByte lobbyType=LobbyType::DEFAULT);
			virtual bool opLeaveLobby(void);
			virtual bool opCreateRoom(const Common::JString& gameID, bool isVisible=true, bool isOpen=true, nByte maxPlayers=0, const Common::Hashtable& customRoomProperties=Common::Hashtable(), const Common::JVector<Common::JString>& propsListedInLobby=Common::JVector<Common::JString>(), const Common::JString& lobbyName=Common::JString(), nByte lobbyType=LobbyType::DEFAULT, int playerTtl=0, int emptyRoomTtl=0);
			virtual bool opJoinRoom(const Common::JString& gameID, bool createIfNotExists=false, int playerNumber=0, int cacheSliceIndex=0, int playerTtl=0, int emptyRoomTtl=0);
			virtual bool opJoinRandomRoom(const Common::Hashtable& customRoomProperties=Common::Hashtable(), nByte maxPlayers=0, nByte matchmakingMode=MatchmakingMode::FILL_ROOM, const Common::JString& lobbyName=Common::JString(), nByte lobbyType=LobbyType::DEFAULT, const Common::JString& sqlLobbyFilter=Common::JString());
			virtual bool opLeaveRoom(bool willComeBack=true);
			virtual bool opFindFriends(const Common::JString* friendsToFind, short numFriendsToFind);
			virtual bool opLobbyStats(const Common::JVector<LoadBalancing::LobbyStats>& lobbiesToQuery=Common::JVector<LoadBalancing::LobbyStats>());
			virtual bool opChangeGroups(const Common::JVector<nByte>* groupsToRemove, const Common::JVector<nByte>* groupsToAdd);
			virtual bool opCustomAuthenticationSendNextStepData(const AuthenticationValues& authenticationValues);
			virtual bool opWebRpc(const Common::JString& uriPath, const Common::Object& parameters);

			virtual bool selectRegion(const Common::JString& selectedRegion);

			PeerStates::PeerStates getState(void) const;
			const Common::JString& getMasterserverAddress(void) const;
			int getCountPlayersIngame(void) const;
			int getCountGamesRunning(void) const;
			int getCountPlayersOnline(void) const;
			MutableRoom& getCurrentlyJoinedRoom(void);
			const Common::JVector<Room*>& getRoomList(void) const;
			const Common::JVector<Common::JString>& getRoomNameList(void) const;
			bool getIsInRoom(void) const;
			bool getIsInGameRoom(void) const;
			bool getIsInLobby(void) const;
			bool getAutoJoinLobby(void) const;
			void setAutoJoinLobby(bool onConnect);
			MutablePlayer& getLocalPlayer(void);
			const Common::JVector<FriendInfo>& getFriendList(void);
			int getFriendListAge(void);
			int getDisconnectedCause(void);
		protected:
			virtual bool opAuthenticate(const Common::JString& appID, const Common::JString& appVersion, bool encrypted, const Common::JString& userID=Common::JString());
			virtual bool opGetRegions(bool encrypted, const Common::JString& appID);
			virtual bool opSetPropertiesOfPlayer(int playerNr, const Common::Hashtable& properties);
			virtual bool opSetPropertiesOfRoom(const Common::Hashtable& properties, bool webForward = false);

			virtual Room* createRoom(const Common::JString& name, const Common::Hashtable& properties);
			virtual void destroyRoom(const Room* pRoom) const;
			virtual MutablePlayerFactory* getMutablePlayerFactory(void) const;
			virtual MutableRoomFactory* getMutableRoomFactory(void) const;

			// From Photon::PhotonListener
			virtual void onOperationResponse(const Photon::OperationResponse& operationResponse);
			virtual void onStatusChanged(int statusCode);
			virtual void onEvent(const Photon::EventData& eventData);
			virtual void debugReturn(Common::DebugLevel::DebugLevel debugLevel, const Common::JString& string);
		private:
			void readoutProperties(Common::Hashtable& roomProperties, Common::Hashtable& playerProperties, bool multiplePlayers, int targetPlayerNr);
			void handleConnectionFlowError(PeerStates::PeerStates oldState, int errorCode, const Common::JString& errorString);
			void onConnectToMasterFinished(bool comingFromGameserver);
			MutablePlayer* createMutablePlayer(int number, const Common::Hashtable& properties);
			void destroyMutablePlayer(const MutablePlayer* pPlayer) const;
			MutableRoom* createMutableRoom(const Common::JString& name, const Common::Hashtable& properties, const Common::JVector<Common::JString>& propsListedInLobby=Common::JVector<Common::JString>());
			void destroyMutableRoom(const MutableRoom* pRoom) const;

			bool getIsOnGameServer(void) const;

			typedef Peer super;

			Listener& mListener;
			Common::JString mGameserver;
			Common::JString mAppVersion;
			Common::JString mRoomName;
			Common::JString mAppID;
			int mPeerCount;
			int mRoomCount;
			int mMasterPeerCount;
			nByte mLastJoinType;
			nByte mLastLobbyJoinType;
			bool mLastJoinCreateIfNotExists;
			int mLastJoinPlayerNumber;
			int mLastCacheSliceIndex;
			MutableRoom* mpCurrentlyJoinedRoom;
			Common::JVector<Room*> mRoomList;
			Common::JVector<Common::JString> mRoomNameList;
			int mSenttime;
			int mCachedErrorCodeFromGameServer;
			Common::JString mCachedErrorStringFromGameServer;
			Common::JString mNameserver;
			bool mAutoJoinLobby;
			MutablePlayer* mpLocalPlayer;
			Common::JVector<FriendInfo> mFriendList;
			Common::JVector<Common::JString> mLastFindFriendsRequest;
			int mFriendListTimestamp;
			bool mIsFetchingFriendList;
			Common::JVector<LobbyStats> mLobbyStatsList;
			PeerStates::PeerStates mState;
			AuthenticationValues mAuthenticationValues;
			bool mAutoLobbyStats;
			MutablePlayerFactory* mpMutablePlayerFactory;
			MutableRoomFactory* mpMutableRoomFactory;
			int mDisconnectedCause;
			Common::JString mSelectedRegion;
			const bool M_USE_DEFAULT_REGION;
			Common::JString mMasterserver;
		};
	}
}