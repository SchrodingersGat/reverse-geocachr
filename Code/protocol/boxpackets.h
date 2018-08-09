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

//! Create the UnlockSettings packet
void encodeUnlockSettingsPacket(void* pkt, const char password[32]);

//! Decode the UnlockSettings packet
int decodeUnlockSettingsPacket(const void* pkt, char password[32]);

//! return the packet ID for the UnlockSettings packet
#define getUnlockSettingsPacketID() (MSG_UNLOCK_SETTINGS)

//! return the minimum encoded length for the UnlockSettings packet
#define getUnlockSettingsMinDataLength() (1)

//! return the maximum encoded length for the UnlockSettings packet
#define getUnlockSettingsMaxDataLength() (32)

//! Create the LockSettings packet
void encodeLockSettingsPacket(void* pkt, const char password[32]);

//! Decode the LockSettings packet
int decodeLockSettingsPacket(const void* pkt, char password[32]);

//! return the packet ID for the LockSettings packet
#define getLockSettingsPacketID() (MSG_LOCK_SETTINGS)

//! return the minimum encoded length for the LockSettings packet
#define getLockSettingsMinDataLength() (1)

//! return the maximum encoded length for the LockSettings packet
#define getLockSettingsMaxDataLength() (32)

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

//! Create the EnableDebug packet
void encodeEnableDebugPacket(void* pkt, uint8_t debugOn);

//! Decode the EnableDebug packet
int decodeEnableDebugPacket(const void* pkt, uint8_t* debugOn);

//! return the packet ID for the EnableDebug packet
#define getEnableDebugPacketID() (MSG_ENABLE_DEBUG_MODE)

//! return the minimum encoded length for the EnableDebug packet
#define getEnableDebugMinDataLength() (1)

//! return the maximum encoded length for the EnableDebug packet
#define getEnableDebugMaxDataLength() (1)

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

typedef struct
{
    uint8_t  state;                 //!< State machine status
    unsigned locked : 1;           
    uint8_t  charge;                //!< Battery charge estimate, 0% to 100%
    unsigned passwordProtected : 1; //!< Box is protected with password
    unsigned gpsConnection : 1;     //!< 1 = GPS unit detected
    unsigned gpsStatus : 2;         //!< GPS Status
    unsigned charging : 1;          //!< Battery charging status
    unsigned debug : 1;            
    unsigned settingsError : 1;     //!< Settings could not be loaded from EEPROM
}BoxStatus_t;

//! Create the BoxStatus packet
void encodeBoxStatusPacketStructure(void* pkt, const BoxStatus_t* user);

//! Decode the BoxStatus packet
int decodeBoxStatusPacketStructure(const void* pkt, BoxStatus_t* user);

//! Create the BoxStatus packet
void encodeBoxStatusPacket(void* pkt, uint8_t state, unsigned locked, uint8_t charge, unsigned passwordProtected, unsigned gpsConnection, unsigned gpsStatus, unsigned charging, unsigned debug, unsigned settingsError);

//! Decode the BoxStatus packet
int decodeBoxStatusPacket(const void* pkt, uint8_t* state, unsigned* locked, uint8_t* charge, unsigned* passwordProtected, unsigned* gpsConnection, unsigned* gpsStatus, unsigned* charging, unsigned* debug, unsigned* settingsError);

//! return the packet ID for the BoxStatus packet
#define getBoxStatusPacketID() (MSG_SYSTEM_STATUS)

//! return the minimum encoded length for the BoxStatus packet
#define getBoxStatusMinDataLength() (4)

//! return the maximum encoded length for the BoxStatus packet
#define getBoxStatusMaxDataLength() (4)

//! Create the RequestBoxStatus packet
void encodeRequestBoxStatusPacket(void* pkt);

//! Decode the RequestBoxStatus packet
int decodeRequestBoxStatusPacket(const void* pkt);

//! return the packet ID for the RequestBoxStatus packet
#define getRequestBoxStatusPacketID() (MSG_SYSTEM_STATUS)

//! return the minimum encoded length for the RequestBoxStatus packet
#define getRequestBoxStatusMinDataLength() 0

//! return the maximum encoded length for the RequestBoxStatus packet
#define getRequestBoxStatusMaxDataLength() 0

typedef struct
{
    uint8_t  totalClues;   //!< Total number of clues
    uint8_t  currentClue;  //!< Current clue index
    uint16_t pwmLocked;    //!< PWM value for locked position
    uint16_t pwmUnlocked;  //!< PWM value for unlocked position
    char     password[32]; //!< Password
}BoxSettings_t;

// Initial and verify values for BoxSettings
#define ReverseGeocache_BoxSettings_totalClues_InitValue 0
#define ReverseGeocache_BoxSettings_currentClue_InitValue 0
#define ReverseGeocache_BoxSettings_pwmLocked_InitValue 1000
#define ReverseGeocache_BoxSettings_pwmLocked_VerifyMin 500
#define ReverseGeocache_BoxSettings_pwmLocked_VerifyMax 2500
#define ReverseGeocache_BoxSettings_pwmUnlocked_InitValue 2000
#define ReverseGeocache_BoxSettings_pwmUnlocked_VerifyMin 500
#define ReverseGeocache_BoxSettings_pwmUnlocked_VerifyMax 2500

//! Set a BoxSettings_t structure to initial values
void initBoxSettings_t(BoxSettings_t* user);

//! Verify a BoxSettings_t structure has acceptable values
int verifyBoxSettings_t(BoxSettings_t* user);

//! Create the BoxSettings packet
void encodeBoxSettingsPacketStructure(void* pkt, const BoxSettings_t* user);

//! Decode the BoxSettings packet
int decodeBoxSettingsPacketStructure(const void* pkt, BoxSettings_t* user);

