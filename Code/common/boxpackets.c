// boxpackets.c was generated by ProtoGen version 1.4.1.a on Sun Apr 3 18:12:06 2016

#include "boxpackets.h"
#include "bitfieldspecial.h"
#include "fielddecode.h"
#include "fieldencode.h"
#include "scaleddecode.h"
#include "scaledencode.h"

/*!
 * \brief Create the Unlock packet
 *

 * \param pkt points to the packet which will be created by this function
 */
void encodeUnlockPacket(void* pkt)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getUnlockPacketID());
}

/*!
 * \brief Decode the Unlock packet
 *

 * \param pkt points to the packet being decoded by this function
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeUnlockPacket(const void* pkt)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getUnlockPacketID())
        return 0;

    if(numBytes < getUnlockMinDataLength())
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the Unlock packet
 */
uint32_t getUnlockPacketID(void)
{
    return MSG_UNLOCK;
}

/*!
 * \return the minimum data length in bytes for the Unlock packet
 */
int getUnlockMinDataLength(void)
{
    return 0;
}

/*!
 * \brief Create the Lock packet
 *

 * \param pkt points to the packet which will be created by this function
 */
void encodeLockPacket(void* pkt)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getLockPacketID());
}

/*!
 * \brief Decode the Lock packet
 *

 * \param pkt points to the packet being decoded by this function
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeLockPacket(const void* pkt)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getLockPacketID())
        return 0;

    if(numBytes < getLockMinDataLength())
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the Lock packet
 */
uint32_t getLockPacketID(void)
{
    return MSG_LOCK;
}

/*!
 * \return the minimum data length in bytes for the Lock packet
 */
int getLockMinDataLength(void)
{
    return 0;
}

/*!
 * \brief Create the NextClue packet
 *

 * \param pkt points to the packet which will be created by this function
 */
void encodeNextCluePacket(void* pkt)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getNextCluePacketID());
}

/*!
 * \brief Decode the NextClue packet
 *

 * \param pkt points to the packet being decoded by this function
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeNextCluePacket(const void* pkt)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getNextCluePacketID())
        return 0;

    if(numBytes < getNextClueMinDataLength())
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the NextClue packet
 */
uint32_t getNextCluePacketID(void)
{
    return MSG_NEXT_CLUE;
}

/*!
 * \return the minimum data length in bytes for the NextClue packet
 */
int getNextClueMinDataLength(void)
{
    return 0;
}

/*!
 * \brief Create the PrevClue packet
 *

 * \param pkt points to the packet which will be created by this function
 */
void encodePrevCluePacket(void* pkt)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getPrevCluePacketID());
}

/*!
 * \brief Decode the PrevClue packet
 *

 * \param pkt points to the packet being decoded by this function
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodePrevCluePacket(const void* pkt)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getPrevCluePacketID())
        return 0;

    if(numBytes < getPrevClueMinDataLength())
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the PrevClue packet
 */
uint32_t getPrevCluePacketID(void)
{
    return MSG_PREV_CLUE;
}

/*!
 * \return the minimum data length in bytes for the PrevClue packet
 */
int getPrevClueMinDataLength(void)
{
    return 0;
}

/*!
 * \brief Create the FirstClue packet
 *

 * \param pkt points to the packet which will be created by this function
 */
void encodeFirstCluePacket(void* pkt)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getFirstCluePacketID());
}

/*!
 * \brief Decode the FirstClue packet
 *

 * \param pkt points to the packet being decoded by this function
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeFirstCluePacket(const void* pkt)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getFirstCluePacketID())
        return 0;

    if(numBytes < getFirstClueMinDataLength())
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the FirstClue packet
 */
uint32_t getFirstCluePacketID(void)
{
    return MSG_FIRST_CLUE;
}

/*!
 * \return the minimum data length in bytes for the FirstClue packet
 */
int getFirstClueMinDataLength(void)
{
    return 0;
}

/*!
 * \brief Create the LastClue packet
 *

 * \param pkt points to the packet which will be created by this function
 */
void encodeLastCluePacket(void* pkt)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getLastCluePacketID());
}

