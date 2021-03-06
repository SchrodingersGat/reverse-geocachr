// scaleddecode.c was generated by ProtoGen version 2.4.b

#include "scaleddecode.h"
#include "fielddecode.h"


/*!
 * Inverse scale the bitfield base integer type to a float32
 * \param value is the integer number to inverse scale
 * \param min is the minimum value that can be represented.
 * \param invscaler is multiplied by the integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the scaling function.
 * \return the correctly scaled decoded value. return = min + value*invscaler.
 */
float float32ScaledFromBitfield(unsigned int value, float min, float invscaler)
{
    return (float)(min + invscaler*value);
}


/*!
 * Compute a float scaled from 4 unsigned bytes in big endian order.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 4 when this function is complete.
 * \param min is the minimum value that can be decoded.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = min + encoded*invscaler.
 */
float float32ScaledFrom4UnsignedBeBytes(const uint8_t* bytes, int* index, float min, float invscaler)
{
    return (float)(min + invscaler*uint32FromBeBytes(bytes, index));
}


/*!
 * Compute a float scaled from 4 unsigned bytes in little endian order.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 4 when this function is complete.
 * \param min is the minimum value that can be decoded.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = min + encoded*invscaler.
 */
float float32ScaledFrom4UnsignedLeBytes(const uint8_t* bytes, int* index, float min, float invscaler)
{
    return (float)(min + invscaler*uint32FromLeBytes(bytes, index));
}


/*!
 * Compute a float scaled from 4 signed bytes in big endian order.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 4 when this function is complete.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = encoded*invscaler.
 */
float float32ScaledFrom4SignedBeBytes(const uint8_t* bytes, int* index, float invscaler)
{
    return (float)(invscaler*int32FromBeBytes(bytes, index));
}


/*!
 * Compute a float scaled from 4 signed bytes in little endian order.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 4 when this function is complete.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = encoded*invscaler.
 */
float float32ScaledFrom4SignedLeBytes(const uint8_t* bytes, int* index, float invscaler)
{
    return (float)(invscaler*int32FromLeBytes(bytes, index));
}


/*!
 * Compute a float scaled from 3 unsigned bytes in big endian order.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 3 when this function is complete.
 * \param min is the minimum value that can be decoded.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = min + encoded*invscaler.
 */
float float32ScaledFrom3UnsignedBeBytes(const uint8_t* bytes, int* index, float min, float invscaler)
{
    return (float)(min + invscaler*uint24FromBeBytes(bytes, index));
}


/*!
 * Compute a float scaled from 3 unsigned bytes in little endian order.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 3 when this function is complete.
 * \param min is the minimum value that can be decoded.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = min + encoded*invscaler.
 */
float float32ScaledFrom3UnsignedLeBytes(const uint8_t* bytes, int* index, float min, float invscaler)
{
    return (float)(min + invscaler*uint24FromLeBytes(bytes, index));
}


/*!
 * Compute a float scaled from 3 signed bytes in big endian order.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 3 when this function is complete.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = encoded*invscaler.
 */
float float32ScaledFrom3SignedBeBytes(const uint8_t* bytes, int* index, float invscaler)
{
    return (float)(invscaler*int24FromBeBytes(bytes, index));
}


/*!
 * Compute a float scaled from 3 signed bytes in little endian order.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 3 when this function is complete.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = encoded*invscaler.
 */
float float32ScaledFrom3SignedLeBytes(const uint8_t* bytes, int* index, float invscaler)
{
    return (float)(invscaler*int24FromLeBytes(bytes, index));
}


/*!
 * Compute a float scaled from 2 unsigned bytes in big endian order.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 2 when this function is complete.
 * \param min is the minimum value that can be decoded.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = min + encoded*invscaler.
 */
float float32ScaledFrom2UnsignedBeBytes(const uint8_t* bytes, int* index, float min, float invscaler)
{
    return (float)(min + invscaler*uint16FromBeBytes(bytes, index));
}


/*!
 * Compute a float scaled from 2 unsigned bytes in little endian order.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 2 when this function is complete.
 * \param min is the minimum value that can be decoded.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = min + encoded*invscaler.
 */
float float32ScaledFrom2UnsignedLeBytes(const uint8_t* bytes, int* index, float min, float invscaler)
{
    return (float)(min + invscaler*uint16FromLeBytes(bytes, index));
}


/*!
 * Compute a float scaled from 2 signed bytes in big endian order.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 2 when this function is complete.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = encoded*invscaler.
 */
float float32ScaledFrom2SignedBeBytes(const uint8_t* bytes, int* index, float invscaler)
{
    return (float)(invscaler*int16FromBeBytes(bytes, index));
}


/*!
 * Compute a float scaled from 2 signed bytes in little endian order.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 2 when this function is complete.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = encoded*invscaler.
 */
float float32ScaledFrom2SignedLeBytes(const uint8_t* bytes, int* index, float invscaler)
{
    return (float)(invscaler*int16FromLeBytes(bytes, index));
}


/*!
 * Compute a float scaled from 1 unsigned byte.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 1 when this function is complete.
 * \param min is the minimum value that can be decoded.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = min + encoded*invscaler.
 */
float float32ScaledFrom1UnsignedBytes(const uint8_t* bytes, int* index, float min, float invscaler)
{
    return (float)(min + invscaler*uint8FromBytes(bytes, index));
}


/*!
 * Compute a float scaled from 1 signed byte.
 * \param bytes is a pointer to the byte stream to decode.
 * \param index gives the location of the first byte in the byte stream, and
 *        will be incremented by 1 when this function is complete.
 * \param invscaler is multiplied by the encoded integer to create the return value.
 *        invscaler should be the inverse of the scaler given to the encode function.
 * \return the correctly scaled decoded value. return = encoded*invscaler.
 */
float float32ScaledFrom1SignedBytes(const uint8_t* bytes, int* index, float invscaler)
{
    return (float)(invscaler*int8FromBytes(bytes, index));
}


// end of scaleddecode.c
