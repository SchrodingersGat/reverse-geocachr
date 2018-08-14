// boxdefines.h was generated by ProtoGen version 2.4.b

#ifndef _BOXDEFINES_H
#define _BOXDEFINES_H

// C++ compilers: don't mangle us
#ifdef __cplusplus
extern "C" {
#endif

/*!
 * \file
 */

#include "ReverseGeocacheProtocol.h"

typedef struct
{
    unsigned centerText : 1; //!< Text is centered on the screen
}ClueOptionBits_t;

//! return the minimum encoded length for the ClueOptionBits_t structure
#define getMinLengthOfClueOptionBits_t() (1)

//! Encode a ClueOptionBits_t structure into a byte array
void encodeClueOptionBits_t(uint8_t* data, int* bytecount, const ClueOptionBits_t* user);

//! Decode a ClueOptionBits_t structure from a byte array
int decodeClueOptionBits_t(const uint8_t* data, int* bytecount, ClueOptionBits_t* user);

typedef struct
{
    float            lat;       //!< Location latitude
    float            lng;       //!< Location longitude
    uint16_t         threshold; //!< Distance threshold (m)
    uint8_t          type;      //!< Clue type
    ClueOptionBits_t options;   //!< Extra clue options
}Waypoint_t;

// Initial and verify values for Waypoint
#define ReverseGeocache_Waypoint_threshold_VerifyMin 25
#define ReverseGeocache_Waypoint_threshold_VerifyMax 500

//! return the minimum encoded length for the Waypoint_t structure
#define getMinLengthOfWaypoint_t() (12)

//! Encode a Waypoint_t structure into a byte array
void encodeWaypoint_t(uint8_t* data, int* bytecount, const Waypoint_t* user);

//! Decode a Waypoint_t structure from a byte array
int decodeWaypoint_t(const uint8_t* data, int* bytecount, Waypoint_t* user);

//! Verify a Waypoint_t structure has acceptable values
int verifyWaypoint_t(Waypoint_t* user);

typedef struct
{
    char text[CLUE_LINE_LEN_MAX];
}ClueLine_t;

//! return the minimum encoded length for the ClueLine_t structure
#define getMinLengthOfClueLine_t() (1)

//! Encode a ClueLine_t structure into a byte array
void encodeClueLine_t(uint8_t* data, int* bytecount, const ClueLine_t* user);

//! Decode a ClueLine_t structure from a byte array
int decodeClueLine_t(const uint8_t* data, int* bytecount, ClueLine_t* user);

typedef struct
{
    Waypoint_t waypoint;              //!< Waypoint data
    ClueLine_t lines[NUM_CLUE_LINES]; //!< Text data
    uint32_t   checksum;              //!< Clue checksum
}Clue_t;

//! return the minimum encoded length for the Clue_t structure
#define getMinLengthOfClue_t() (NUM_CLUE_LINES*1+16)

//! Encode a Clue_t structure into a byte array
void encodeClue_t(uint8_t* data, int* bytecount, const Clue_t* user);

//! Decode a Clue_t structure from a byte array
int decodeClue_t(const uint8_t* data, int* bytecount, Clue_t* user);

//! Verify a Clue_t structure has acceptable values
int verifyClue_t(Clue_t* user);

#ifdef __cplusplus
}
#endif
#endif
