// boxdefines.c was generated by ProtoGen version 2.4.b

#include "boxdefines.h"
#include "fielddecode.h"
#include "fieldencode.h"
#include "scaleddecode.h"
#include "scaledencode.h"

/*!
 * \brief Encode a ClueOptionBits_t structure into a byte array
 *

 * \param data points to the byte array to add encoded data to
 * \param bytecount points to the starting location in the byte array, and will be incremented by the number of encoded bytes.
 * \param user is the data to encode in the byte array
 */
void encodeClueOptionBits_t(uint8_t* data, int* bytecount, const ClueOptionBits_t* user)
{
    int byteindex = *bytecount;

    // Text is centered on the screen
    data[byteindex] = (uint8_t)user->centerText << 7;
    byteindex += 1; // close bit field

    *bytecount = byteindex;

}// encodeClueOptionBits_t

/*!
 * \brief Decode a ClueOptionBits_t structure from a byte array
 *

 * \param data points to the byte array to decoded data from
 * \param bytecount points to the starting location in the byte array, and will be incremented by the number of bytes decoded
 * \param user is the data to decode from the byte array
 * \return 1 if the data are decoded, else 0. If 0 is returned bytecount will not be updated.
 */
int decodeClueOptionBits_t(const uint8_t* data, int* bytecount, ClueOptionBits_t* user)
{
    int byteindex = *bytecount;

    // Text is centered on the screen
    user->centerText = (data[byteindex] >> 7);
    byteindex += 1; // close bit field

    *bytecount = byteindex;

    return 1;

}// decodeClueOptionBits_t

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

    // Location latitude
    float32ToBeBytes((float)user->lat, data, &byteindex);

    // Location longitude
    float32ToBeBytes((float)user->lng, data, &byteindex);

    // Distance threshold (m)
    uint16ToBeBytes((uint16_t)user->threshold, data, &byteindex);

    // Clue type
    uint8ToBytes((uint8_t)user->type, data, &byteindex);

    // Extra clue options
    encodeClueOptionBits_t(data, &byteindex, &user->options);

    *bytecount = byteindex;

}// encodeWaypoint_t

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

    // Location latitude
    user->lat = float32FromBeBytes(data, &byteindex);

    // Location longitude
    user->lng = float32FromBeBytes(data, &byteindex);

    // Distance threshold (m)
    user->threshold = (uint16_t)uint16FromBeBytes(data, &byteindex);

    // Clue type
    user->type = (uint8_t)uint8FromBytes(data, &byteindex);

    // Extra clue options
    if(decodeClueOptionBits_t(data, &byteindex, &user->options) == 0)
        return 0;

    *bytecount = byteindex;

    return 1;

}// decodeWaypoint_t

// end of boxdefines.c