/*!
 * \brief Decode the LastClue packet
 *

 * \param pkt points to the packet being decoded by this function
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeLastCluePacket(const void* pkt)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getLastCluePacketID())
        return 0;

    if(numBytes < getLastClueMinDataLength())
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the LastClue packet
 */
uint32_t getLastCluePacketID(void)
{
    return MSG_LAST_CLUE;
}

/*!
 * \return the minimum data length in bytes for the LastClue packet
 */
int getLastClueMinDataLength(void)
{
    return 0;
}

/*!
 * \brief Create the Bootload packet
 *

 * \param pkt points to the packet which will be created by this function
 */
void encodeBootloadPacket(void* pkt)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getBootloadPacketID());
}

/*!
 * \brief Decode the Bootload packet
 *

 * \param pkt points to the packet being decoded by this function
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeBootloadPacket(const void* pkt)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getBootloadPacketID())
        return 0;

    if(numBytes < getBootloadMinDataLength())
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the Bootload packet
 */
uint32_t getBootloadPacketID(void)
{
    return MSG_RESET_INTO_BOOTLOADER;
}

/*!
 * \return the minimum data length in bytes for the Bootload packet
 */
int getBootloadMinDataLength(void)
{
    return 0;
}

/*!
 * \brief Create the EnableDebug packet
 *

 * \param pkt points to the packet which will be created by this function
 */
void encodeEnableDebugPacket(void* pkt)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getEnableDebugPacketID());
}

/*!
 * \brief Decode the EnableDebug packet
 *

 * \param pkt points to the packet being decoded by this function
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeEnableDebugPacket(const void* pkt)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getEnableDebugPacketID())
        return 0;

    if(numBytes < getEnableDebugMinDataLength())
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the EnableDebug packet
 */
uint32_t getEnableDebugPacketID(void)
{
    return MSG_ENABLE_DEBUG_MODE;
}

/*!
 * \return the minimum data length in bytes for the EnableDebug packet
 */
int getEnableDebugMinDataLength(void)
{
    return 0;
}

/*!
 * \brief Create the SetClueCount packet
 *

 * \param pkt points to the packet which will be created by this function
 * \param clueCount is 
 */
void encodeSetClueCountPacket(void* pkt, uint8_t clueCount)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    uint8ToBytes((uint8_t)clueCount, data, &byteindex);

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getSetClueCountPacketID());
}

/*!
 * \brief Decode the SetClueCount packet
 *

 * \param pkt points to the packet being decoded by this function
 * \param clueCount receives 
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeSetClueCountPacket(const void* pkt, uint8_t* clueCount)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getSetClueCountPacketID())
        return 0;

    if(numBytes < getSetClueCountMinDataLength())
        return 0;

    *clueCount = (uint8_t)uint8FromBytes(data, &byteindex);

    return 1;
}

/*!
 * \return the packet ID for the SetClueCount packet
 */
uint32_t getSetClueCountPacketID(void)
{
    return MSG_SET_CLUE_COUNT;
}

/*!
 * \return the minimum data length in bytes for the SetClueCount packet
 */
int getSetClueCountMinDataLength(void)
{
    return 1;
}

/*!
 * \brief Create the ValidateClues packet
 *

 * \param pkt points to the packet which will be created by this function
 */
void encodeValidateCluesPacket(void* pkt)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getValidateCluesPacketID());
}

/*!
 * \brief Decode the ValidateClues packet
 *

 * \param pkt points to the packet being decoded by this function
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeValidateCluesPacket(const void* pkt)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getValidateCluesPacketID())
        return 0;

    if(numBytes < getValidateCluesMinDataLength())
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the ValidateClues packet
 */
uint32_t getValidateCluesPacketID(void)
{
    return MSG_VALIDATE_CLUES;
}

/*!
 * \return the minimum data length in bytes for the ValidateClues packet
 */
int getValidateCluesMinDataLength(void)
{
    return 0;
}

/*!
 * \brief Create the InvalidateClues packet
 *

 * \param pkt points to the packet which will be created by this function
 */
void encodeInvalidateCluesPacket(void* pkt)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getInvalidateCluesPacketID());
}

/*!
 * \brief Decode the InvalidateClues packet
 *

 * \param pkt points to the packet being decoded by this function
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeInvalidateCluesPacket(const void* pkt)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getInvalidateCluesPacketID())
        return 0;

    if(numBytes < getInvalidateCluesMinDataLength())
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the InvalidateClues packet
 */
