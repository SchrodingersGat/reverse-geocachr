<style>
    body {
        text-align:justify;
        width: 1000px;
        background-color:#eee;
        margin-left: auto;
        margin-right: auto;
        font-family:Verdana;
        counter-reset: h1counter;    }

    table {
       border: 2px solid darkred;
       border-collapse: collapse;
       margin-bottom: 25px;
    }

    th, td {
       border: 1px solid green;
       font-family: Courier New, monospace;
    }

    td{ padding: 2px; }
    h1, h2, h3, h4, h5 { font-family: Arial; }
    h1 { font-size:120%; margin-bottom: 25px;}
    h2 { font-size:110%; margin-bottom: 15px; }
    h3 { font-size:100%; margin-bottom: 10px;}
    h4, li { font-size:100%; }
    caption{ font-family:Verdana; }

    hr{
        color: black;
        background-color: dimgray;
        height: 1px;
        margin-bottom:25px;
        margin-top:25px;
    }

    code, pre, .codelike {
        font-family: Courier New, monospace;
        font-size: 100%;
        color: darkblue;
    }
    h1:before {
      content: counter(h1counter) "\00a0 ";
      counter-increment: h1counter;
      counter-reset: h2counter;
    }
    h1 {
      counter-reset: h2counter;
    }
    h2:before {
      content: counter(h1counter) "." counter(h2counter) "\00a0 ";
      counter-increment: h2counter;
      counter-reset: h3counter;
    }
    h3:before {
      content: counter(h1counter) "." counter(h2counter) "." counter(h3counter) "\00a0 ";
      counter-increment: h3counter;
    }</style>

# ReverseGeocache Protocol

Reverse Geocache USB message protocol

 Protocol version is 1.0.0.a.

 Protocol API is 1.

----------------------------

## Packet enumeration

USB Packet types

