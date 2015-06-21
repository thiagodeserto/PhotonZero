/* Exit Games Photon LoadBalancing - C++ Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#include "Common-cpp/inc/Common.h"

namespace ExitGames
{
	namespace Photon
	{
		namespace Internal
		{
			class NetSim
			{
			public:
				NetSim(const Common::JString& name, int delay = 0, int jitter = 0, int lossPerc = 0, int dupPerc = 0);
			
				void push(nByte* pBuf, int iCount);
				bool pop(nByte*& pBuf, int& iCount);
			protected:
				Common::JString mName;
				int mDelay;
				int mJitter;
				int mLossPerc;
				int mDupPerc;

			private:
				class Packet : public Common::Base
				{		
				public:
					using Common::ToString::toString;

					Packet(nByte* buf, int size, int time = 0) : time(time), buf(buf), size(size) {}

					nByte* buf;
					int size;
					int time;

					virtual Common::JString& toString(Common::JString& retStr, bool withTypes=false) const
					{
						return retStr += L"{NetSim Packet}";
					}
				};

				void pushWithDelay(Packet*);
				int nPush;
				int nOut;
				int nLost;
				int nDuplicated;
				ExitGames::Common::JVector<Packet*> buffer;
			};
		}
	}
}