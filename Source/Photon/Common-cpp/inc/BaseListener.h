/* Exit Games Common - C++ Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Common-cpp/inc/Helpers/TypeName.h"
#include "Common-cpp/inc/Enums/DebugLevel.h"

namespace ExitGames
{
	namespace Common
	{
		class BaseListener
		{
		public:
			virtual ~BaseListener() {};
			virtual void debugReturn(DebugLevel::DebugLevel debugLevel, const JString& string) = 0;
		};

		/** @file */

		/** @class BaseListener
			This class defines the listener interface for the debug
			callback mechanism.
			@sa
			Base, Base::setListener()                                     */

			/** @fn BaseListener::debugReturn(DebugLevel::DebugLevel debugLevel, const JString& string)
				This is the callback function for debug-messages.
				@param debugLevel one of the values in DebugLevel
				@param string the formatted debug string
				@sa
				BaseListener                                          */
	}
}