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
		class Player;

		namespace Internal
		{
			class PlayerPropertiesCacher
			{
				static void cache(Player& player, const Common::Hashtable& properties);
				static void setIsInactive(Player& player, bool v);

				friend class PlayerPropertiesUpdateInformant;
			};
		}
	}
}