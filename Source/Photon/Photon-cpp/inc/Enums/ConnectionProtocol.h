/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

namespace ExitGames
{
	namespace Photon
	{
		/**
			These are the options that can be used as underlying transport protocol.
		*/
		namespace ConnectionProtocol
		{
			/// Use UDP to connect to Photon, which allows you to send operations reliable or unreliable on demand.
			static const nByte UDP = 0;
			/// Use TCP to connect to Photon.
			static const nByte TCP = 1;
		}
	}
}