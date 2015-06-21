/* Exit Games Photon - C++ Client Lib
 * Copyright (C) 2004-2013 by Exit Games GmbH. All rights reserved.
 * http://www.exitgames.com
 * mailto:developer@exitgames.com
 */

#pragma once

#include "Photon-cpp/inc/Internal/EnetConnect.h"
#include "Photon-cpp/inc/Internal/NetSim.h"

namespace ExitGames
{
	namespace Photon
	{
		namespace Internal
		{
			class EnetConnectNetSim : public EnetConnect
			{			
			public:
				EnetConnectNetSim(PhotonConnectListener& listener);
				~EnetConnectNetSim(void);
				void service(void);
			protected:
				// pops from recvNetSim 
				int recvBuffer(nByte** ppBuff, int* pBytesRead);
				// pushes to sendNetSim
				int sendBuffer(char* pBuff, int iSize);				
				NetSim* sendNetSim;
				NetSim* recvNetSim;
			private:
				typedef EnetConnect super;

				// pops from sendNetSim and sends to socket
				void serviceSend(void);
				// receives from socket and pushes to recvNetSim
				void serviceRecv(void);
			};
		}
	}
}