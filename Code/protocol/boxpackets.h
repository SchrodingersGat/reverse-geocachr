// boxpackets.h was generated by ProtoGen version 2.4.b

#ifndef _BOXPACKETS_H
#define _BOXPACKETS_H

// C++ compilers: don't mangle us
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \file
 */

#include "ReverseGeocacheProtocol.h"
#include "boxdefines.h"

//! Create the Reset packet
void encodeResetPacket(void* pkt);

//! Decode the Reset packet
int decodeResetPacket(const void* pkt);

//! return the packet ID for the Reset packet
#define getResetPacketID() (MSG_RESET_INTO_BOOTLOADER)

//! return the minimum encoded length for the Reset packet
#define getResetMinDataLength() 0

//! return the maximum encoded length for the Reset packet
#define getResetMaxDataLength() 0

//! Create the Unlock packet
void encodeUnlockPacket(void* pkt);

//! Decode the Unlock packet
int decodeUnlockPacket(const void* pkt);

//! return the packet ID for the Unlock packet
#define getUnlockPacketID() (MSG_UNLOCK)

//! return the minimum encoded length for the Unlock packet
#define getUnlockMinDataLength() 0

//! return the maximum encoded length for the Unlock packet
#define getUnlockMaxDataLength() 0

//! Create the Lock packet
void encodeLockPacket(void* pkt);

//! Decode the Lock packet
int decodeLockPacket(const void* pkt);

//! return the packet ID for the Lock packet
#define getLockPacketID() (MSG_LOCK)

//! return the minimum encoded length for the Lock packet
#define getLockMinDataLength() 0

//! return the maximum encoded length for the Lock packet
#define getLockMaxDataLength() 0

//! Create the NextClue packet
void encodeNextCluePacket(void* pkt);

//! Decode the NextClue packet
int decodeNextCluePacket(const void* pkt);

//! return the packet ID for the NextClue packet
#define getNextCluePacketID() (MSG_NEXT_CLUE)

//! return the minimum encoded length for the NextClue packet
#define getNextClueMinDataLength() 0

//! return the maximum encoded length for the NextClue packet
#define getNextClueMaxDataLength() 0

//! Create the PrevClue packet
void encodePrevCluePacket(void* pkt);

//! Decode the PrevClue packet
int decodePrevCluePacket(const void* pkt);

//! return the packet ID for the PrevClue packet
#define getPrevCluePacketID() (MSG_PREV_CLUE)

//! return the minimum encoded length for the PrevClue packet
#define getPrevClueMinDataLength() 0

//! return the maximum encoded length for the PrevClue packet
#define getPrevClueMaxDataLength() 0

//! Create the FirstClue packet
void encodeFirstCluePacket(void* pkt);

//! Decode the FirstClue packet
int decodeFirstCluePacket(const void* pkt);

//! return the packet ID for the FirstClue packet
#define getFirstCluePacketID() (MSG_FIRST_CLUE)

//! return the minimum encoded length for the FirstClue packet
#define getFirstClueMinDataLength() 0

//! return the maximum encoded length for the FirstClue packet
#define getFirstClueMaxDataLength() 0

//! Create the LastClue packet
void encodeLastCluePacket(void* pkt);

//! Decode the LastClue packet
int decodeLastCluePacket(const void* pkt);

//! return the packet ID for the LastClue packet
#define getLastCluePacketID() (MSG_LAST_CLUE)

//! return the minimum encoded length for the LastClue packet
#define getLastClueMinDataLength() 0

//! return the maximum encoded length for the LastClue packet
#define getLastClueMaxDataLength() 0

//! Create the Bootload packet
void encodeBootloadPacket(void* pkt);

//! Decode the Bootload packet
int decodeBootloadPacket(const void* pkt);

//! return the packet ID for the Bootload packet
#define getBootloadPacketID() (MSG_RESET_INTO_BOOTLOADER)

//! return the minimum encoded length for the Bootload packet
#define getBootloadMinDataLength() 0

//! return the maximum encoded length for the Bootload packet
#define getBootloadMaxDataLength() 0

//! Create the EnableDebug packet
void encodeEnableDebugPacket(void* pkt);

//! Decode the EnableDebug packet
int decodeEnableDebugPacket(const void* pkt);

//! return the packet ID for the EnableDebug packet
#define getEnableDebugPacketID() (MSG_ENABLE_DEBUG_MODE)

//! return the minimum encoded length for the EnableDebug packet
#define getEnableDebugMinDataLength() 0

//! return the maximum encoded length for the EnableDebug packet
#define getEnableDebugMaxDataLength() 0

//! Create the SetClueCount packet
void encodeSetClueCountPacket(void* pkt, uint8_t clueCount);

//! Decode the SetClueCount packet
int decodeSetClueCountPacket(const void* pkt, uint8_t* clueCount);

//! return the packet ID for the SetClueCount packet
#define getSetClueCountPacketID() (MSG_SET_CLUE_COUNT)

//! return the minimum encoded length for the SetClueCount packet
#define getSetClueCountMinDataLength() (1)

//! return the maximum encoded length for the SetClueCount packet
#define getSetClueCountMaxDataLength() (1)

//! Create the ValidateClues packet
void encodeValidateCluesPacket(void* pkt);