[<a name="Packet"></a>Packet enumeration]
| Name                                                      | Value | Description                             |
| --------------------------------------------------------- | :---: | --------------------------------------- |
| [`MSG_RESET_INTO_BOOTLOADER`](#MSG_RESET_INTO_BOOTLOADER) | 10    | Enter USB bootloader mode               |
| [`MSG_ENABLE_DEBUG_MODE`](#MSG_ENABLE_DEBUG_MODE)         | 11    | Enable extra debugging information      |
| [`MSG_SYSTEM_STATUS`](#MSG_SYSTEM_STATUS)                 | 160   | System status information               |
| [`MSG_SYSTEM_SETTINGS`](#MSG_SYSTEM_SETTINGS)             | 161   | System configuration information        |
| [`MSG_SYSTEM_VERSION`](#MSG_SYSTEM_VERSION)               | 162   | System version information              |
| [`MSG_CLUE_INFO`](#MSG_CLUE_INFO)                         | 176   | Clue information                        |
| [`MSG_CLUE_LINE`](#MSG_CLUE_LINE)                         | 192   | Single line of text for a given clue    |
| [`MSG_UNLOCK`](#MSG_UNLOCK)                               | 208   | Unlock the box                          |
| [`MSG_LOCK`](#MSG_LOCK)                                   | 209   | Lock the box                            |
| [`MSG_UNLOCK_SETTINGS`](#MSG_UNLOCK_SETTINGS)             | 213   | Unlock settings with password           |
| [`MSG_LOCK_SETTINGS`](#MSG_LOCK_SETTINGS)                 | 214   | Lock settings with password             |
| [`MSG_NEXT_CLUE`](#MSG_NEXT_CLUE)                         | 224   | Move to the next clue                   |
| [`MSG_PREV_CLUE`](#MSG_PREV_CLUE)                         | 225   | Move to the previous clue               |
| [`MSG_FIRST_CLUE`](#MSG_FIRST_CLUE)                       | 226   | Move to the first clue                  |
| [`MSG_LAST_CLUE`](#MSG_LAST_CLUE)                         | 227   | Move to the last clue                   |
| [`MSG_SET_CLUE_COUNT`](#MSG_SET_CLUE_COUNT)               | 240   | Set the total number of clues           |
| `MSG_INVALIDATE_CLUES`                                    | 241   | Mark clues as invalid (before download) |
| [`MSG_VALIDATE_CLUES`](#MSG_VALIDATE_CLUES)               | 242   | Mark clues as valid (after download)    |



## ClueTypes enumeration

[<a name="ClueTypes"></a>ClueTypes enumeration]
| Name                 | Value | Description                                     |
| -------------------- | :---: | ----------------------------------------------- |
| `CLUE_NO_HINT`       | 0     | No extra hint                                   |
| `CLUE_SHOW_DISTANCE` | 1     | Show distance to location                       |
| `CLUE_SHOW_LOCATION` | 2     | Show coordinates of location                    |
| `CLUE_WARMER_COOLER` | 3     | Show warmer / cooler (than previous try)        |
| `CLUE_SHOW_HEADING`  | 4     | Show heading to location in degrees             |
| `CLUE_SHOW_CARDINAL` | 5     | Show heading to location in cardinal directions |
| `NUM_CLUE_TYPES`     | 6     | Number of clue types (not a clue type itself)   |



## <a name="MSG_RESET_INTO_BOOTLOADER"></a>Reset packet

- packet identifier: `MSG_RESET_INTO_BOOTLOADER` : 10
- data length: 0


## <a name="MSG_UNLOCK"></a>Unlock packet

- packet identifier: `MSG_UNLOCK` : 208
- data length: 0


## <a name="MSG_LOCK"></a>Lock packet

- packet identifier: `MSG_LOCK` : 209
- data length: 0


## <a name="MSG_UNLOCK_SETTINGS"></a>UnlockSettings packet

- packet identifier: `MSG_UNLOCK_SETTINGS` : 213
- minimum data length: 1
- maximum data length: 32


[UnlockSettings packet bytes]
| Bytes  | Name       | [Enc](#Enc)                           | Repeat | Description |
| ------ | ---------- | :-----------------------------------: | :----: | ----------- |
| 0...31 | 1)password | Zero-terminated string up to 32 bytes         ||             |


## <a name="MSG_LOCK_SETTINGS"></a>LockSettings packet

- packet identifier: `MSG_LOCK_SETTINGS` : 214
- minimum data length: 1
- maximum data length: 32


[LockSettings packet bytes]
| Bytes  | Name       | [Enc](#Enc)                           | Repeat | Description |
| ------ | ---------- | :-----------------------------------: | :----: | ----------- |
| 0...31 | 1)password | Zero-terminated string up to 32 bytes         ||             |


## <a name="MSG_NEXT_CLUE"></a>NextClue packet

- packet identifier: `MSG_NEXT_CLUE` : 224
- data length: 0


## <a name="MSG_PREV_CLUE"></a>PrevClue packet

- packet identifier: `MSG_PREV_CLUE` : 225
- data length: 0


## <a name="MSG_FIRST_CLUE"></a>FirstClue packet

- packet identifier: `MSG_FIRST_CLUE` : 226
- data length: 0


## <a name="MSG_LAST_CLUE"></a>LastClue packet

- packet identifier: `MSG_LAST_CLUE` : 227
- data length: 0


## <a name="MSG_ENABLE_DEBUG_MODE"></a>EnableDebug packet

- packet identifier: `MSG_ENABLE_DEBUG_MODE` : 11
- data length: 1


[EnableDebug packet bytes]
| Bytes | Name      | [Enc](#Enc) | Repeat | Description                  |
| ----- | --------- | :---------: | :----: | ---------------------------- |
| 0     | 1)debugOn | U8          | 1      | Turn debug mode on (or off). |


## <a name="MSG_SET_CLUE_COUNT"></a>SetClueCount packet

- packet identifier: `MSG_SET_CLUE_COUNT` : 240
- data length: 1


[SetClueCount packet bytes]
| Bytes | Name        | [Enc](#Enc) | Repeat | Description |
| ----- | ----------- | :---------: | :----: | ----------- |
| 0     | 1)clueCount | U8          | 1      |             |


## <a name="MSG_VALIDATE_CLUES"></a>ValidateClues packet

- packet identifier: `MSG_VALIDATE_CLUES` : 242
- data length: 0


## <a name="MSG_VALIDATE_CLUES"></a>InvalidateClues packet

- packet identifier: `MSG_VALIDATE_CLUES` : 242
- data length: 0


## <a name="MSG_SYSTEM_STATUS"></a>BoxStatus packet

- packet identifier: `MSG_SYSTEM_STATUS` : 160
- data length: 4


[BoxStatus packet bytes]
| Bytes     | Name                | [Enc](#Enc) | Repeat | Description                          |
| --------- | ------------------- | :---------: | :----: | ------------------------------------ |
| 0:7       | 1)locked            | B1          | 1      |                                      |
| 0:6       | 2)passwordProtected | B1          | 1      | Box is protected with password.      |
| 0:5       | 3)gpsConnection     | B1          | 1      | 1 = GPS unit detected.               |
| 0:4...0:3 | 4)gpsStatus         | B2          | 1      | GPS Status.                          |
| 0:2       | 5)charging          | B1          | 1      | Battery charging status.             |
| 0:1       | 6)debug             | B1          | 1      |                                      |
| 1         | 7)charge            | U8          | 1      | Battery charge estimate, 0% to 100%. |
| 2         | 8)currentClue       | U8          | 1      | Index of current clue.               |
| 3         | 9)totalClues        | U8          | 1      | Total clue count.                    |


## <a name="MSG_SYSTEM_STATUS"></a>RequestBoxStatus packet

- packet identifier: `MSG_SYSTEM_STATUS` : 160
- data length: 0


## <a name="MSG_SYSTEM_SETTINGS"></a>BoxSettings packet

- packet identifier: `MSG_SYSTEM_SETTINGS` : 161
- data length: 4


[BoxSettings packet bytes]
| Bytes | Name          | [Enc](#Enc) | Repeat | Description                      |
| ----- | ------------- | :---------: | :----: | -------------------------------- |
| 0...1 | 1)pwmLocked   | U16         | 1      | PWM value for locked position.   |
| 2...3 | 2)pwmUnlocked | U16         | 1      | PWM value for unlocked position. |


## <a name="MSG_SYSTEM_SETTINGS"></a>RequestBoxSettings packet

- packet identifier: `MSG_SYSTEM_SETTINGS` : 161
- data length: 0


## <a name="MSG_SYSTEM_VERSION"></a>BoxVersion packet

- packet identifier: `MSG_SYSTEM_VERSION` : 162
- data length: 5


[BoxVersion packet bytes]
| Bytes | Name           | [Enc](#Enc) | Repeat | Description              |
| ----- | -------------- | :---------: | :----: | ------------------------ |
| 0...1 | 1)serialNumber | U16         | 1      | Box serial number.       |
| 2     | 2)versionMajor | U8          | 1      | Firmware version, major. |
| 3     | 3)versionMinor | U8          | 1      | Firmware version, minor. |
| 4     | 4)pcbRevision  | U8          | 1      | PCB revision.            |


## <a name="MSG_SYSTEM_VERSION"></a>RequestBoxVersion packet

- packet identifier: `MSG_SYSTEM_VERSION` : 162
- data length: 0


## <a name="MSG_CLUE_INFO"></a>ClueInfo packet

- packet identifier: `MSG_CLUE_INFO` : 176
- data length: 13


[ClueInfo packet bytes]
| Bytes  | Name             | [Enc](#Enc) | Repeat | Description                     |
| ------ | ---------------- | :---------: | :----: | ------------------------------- |
| 0      | 1)clueNumber     | U8          | 1      |                                 |
| 1...12 | 2)clueInfo                    || 1      |                                 |
| 1...4  | 2.1)lat          | F32         | 1      | Location latitude.              |
| 5...8  | 2.2)lng          | F32         | 1      | Location longitude.             |
| 9...10 | 2.3)threshold    | U16         | 1      | Distance threshold (m).         |
| 11     | 2.4)type         | U8          | 1      | Clue type.                      |
| 12     | 2.5)options                   || 1      | Extra clue options              |
| 12:7   | 2.5.1)centerText | B1          | 1      | Text is centered on the screen. |


