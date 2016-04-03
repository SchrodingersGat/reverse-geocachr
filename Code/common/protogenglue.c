#include "ReverseGeocacheProtocol.h"

/* Format of a HIDbuffer data struct 
0 = Msg Type
1 = Msg Len
2 = Msg Data
*/

//! \return the packet data pointer from the packet
uint8_t* getReverseGeocachePacketData(void* pkt)
{
    return (uint8_t*) (pkt + 2);
}

//! \return the packet data pointer from the packet, const
const uint8_t* getReverseGeocachePacketDataConst(const void* pkt)
{
    return (const uint8_t*) (pkt + 2);
}

//! Complete a packet after the data have been encoded
void finishReverseGeocachePacket(void* pkt, int size, uint32_t packetID)
{
    uint8_t *ptr = (uint8_t*) pkt;
    
    //Copy across the size and the ID
    ptr[0] = packetID;
    ptr[1] = size;
}

//! \return the size of a packet from the packet header
int getReverseGeocachePacketSize(const void* pkt)
{
    uint8_t *ptr = (uint8_t*) pkt;
    
    return ptr[1];
}

//! \return the ID of a packet from the packet header
uint32_t getReverseGeocachePacketID(const void* pkt)
{
    uint8_t *ptr = (uint8_t*) pkt;
    
    return ptr[0];
}
