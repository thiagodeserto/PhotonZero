/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/Common.h"

/** @file TrafficStats.h */

namespace ExitGames
{
	namespace Photon
	{
		/**
			Only in use as long as PhotonPeer.TrafficStatsEnabled = true;
		*/
		class TrafficStatsGameLevel
		{
		public:
			TrafficStatsGameLevel();

			int getOperationByteCount(void) const;
			int getOperationCount(void) const;
			int getResultByteCount(void) const;
			int getResultCount(void) const;
			int getEventByteCount(void) const;
			int getEventCount(void) const;
        	int getLongestOpResponseCallback(void) const;
			nByte getLongestOpResponseCallbackOpCode(void) const;
        	int getLongestEventCallback(void) const;
	//#if SDK_V4
	//        int LongestMessageCallback(void) const;
	//        int LongestRawMessageCallback(void) const;
	//#endif//SDK_V4
			nByte getLongestEventCallbackCode(void) const;
			int getLongestDeltaBetweenDispatching(void) const;
			int getLongestDeltaBetweenSending(void) const;
			int getDispatchIncomingCommandsCalls(void) const;
			int getSendOutgoingCommandsCalls(void) const;
			int getTotalByteCount(void) const;
			int getTotalMessageCount(void) const;
			int getTotalIncomingByteCount(void) const;
			int getTotalIncomingMessageCount(void) const;
			int getTotalOutgoingByteCount(void) const;
			int getTotalOutgoingMessageCount(void) const;
			void resetMaximumCounters(void); // use PhotonPeer::trafficStatsResetMaximumCounters() to call this on peer's stats

			virtual Common::JString toString(void) const;
			virtual Common::JString toStringVitalStats(void) const;

		protected:
			int timeOfLastDispatchCall;
			int timeOfLastSendCall;

			int operationByteCount;
			int operationCount;
			int resultByteCount;
			int resultCount;
			int eventByteCount;
			int eventCount;
			int longestOpResponseCallback;
			nByte longestOpResponseCallbackOpCode;
			int longestEventCallback;
	//#if SDK_V4
	//        int longestMessageCallback;
	//        int longestRawMessageCallback;
	//#endif//SDK_V4
			nByte longestEventCallbackCode;
			int longestDeltaBetweenDispatching;
			int longestDeltaBetweenSending;
			int dispatchIncomingCommandsCalls;
			int sendOutgoingCommandsCalls;
		};

		class TrafficStats
		{
		public:
			TrafficStats(int packageHeaderSize);

			int getPackageHeaderSize(void) const;
			int getReliableCommandCount(void) const;
			int getUnreliableCommandCount(void) const;
			int getFragmentCommandCount(void) const;
			int getControlCommandCount(void) const;
			int getTotalPacketCount(void) const;
			int getTotalCommandsInPackets(void) const;
			int getReliableCommandBytes(void) const;
			int getUnreliableCommandBytes(void) const;
			int getFragmentCommandBytes(void) const;
			int getControlCommandBytes(void) const;
			int getTotalCommandCount(void) const;
			int getTotalCommandBytes(void) const;
			int getTotalPacketBytes(void) const;
			int getTimestampOfLastAck(void) const;
			int getTimestampOfLastReliableCommand(void) const;

			virtual Common::JString toString(void) const;
		protected:
			int packageHeaderSize;
			int reliableCommandCount;
			int unreliableCommandCount;
			int fragmentCommandCount;
			int controlCommandCount;
			int totalPacketCount;
			int totalCommandsInPackets;
			int reliableCommandBytes;
			int unreliableCommandBytes;
			int fragmentCommandBytes;
			int controlCommandBytes;
			int timestampOfLastAck;
			int timestampOfLastReliableCommand;

		};	
	}

}