## <a name="MSG_CLUE_INFO"></a>RequestClueInfo packet

- packet identifier: `MSG_CLUE_INFO` : 176
- data length: 1


[RequestClueInfo packet bytes]
| Bytes | Name         | [Enc](#Enc) | Repeat | Description |
| ----- | ------------ | :---------: | :----: | ----------- |
| 0     | 1)clueNumber | U8          | 1      |             |


## <a name="MSG_CLUE_LINE"></a>ClueLine packet

- packet identifier: `MSG_CLUE_LINE` : 192
- minimum data length: 3
- maximum data length: 42


[ClueLine packet bytes]
| Bytes  | Name         | [Enc](#Enc)                           | Repeat | Description    |
| ------ | ------------ | :-----------------------------------: | :----: | -------------- |
| 0      | 1)clueNumber | U8                                    | 1      | Index of clue. |
| 1      | 2)lineNumber | U8                                    | 1      | Line number.   |
| 2...41 | 3)lineText   | Zero-terminated string up to 40 bytes         || Line data.     |


## <a name="MSG_CLUE_LINE"></a>RequestClueLine packet

- packet identifier: `MSG_CLUE_LINE` : 192
- data length: 2


[RequestClueLine packet bytes]
| Bytes | Name         | [Enc](#Enc) | Repeat | Description |
| ----- | ------------ | :---------: | :----: | ----------- |
| 0     | 1)clueNumber | U8          | 1      |             |
| 1     | 2)lineNumber | U8          | 1      |             |