uint32_t getInvalidateCluesPacketID(void)
{
    return MSG_VALIDATE_CLUES;
}

/*!
 * \return the minimum data length in bytes for the InvalidateClues packet
 */
int getInvalidateCluesMinDataLength(void)
{
    return 0;
}

/*!
 * \brief Create the BoxInfo packet
 *

 * \param pkt points to the packet which will be created by this function
 * \param info is 
 */
void encodeBoxInfoPacket(void* pkt, const BoxInfo_t* info)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    encodeBoxInfo_t(data, &byteindex, info);

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getBoxInfoPacketID());
}

/*!
 * \brief Decode the BoxInfo packet
 *

 * \param pkt points to the packet being decoded by this function
 * \param info receives 
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeBoxInfoPacket(const void* pkt, BoxInfo_t* info)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getBoxInfoPacketID())
        return 0;

    if(numBytes < getBoxInfoMinDataLength())
        return 0;

    if(decodeBoxInfo_t(data, &byteindex, info) == 0)
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the BoxInfo packet
 */
uint32_t getBoxInfoPacketID(void)
{
    return MSG_SYSTEM_INFO;
}

/*!
 * \return the minimum data length in bytes for the BoxInfo packet
 */
int getBoxInfoMinDataLength(void)
{
    return 9;
}

/*!
 * \brief Create the RequestBoxInfo packet
 *

 * \param pkt points to the packet which will be created by this function
 */
void encodeRequestBoxInfoPacket(void* pkt)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getRequestBoxInfoPacketID());
}

/*!
 * \brief Decode the RequestBoxInfo packet
 *

 * \param pkt points to the packet being decoded by this function
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeRequestBoxInfoPacket(const void* pkt)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getRequestBoxInfoPacketID())
        return 0;

    if(numBytes < getRequestBoxInfoMinDataLength())
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the RequestBoxInfo packet
 */
uint32_t getRequestBoxInfoPacketID(void)
{
    return MSG_SYSTEM_INFO;
}

/*!
 * \return the minimum data length in bytes for the RequestBoxInfo packet
 */
int getRequestBoxInfoMinDataLength(void)
{
    return 0;
}

/*!
 * \brief Create the ClueInfo packet
 *

 * \param pkt points to the packet which will be created by this function
 * \param clueNumber is 
 * \param clueInfo is 
 */
void encodeClueInfoPacket(void* pkt, uint8_t clueNumber, const Waypoint_t* clueInfo)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    uint8ToBytes((uint8_t)clueNumber, data, &byteindex);

    encodeWaypoint_t(data, &byteindex, clueInfo);

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getClueInfoPacketID());
}

/*!
 * \brief Decode the ClueInfo packet
 *

 * \param pkt points to the packet being decoded by this function
 * \param clueNumber receives 
 * \param clueInfo receives 
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeClueInfoPacket(const void* pkt, uint8_t* clueNumber, Waypoint_t* clueInfo)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getClueInfoPacketID())
        return 0;

    if(numBytes < getClueInfoMinDataLength())
        return 0;

    *clueNumber = (uint8_t)uint8FromBytes(data, &byteindex);

    if(decodeWaypoint_t(data, &byteindex, clueInfo) == 0)
        return 0;

    return 1;
}

/*!
 * \return the packet ID for the ClueInfo packet
 */
uint32_t getClueInfoPacketID(void)
{
    return MSG_CLUE_INFO;
}

/*!
 * \return the minimum data length in bytes for the ClueInfo packet
 */
int getClueInfoMinDataLength(void)
{
    return 13;
}

/*!
 * \brief Create the RequestClueInfo packet
 *

 * \param pkt points to the packet which will be created by this function
 * \param clueNumber is 
 */
void encodeRequestClueInfoPacket(void* pkt, uint8_t clueNumber)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    uint8ToBytes((uint8_t)clueNumber, data, &byteindex);

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getRequestClueInfoPacketID());
}

