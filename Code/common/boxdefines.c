// boxdefines.c was generated by ProtoGen version 1.4.1.a on Sat Jun 11 15:35:13 2016

#include "boxdefines.h"
#include "bitfieldspecial.h"
#include "fielddecode.h"
#include "fieldencode.h"
#include "scaleddecode.h"
#include "scaledencode.h"

/*!
 * \brief Encode a BoxStatus_t structure into a byte array
 *

 * \param data points to the byte array to add encoded data to
 * \param bytecount points to the starting location in the byte array, and will be incremented by the number of encoded bytes.
 * \param user is the data to encode in the byte array
 */
void encodeBoxStatus_t(uint8_t* data, int* bytecount, const BoxStatus_t* user)
{
    int byteindex = *bytecount;    int bitcount = 0;

    encodeBitfield((unsigned int)user->locked, data, &byteindex, &bitcount, 1);

    // 1 = GPS unit detected
    encodeBitfield((unsigned int)user->gpsConnection, data, &byteindex, &bitcount, 1);

    // GPS Status
    encodeBitfield((unsigned int)user->gpsStatus, data, &byteindex, &bitcount, 2);

    // Battery charging status
    encodeBitfield((unsigned int)user->charging, data, &byteindex, &bitcount, 1);

    encodeBitfield((unsigned int)user->debug, data, &byteindex, &bitcount, 1);
    bitcount = 0; byteindex++; // close bit field, go to next byte

    *bytecount = byteindex;
}

/*!
 * \brief Decode a BoxStatus_t structure from a byte array
 *

 * \param data points to the byte array to decoded data from
 * \param bytecount points to the starting location in the byte array, and will be incremented by the number of bytes decoded
 * \param user is the data to decode from the byte array
 * \return 1 if the data are decoded, else 0. If 0 is returned bytecount will not be updated.
 */
int decodeBoxStatus_t(const uint8_t* data, int* bytecount, BoxStatus_t* user)
{
    int byteindex = *bytecount;    int bitcount = 0;

    user->locked = (unsigned)decodeBitfield(data, &byteindex, &bitcount, 1);

    // 1 = GPS unit detected
    user->gpsConnection = (unsigned)decodeBitfield(data, &byteindex, &bitcount, 1);

    // GPS Status
    user->gpsStatus = (unsigned)decodeBitfield(data, &byteindex, &bitcount, 2);

    // Battery charging status
    user->charging = (unsigned)decodeBitfield(data, &byteindex, &bitcount, 1);

    user->debug = (unsigned)decodeBitfield(data, &byteindex, &bitcount, 1);
    bitcount = 0; byteindex++; // close bit field, go to next byte

    *bytecount = byteindex;

    return 1;
}

/*!
 * \brief Encode a ClueOptions_t structure into a byte array
 *

 * \param data points to the byte array to add encoded data to
 * \param bytecount points to the starting location in the byte array, and will be incremented by the number of encoded bytes.
 * \param user is the data to encode in the byte array
 */
void encodeClueOptions_t(uint8_t* data, int* bytecount, const ClueOptions_t* user)
{
    int byteindex = *bytecount;    int bitcount = 0;

    encodeBitfield((unsigned int)user->centerText, data, &byteindex, &bitcount, 1);
    bitcount = 0; byteindex++; // close bit field, go to next byte

    *bytecount = byteindex;
}

/*!
 * \brief Decode a ClueOptions_t structure from a byte array
 *

 * \param data points to the byte array to decoded data from
 * \param bytecount points to the starting location in the byte array, and will be incremented by the number of bytes decoded
 * \param user is the data to decode from the byte array
 * \return 1 if the data are decoded, else 0. If 0 is returned bytecount will not be updated.
 */
int decodeClueOptions_t(const uint8_t* data, int* bytecount, ClueOptions_t* user)
{
    int byteindex = *bytecount;    int bitcount = 0;

    user->centerText = (unsigned)decodeBitfield(data, &byteindex, &bitcount, 1);
    bitcount = 0; byteindex++; // close bit field, go to next byte

    *bytecount = byteindex;

    return 1;
}

