/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/Common.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		/**
			Options for matchmaking rules for OpJoinRandomRoom.
		*/
		namespace MatchmakingMode
		{
			/// Fills up rooms (oldest first) to get players together as fast as possible. Default.
			/// Makes most sense with MaxPlayers > 0 and games that can only start with more players.
			static const nByte FILL_ROOM = 0;
			/// Distributes players across available rooms sequentially but takes filter into account. Without filter, rooms get players evenly distributed.
			static const nByte SERIAL_MATCHING = 1;
			/// Joins a (fully) random room. Expected properties must match but aside from this, any available room might be selected.
			static const nByte RANDOM_MATCHING = 2;
		}
	}
}