//! Decode the ValidateClues packet
int decodeValidateCluesPacket(const void* pkt);

//! return the packet ID for the ValidateClues packet
#define getValidateCluesPacketID() (MSG_VALIDATE_CLUES)

//! return the minimum encoded length for the ValidateClues packet
#define getValidateCluesMinDataLength() 0

//! return the maximum encoded length for the ValidateClues packet
#define getValidateCluesMaxDataLength() 0

//! Create the InvalidateClues packet
void encodeInvalidateCluesPacket(void* pkt);

//! Decode the InvalidateClues packet
int decodeInvalidateCluesPacket(const void* pkt);

//! return the packet ID for the InvalidateClues packet
#define getInvalidateCluesPacketID() (MSG_VALIDATE_CLUES)

//! return the minimum encoded length for the InvalidateClues packet
#define getInvalidateCluesMinDataLength() 0

//! return the maximum encoded length for the InvalidateClues packet
#define getInvalidateCluesMaxDataLength() 0

//! Create the BoxInfo packet
void encodeBoxInfoPacket(void* pkt, const BoxInfo_t* info);

//! Decode the BoxInfo packet
int decodeBoxInfoPacket(const void* pkt, BoxInfo_t* info);

//! return the packet ID for the BoxInfo packet
#define getBoxInfoPacketID() (MSG_SYSTEM_INFO)

//! return the minimum encoded length for the BoxInfo packet
#define getBoxInfoMinDataLength() (9)

//! return the maximum encoded length for the BoxInfo packet
#define getBoxInfoMaxDataLength() (9)

//! Create the RequestBoxInfo packet
void encodeRequestBoxInfoPacket(void* pkt);

//! Decode the RequestBoxInfo packet
int decodeRequestBoxInfoPacket(const void* pkt);

//! return the packet ID for the RequestBoxInfo packet
#define getRequestBoxInfoPacketID() (MSG_SYSTEM_INFO)

//! return the minimum encoded length for the RequestBoxInfo packet
#define getRequestBoxInfoMinDataLength() 0

//! return the maximum encoded length for the RequestBoxInfo packet
#define getRequestBoxInfoMaxDataLength() 0

typedef struct
{
    uint8_t    clueNumber;
    Waypoint_t clueInfo;  
}ClueInfo_t;

//! Create the ClueInfo packet
void encodeClueInfoPacket(void* pkt, uint8_t clueNumber, const Waypoint_t* clueInfo);

//! Decode the ClueInfo packet
int decodeClueInfoPacket(const void* pkt, uint8_t* clueNumber, Waypoint_t* clueInfo);

//! return the packet ID for the ClueInfo packet
#define getClueInfoPacketID() (MSG_CLUE_INFO)

//! return the minimum encoded length for the ClueInfo packet
#define getClueInfoMinDataLength() (13)

//! return the maximum encoded length for the ClueInfo packet
#define getClueInfoMaxDataLength() (13)

//! Create the RequestClueInfo packet
void encodeRequestClueInfoPacket(void* pkt, uint8_t clueNumber);

//! Decode the RequestClueInfo packet
int decodeRequestClueInfoPacket(const void* pkt, uint8_t* clueNumber);

//! return the packet ID for the RequestClueInfo packet
#define getRequestClueInfoPacketID() (MSG_GET_CLUE_INFO)

//! return the minimum encoded length for the RequestClueInfo packet
#define getRequestClueInfoMinDataLength() (1)

//! return the maximum encoded length for the RequestClueInfo packet
#define getRequestClueInfoMaxDataLength() (1)

typedef struct
{
    uint8_t clueNumber;   //!< Index of clue
    uint8_t lineNumber;   //!< Line number
    char    lineText[40]; //!< Line data
}ClueLine_t;

//! Create the ClueLine packet
void encodeClueLinePacket(void* pkt, uint8_t clueNumber, uint8_t lineNumber, const char lineText[40]);

//! Decode the ClueLine packet
int decodeClueLinePacket(const void* pkt, uint8_t* clueNumber, uint8_t* lineNumber, char lineText[40]);

//! return the packet ID for the ClueLine packet
#define getClueLinePacketID() (MSG_CLUE_LINE)

//! return the minimum encoded length for the ClueLine packet
#define getClueLineMinDataLength() (3)

//! return the maximum encoded length for the ClueLine packet
#define getClueLineMaxDataLength() (42)

typedef struct
{
    uint8_t clueNumber;
    uint8_t lineNumber;
}RequestClueLine_t;

//! Create the RequestClueLine packet
void encodeRequestClueLinePacket(void* pkt, uint8_t clueNumber, uint8_t lineNumber);

//! Decode the RequestClueLine packet
int decodeRequestClueLinePacket(const void* pkt, uint8_t* clueNumber, uint8_t* lineNumber);

//! return the packet ID for the RequestClueLine packet
#define getRequestClueLinePacketID() (MSG_CLUE_LINE)

//! return the minimum encoded length for the RequestClueLine packet
#define getRequestClueLineMinDataLength() (2)

//! return the maximum encoded length for the RequestClueLine packet
#define getRequestClueLineMaxDataLength() (2)

#ifdef __cplusplus
}
#endif
#endif
