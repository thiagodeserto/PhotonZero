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
			Options for optional "Custom Authentication" services used with Photon. Used by OpAuthenticate after connecting to Photon.
		*/
		namespace CustomAuthenticationType
		{
			/// Use a custom authentification service. Currently the only implemented option.
			static const nByte CUSTOM = 0;
			/// Authenticates users by their Steam Account. Set auth values accordingly!
			static const nByte STEAM = 1;
			/// Authenticates users by their Facebook Account. Set auth values accordingly!
			static const nByte FACEBOOK = 2;
			/// Disables custom authentification. Same as not providing any AuthenticationValues for connect (more precisely for: OpAuthenticate).
			static const nByte NONE = UCHAR_MAX;
		}	
	}
}