#include "box_usb.h"
#include "types.h"
#include "boxpackets.h"


bool Box_DecodeMessage()
{
	bool response = false;


	if (decodeRequestBoxStatusPacket(rxBuf))
	{
		encodeBoxStatusPacketStructure(txBuf, &status);
		response = true;
	}


	return response;
}