/*!
 * \brief Decode the RequestClueInfo packet
 *

 * \param pkt points to the packet being decoded by this function
 * \param clueNumber receives 
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeRequestClueInfoPacket(const void* pkt, uint8_t* clueNumber)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getRequestClueInfoPacketID())
        return 0;

    if(numBytes < getRequestClueInfoMinDataLength())
        return 0;

    *clueNumber = (uint8_t)uint8FromBytes(data, &byteindex);

    return 1;
}

/*!
 * \return the packet ID for the RequestClueInfo packet
 */
uint32_t getRequestClueInfoPacketID(void)
{
    return MSG_CLUE_INFO;
}

/*!
 * \return the minimum data length in bytes for the RequestClueInfo packet
 */
int getRequestClueInfoMinDataLength(void)
{
    return 1;
}

/*!
 * \brief Create the ClueLine packet
 *

 * \param pkt points to the packet which will be created by this function
 * \param clueNumber is 
 * \param lineNumber is 
 * \param lineText is 
 */
void encodeClueLinePacket(void* pkt, uint8_t clueNumber, uint8_t lineNumber, const char lineText[40])
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    uint8ToBytes((uint8_t)clueNumber, data, &byteindex);

    uint8ToBytes((uint8_t)lineNumber, data, &byteindex);

    stringToBytes(lineText, data, &byteindex, 40, 0);

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getClueLinePacketID());
}

/*!
 * \brief Decode the ClueLine packet
 *

 * \param pkt points to the packet being decoded by this function
 * \param clueNumber receives 
 * \param lineNumber receives 
 * \param lineText receives 
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeClueLinePacket(const void* pkt, uint8_t* clueNumber, uint8_t* lineNumber, char lineText[40])
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getClueLinePacketID())
        return 0;

    if(numBytes < getClueLineMinDataLength())
        return 0;

    *clueNumber = (uint8_t)uint8FromBytes(data, &byteindex);

    *lineNumber = (uint8_t)uint8FromBytes(data, &byteindex);

    stringFromBytes(lineText, data, &byteindex, 40, 0);

    return 1;
}

/*!
 * \return the packet ID for the ClueLine packet
 */
uint32_t getClueLinePacketID(void)
{
    return MSG_CLUE_LINE;
}

/*!
 * \return the minimum data length in bytes for the ClueLine packet
 */
int getClueLineMinDataLength(void)
{
    return 3;
}

/*!
 * \brief Create the RequestClueLine packet
 *

 * \param pkt points to the packet which will be created by this function
 * \param clueNumber is 
 * \param lineNumber is 
 */
void encodeRequestClueLinePacket(void* pkt, uint8_t clueNumber, uint8_t lineNumber)
{
    uint8_t* data = getReverseGeocachePacketData(pkt);
    int byteindex = 0;

    uint8ToBytes((uint8_t)clueNumber, data, &byteindex);

    uint8ToBytes((uint8_t)lineNumber, data, &byteindex);

    // complete the process of creating the packet
    finishReverseGeocachePacket(pkt, byteindex, getRequestClueLinePacketID());
}

/*!
 * \brief Decode the RequestClueLine packet
 *

 * \param pkt points to the packet being decoded by this function
 * \param clueNumber receives 
 * \param lineNumber receives 
 * \return 0 is returned if the packet ID or size is wrong, else 1
 */
int decodeRequestClueLinePacket(const void* pkt, uint8_t* clueNumber, uint8_t* lineNumber)
{
    int byteindex = 0;
    const uint8_t* data = getReverseGeocachePacketDataConst(pkt);
    int numBytes = getReverseGeocachePacketSize(pkt);

    if(getReverseGeocachePacketID(pkt) != getRequestClueLinePacketID())
        return 0;

    if(numBytes < getRequestClueLineMinDataLength())
        return 0;

    *clueNumber = (uint8_t)uint8FromBytes(data, &byteindex);

    *lineNumber = (uint8_t)uint8FromBytes(data, &byteindex);

    return 1;
}

/*!
 * \return the packet ID for the RequestClueLine packet
 */
uint32_t getRequestClueLinePacketID(void)
{
    return MSG_CLUE_LINE;
}

/*!
 * \return the minimum data length in bytes for the RequestClueLine packet
 */
int getRequestClueLineMinDataLength(void)
{
    return 2;
}
// end of boxpackets.c