//! Create the BoxSettings packet
void encodeBoxSettingsPacket(void* pkt, uint8_t totalClues, uint8_t currentClue, uint16_t pwmLocked, uint16_t pwmUnlocked, const char password[32]);

//! Decode the BoxSettings packet
int decodeBoxSettingsPacket(const void* pkt, uint8_t* totalClues, uint8_t* currentClue, uint16_t* pwmLocked, uint16_t* pwmUnlocked, char password[32]);

//! return the packet ID for the BoxSettings packet
#define getBoxSettingsPacketID() (MSG_SYSTEM_SETTINGS)

//! return the minimum encoded length for the BoxSettings packet
#define getBoxSettingsMinDataLength() (7)

//! return the maximum encoded length for the BoxSettings packet
#define getBoxSettingsMaxDataLength() (38)

//! Create the RequestBoxSettings packet
void encodeRequestBoxSettingsPacket(void* pkt);

//! Decode the RequestBoxSettings packet
int decodeRequestBoxSettingsPacket(const void* pkt);

//! return the packet ID for the RequestBoxSettings packet
#define getRequestBoxSettingsPacketID() (MSG_SYSTEM_SETTINGS)

//! return the minimum encoded length for the RequestBoxSettings packet
#define getRequestBoxSettingsMinDataLength() 0

//! return the maximum encoded length for the RequestBoxSettings packet
#define getRequestBoxSettingsMaxDataLength() 0

typedef struct
{
    uint16_t serialNumber; //!< Box serial number
    uint8_t  versionMajor; //!< Firmware version, major
    uint8_t  versionMinor; //!< Firmware version, minor
    uint8_t  pcbRevision;  //!< PCB revision
}BoxVersion_t;

//! Create the BoxVersion packet
void encodeBoxVersionPacketStructure(void* pkt, const BoxVersion_t* user);

//! Decode the BoxVersion packet
int decodeBoxVersionPacketStructure(const void* pkt, BoxVersion_t* user);

//! Create the BoxVersion packet
void encodeBoxVersionPacket(void* pkt, uint16_t serialNumber, uint8_t versionMajor, uint8_t versionMinor, uint8_t pcbRevision);

//! Decode the BoxVersion packet
int decodeBoxVersionPacket(const void* pkt, uint16_t* serialNumber, uint8_t* versionMajor, uint8_t* versionMinor, uint8_t* pcbRevision);

//! return the packet ID for the BoxVersion packet
#define getBoxVersionPacketID() (MSG_SYSTEM_VERSION)

//! return the minimum encoded length for the BoxVersion packet
#define getBoxVersionMinDataLength() (5)

//! return the maximum encoded length for the BoxVersion packet
#define getBoxVersionMaxDataLength() (5)

//! Create the RequestBoxVersion packet
void encodeRequestBoxVersionPacket(void* pkt);

//! Decode the RequestBoxVersion packet
int decodeRequestBoxVersionPacket(const void* pkt);

//! return the packet ID for the RequestBoxVersion packet
#define getRequestBoxVersionPacketID() (MSG_SYSTEM_VERSION)

//! return the minimum encoded length for the RequestBoxVersion packet
#define getRequestBoxVersionMinDataLength() 0

//! return the maximum encoded length for the RequestBoxVersion packet
#define getRequestBoxVersionMaxDataLength() 0

typedef struct
{
    uint8_t    clueNumber;
    Waypoint_t clueInfo;  
    uint32_t   checksum;   //!< Waypoint checksum
}ClueInfo_t;

//! Create the ClueInfo packet
void encodeClueInfoPacket(void* pkt, uint8_t clueNumber, const Waypoint_t* clueInfo, uint32_t checksum);

//! Decode the ClueInfo packet
int decodeClueInfoPacket(const void* pkt, uint8_t* clueNumber, Waypoint_t* clueInfo, uint32_t* checksum);

//! return the packet ID for the ClueInfo packet
#define getClueInfoPacketID() (MSG_CLUE_INFO)

//! return the minimum encoded length for the ClueInfo packet
#define getClueInfoMinDataLength() (17)

//! return the maximum encoded length for the ClueInfo packet
#define getClueInfoMaxDataLength() (17)

//! Create the RequestClueInfo packet
void encodeRequestClueInfoPacket(void* pkt, uint8_t clueNumber);

//! Decode the RequestClueInfo packet
int decodeRequestClueInfoPacket(const void* pkt, uint8_t* clueNumber);

//! return the packet ID for the RequestClueInfo packet
#define getRequestClueInfoPacketID() (MSG_CLUE_INFO)

//! return the minimum encoded length for the RequestClueInfo packet
#define getRequestClueInfoMinDataLength() (1)

//! return the maximum encoded length for the RequestClueInfo packet
#define getRequestClueInfoMaxDataLength() (1)

typedef struct
{
    uint8_t    clueNumber; //!< Index of clue
    uint8_t    lineNumber; //!< Line number
    ClueLine_t lineText;   //!< Line data
}ClueLineText_t;

//! Create the ClueLineText packet
void encodeClueLineTextPacket(void* pkt, uint8_t clueNumber, uint8_t lineNumber, const ClueLine_t* lineText);

//! Decode the ClueLineText packet
int decodeClueLineTextPacket(const void* pkt, uint8_t* clueNumber, uint8_t* lineNumber, ClueLine_t* lineText);

//! return the packet ID for the ClueLineText packet
#define getClueLineTextPacketID() (MSG_CLUE_LINE)

//! return the minimum encoded length for the ClueLineText packet
#define getClueLineTextMinDataLength() (3)

//! return the maximum encoded length for the ClueLineText packet
#define getClueLineTextMaxDataLength() (CLUE_LINE_LEN_MAX+2)

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