/*!
 * \brief Encode a BoxInfo_t structure into a byte array
 *

 * \param data points to the byte array to add encoded data to
 * \param bytecount points to the starting location in the byte array, and will be incremented by the number of encoded bytes.
 * \param user is the data to encode in the byte array
 */
void encodeBoxInfo_t(uint8_t* data, int* bytecount, const BoxInfo_t* user)
{
    int byteindex = *bytecount;

    uint16ToBeBytes((uint16_t)user->serialNumber, data, &byteindex);

    uint8ToBytes((uint8_t)user->versionMajor, data, &byteindex);

    uint8ToBytes((uint8_t)user->versionMinor, data, &byteindex);

    uint8ToBytes((uint8_t)user->pcbRevision, data, &byteindex);

    encodeBoxStatus_t(data, &byteindex, &user->status);

    uint8ToBytes((uint8_t)user->charge, data, &byteindex);

    uint8ToBytes((uint8_t)user->currentClue, data, &byteindex);

    uint8ToBytes((uint8_t)user->totalClues, data, &byteindex);

    *bytecount = byteindex;
}

/*!
 * \brief Decode a BoxInfo_t structure from a byte array
 *

 * \param data points to the byte array to decoded data from
 * \param bytecount points to the starting location in the byte array, and will be incremented by the number of bytes decoded
 * \param user is the data to decode from the byte array
 * \return 1 if the data are decoded, else 0. If 0 is returned bytecount will not be updated.
 */
int decodeBoxInfo_t(const uint8_t* data, int* bytecount, BoxInfo_t* user)
{
    int byteindex = *bytecount;

    user->serialNumber = (uint16_t)uint16FromBeBytes(data, &byteindex);

    user->versionMajor = (uint8_t)uint8FromBytes(data, &byteindex);

    user->versionMinor = (uint8_t)uint8FromBytes(data, &byteindex);

    user->pcbRevision = (uint8_t)uint8FromBytes(data, &byteindex);

    if(decodeBoxStatus_t(data, &byteindex, &user->status) == 0)
        return 0;

    user->charge = (uint8_t)uint8FromBytes(data, &byteindex);

    user->currentClue = (uint8_t)uint8FromBytes(data, &byteindex);

    user->totalClues = (uint8_t)uint8FromBytes(data, &byteindex);

    *bytecount = byteindex;

    return 1;
}

/*!
 * \brief Encode a Waypoint_t structure into a byte array
 *

 * \param data points to the byte array to add encoded data to
 * \param bytecount points to the starting location in the byte array, and will be incremented by the number of encoded bytes.
 * \param user is the data to encode in the byte array
 */
void encodeWaypoint_t(uint8_t* data, int* bytecount, const Waypoint_t* user)
{
    int byteindex = *bytecount;

    float32ToBeBytes((float)user->lat, data, &byteindex);

    float32ToBeBytes((float)user->lng, data, &byteindex);

    uint16ToBeBytes((uint16_t)user->threshold, data, &byteindex);

    uint8ToBytes((uint8_t)user->type, data, &byteindex);

    encodeClueOptions_t(data, &byteindex, &user->options);

    *bytecount = byteindex;
}

/*!
 * \brief Decode a Waypoint_t structure from a byte array
 *

 * \param data points to the byte array to decoded data from
 * \param bytecount points to the starting location in the byte array, and will be incremented by the number of bytes decoded
 * \param user is the data to decode from the byte array
 * \return 1 if the data are decoded, else 0. If 0 is returned bytecount will not be updated.
 */
int decodeWaypoint_t(const uint8_t* data, int* bytecount, Waypoint_t* user)
{
    int byteindex = *bytecount;

    user->lat = float32FromBeBytes(data, &byteindex);

    user->lng = float32FromBeBytes(data, &byteindex);

    user->threshold = (uint16_t)uint16FromBeBytes(data, &byteindex);

    user->type = (ClueTypes)uint8FromBytes(data, &byteindex);

    if(decodeClueOptions_t(data, &byteindex, &user->options) == 0)
        return 0;

    *bytecount = byteindex;

    return 1;
}

// end of boxdefines.c
