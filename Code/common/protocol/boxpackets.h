// boxpackets.h was generated by ProtoGen version 1.4.1.a on Sun Apr 3 12:54:54 2016

#ifndef _BOXPACKETS_H
#define _BOXPACKETS_H

// C++ compilers: don't mangle us
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \file
 * \brief boxpackets.h defines the interface for the Unlock packet of the ReverseGeocache protocol stack
 */

#include "ReverseGeocacheProtocol.h"

//! Create the Unlock packet
void encodeUnlockPacket(void* pkt);

//! Decode the Unlock packet
int decodeUnlockPacket(const void* pkt);

//! return the packet ID for the Unlock packet
uint32_t getUnlockPacketID(void);

//! return the minimum data length for the Unlock packet
int getUnlockMinDataLength(void);

//! Create the Lock packet
void encodeLockPacket(void* pkt);

//! Decode the Lock packet
int decodeLockPacket(const void* pkt);

//! return the packet ID for the Lock packet
uint32_t getLockPacketID(void);

//! return the minimum data length for the Lock packet
int getLockMinDataLength(void);

//! Create the NextClue packet
void encodeNextCluePacket(void* pkt);

//! Decode the NextClue packet
int decodeNextCluePacket(const void* pkt);

//! return the packet ID for the NextClue packet
uint32_t getNextCluePacketID(void);

//! return the minimum data length for the NextClue packet
int getNextClueMinDataLength(void);

//! Create the PrevClue packet
void encodePrevCluePacket(void* pkt);

//! Decode the PrevClue packet
int decodePrevCluePacket(const void* pkt);

//! return the packet ID for the PrevClue packet
uint32_t getPrevCluePacketID(void);

//! return the minimum data length for the PrevClue packet
int getPrevClueMinDataLength(void);

//! Create the FirstClue packet
void encodeFirstCluePacket(void* pkt);

//! Decode the FirstClue packet
int decodeFirstCluePacket(const void* pkt);

//! return the packet ID for the FirstClue packet
uint32_t getFirstCluePacketID(void);

//! return the minimum data length for the FirstClue packet
int getFirstClueMinDataLength(void);

//! Create the LAST_CLUE packet
void encodeLAST_CLUEPacket(void* pkt);

//! Decode the LAST_CLUE packet
int decodeLAST_CLUEPacket(const void* pkt);

//! return the packet ID for the LAST_CLUE packet
uint32_t getLAST_CLUEPacketID(void);

//! return the minimum data length for the LAST_CLUE packet
int getLAST_CLUEMinDataLength(void);

//! Create the Bootload packet
void encodeBootloadPacket(void* pkt);

//! Decode the Bootload packet
int decodeBootloadPacket(const void* pkt);

//! return the packet ID for the Bootload packet
uint32_t getBootloadPacketID(void);

//! return the minimum data length for the Bootload packet
int getBootloadMinDataLength(void);

//! Create the EnableDebug packet
void encodeEnableDebugPacket(void* pkt);

//! Decode the EnableDebug packet
int decodeEnableDebugPacket(const void* pkt);

//! return the packet ID for the EnableDebug packet
uint32_t getEnableDebugPacketID(void);

//! return the minimum data length for the EnableDebug packet
int getEnableDebugMinDataLength(void);

//! Create the SetClueCount packet
void encodeSetClueCountPacket(void* pkt, uint8_t clueCount);

//! Decode the SetClueCount packet
int decodeSetClueCountPacket(const void* pkt, uint8_t* clueCount);

//! return the packet ID for the SetClueCount packet
uint32_t getSetClueCountPacketID(void);

//! return the minimum data length for the SetClueCount packet
int getSetClueCountMinDataLength(void);

//! Create the ValidateClues packet
void encodeValidateCluesPacket(void* pkt);

//! Decode the ValidateClues packet
int decodeValidateCluesPacket(const void* pkt);

//! return the packet ID for the ValidateClues packet
uint32_t getValidateCluesPacketID(void);

//! return the minimum data length for the ValidateClues packet
int getValidateCluesMinDataLength(void);

//! Create the InvalidateClues packet
void encodeInvalidateCluesPacket(void* pkt);

//! Decode the InvalidateClues packet
int decodeInvalidateCluesPacket(const void* pkt);

//! return the packet ID for the InvalidateClues packet
uint32_t getInvalidateCluesPacketID(void);

//! return the minimum data length for the InvalidateClues packet
int getInvalidateCluesMinDataLength(void);

#include "boxdefines.h"

//! Create the BoxInfo packet
void encodeBoxInfoPacket(void* pkt, const BoxInfo_t* info);

//! Decode the BoxInfo packet
int decodeBoxInfoPacket(const void* pkt, BoxInfo_t* info);

//! return the packet ID for the BoxInfo packet
uint32_t getBoxInfoPacketID(void);

//! return the minimum data length for the BoxInfo packet
int getBoxInfoMinDataLength(void);

//! Create the RequestBoxInfo packet
void encodeRequestBoxInfoPacket(void* pkt);

//! Decode the RequestBoxInfo packet
int decodeRequestBoxInfoPacket(const void* pkt);

//! return the packet ID for the RequestBoxInfo packet
uint32_t getRequestBoxInfoPacketID(void);

//! return the minimum data length for the RequestBoxInfo packet
int getRequestBoxInfoMinDataLength(void);

typedef struct
{
    uint8_t    clueNumber;
    ClueInfo_t clueInfo;  
}ClueInfo_t;

//! Create the ClueInfo packet
void encodeClueInfoPacket(void* pkt, uint8_t clueNumber, const ClueInfo_t* clueInfo);

//! Decode the ClueInfo packet
int decodeClueInfoPacket(const void* pkt, uint8_t* clueNumber, ClueInfo_t* clueInfo);

//! return the packet ID for the ClueInfo packet
uint32_t getClueInfoPacketID(void);

//! return the minimum data length for the ClueInfo packet
int getClueInfoMinDataLength(void);

//! Create the RequestClueInfo packet
void encodeRequestClueInfoPacket(void* pkt, uint8_t clueNumber);

//! Decode the RequestClueInfo packet
int decodeRequestClueInfoPacket(const void* pkt, uint8_t* clueNumber);

//! return the packet ID for the RequestClueInfo packet
uint32_t getRequestClueInfoPacketID(void);

//! return the minimum data length for the RequestClueInfo packet
int getRequestClueInfoMinDataLength(void);

typedef struct
{
    uint8_t clueNumber;  
    uint8_t lineNumber;  
    char    lineText[40];
}ClueLine_t;

//! Create the ClueLine packet
void encodeClueLinePacket(void* pkt, uint8_t clueNumber, uint8_t lineNumber, const char lineText[40]);

//! Decode the ClueLine packet
int decodeClueLinePacket(const void* pkt, uint8_t* clueNumber, uint8_t* lineNumber, char lineText[40]);

//! return the packet ID for the ClueLine packet
uint32_t getClueLinePacketID(void);

//! return the minimum data length for the ClueLine packet
int getClueLineMinDataLength(void);

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
uint32_t getRequestClueLinePacketID(void);

//! return the minimum data length for the RequestClueLine packet
int getRequestClueLineMinDataLength(void);

#ifdef __cplusplus
}
#endif
#endif
