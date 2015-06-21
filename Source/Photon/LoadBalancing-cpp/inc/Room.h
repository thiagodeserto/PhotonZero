/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "LoadBalancing-cpp/inc/Internal/RoomFactory.h"
#include "LoadBalancing-cpp/inc/Internal/RoomPropertiesCacher.h"

namespace ExitGames
{
	namespace LoadBalancing
	{
		class Room : public Common::Base
		{
		public:
			using Common::ToString::toString;

			virtual ~Room(void);

			Room(const Room& toCopy);
			virtual Room& operator=(const Room& toCopy);

			const Common::JString& getName(void) const;
			virtual nByte getPlayerCount(void) const;
			nByte getMaxPlayers(void) const;
			bool getIsOpen(void) const;
			const Common::Hashtable& getCustomProperties(void) const;
			int getPlayerTtl();
			int getRoomTtl();

			bool operator==(const Room& room) const;
			virtual Common::JString& toString(Common::JString& retStr, bool withTypes=false) const;
			virtual Common::JString toString(bool withTypes, bool withCustomProperties) const;
		protected:
			Room(const Common::JString& name, const Common::Hashtable& properties);

			virtual bool getIsMutable(void) const;

			virtual Room& assign(const Room& toCopy);
			virtual void cacheProperties(const Common::Hashtable& properties);
			virtual Common::JString payloadToString(bool withTypes=false, bool withCustomProperties=false) const;

			Common::JString mName;
			nByte mPlayerCount;
			nByte mMaxPlayers;
			bool mIsOpen;
			Common::Hashtable mCustomProperties;

			int mPlayerTtl;
			int mRoomTtl;
		private:
			Room(void);

			friend class Internal::RoomFactory;
			friend class Internal::RoomPropertiesCacher;
		};
	}
}