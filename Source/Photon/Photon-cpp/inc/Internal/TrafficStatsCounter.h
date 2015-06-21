/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/Common.h"
#include "Photon-cpp/inc/TrafficStats.h"

/** @file TrafficStatsCounter.h */

namespace ExitGames
{
	namespace Photon
	{
		namespace Internal
		{
			class TrafficStatsGameLevelCounter: public TrafficStatsGameLevel
			{
			public:
				void countOperation(int operationBytes);
				void countResult(int resultBytes);
				void countEvent(int eventBytes);
				void timeForResponseCallback(nByte code, int time);
				void timeForEventCallback(nByte code, int time);
		//#if SDK_V4
		//        void timeForMessageCallback(int time)
		//        void timeForRawMessageCallback(int time)
		//#endif//SDK_V4
				void dispatchIncomingCommandsCalled(void);
				void sendOutgoingCommandsCalled(void);
			};
			
			class TrafficStatsCounter : public TrafficStats
			{
			public:
				TrafficStatsCounter(int packageHeaderSize);

				void countControlCommand(int size);
				void countReliableOpCommand(int size);
				void countUnreliableOpCommand(int size);
				void countFragmentOpCommand(int size);

				void totalPacketCountInc(int inc = 1);
				void totalCommandsInPacketsInc(int inc = 1);

				void setTimestampOfLastAck(int t);
				void setTimestampOfLastReliableCommand(int t);
			};
		}
	}
}