----------------------------

# About this ICD

This is the interface control document for data *on the wire*, not data in memory. This document was automatically generated by the [ProtoGen software](https://github.com/billvaglienti/ProtoGen), version 2.4.b. ProtoGen also generates C source code for doing most of the work of encoding data from memory to the wire, and vice versa.

## Encodings

Data for this protocol are sent in BIG endian format. Any field larger than one byte is sent with the most signficant byte first, and the least significant byte last.

Data can be encoded as unsigned integers, signed integers (two's complement), bitfields, and floating point.

| <a name="Enc"></a>Encoding | Interpretation                        | Notes                                                                       |
| :--------------------------: | ------------------------------------- | --------------------------------------------------------------------------- |
| UX                           | Unsigned integer X bits long          | X must be: 8, 16, 24, 32, 40, 48, 56, or 64                                 |
| IX                           | Signed integer X bits long            | X must be: 8, 16, 24, 32, 40, 48, 56, or 64                                 |
| BX                           | Unsigned integer bitfield X bits long | X must be greater than 0 and less than 32                                   |
| F16:X                        | 16 bit float with X significand bits  | 1 sign bit : 15-X exponent bits : X significant bits with implied leading 1 |
| F24:X                        | 24 bit float with X significand bits  | 1 sign bit : 23-X exponent bits : X significant bits with implied leading 1 |
| F32                          | 32 bit float (IEEE-754)               | 1 sign bit : 8 exponent bits : 23 significant bits with implied leading 1   |
| F64                          | 64 bit float (IEEE-754)               | 1 sign bit : 11 exponent bits : 52 significant bits with implied leading 1  |

## Size of fields
The encoding tables give the bytes for each field as X...Y; where X is the first byte (counting from 0) and Y is the last byte. For example a 4 byte field at the beginning of a packet will give 0...3. If the field is 1 byte long then only the starting byte is given. Bitfields are more complex, they are displayed as Byte:Bit. A 3-bit bitfield at the beginning of a packet will give 0:7...0:5, indicating that the bitfield uses bits 7, 6, and 5 of byte 0. Note that the most signficant bit of a byte is 7, and the least signficant bit is 0. If the bitfield is 1 bit long then only the starting bit is given.

The byte count in the encoding tables are based on the maximum length of the field(s). If a field is variable length then the actual byte location of the data may be different depending on the value of the variable field. If the field is a variable length character string this will be indicated in the encoding column of the table. If the field is a variable length array this will be indicated in the repeat column of the encoding table. If the field depends on the non-zero value of another field this will be indicated in the description column of the table.

