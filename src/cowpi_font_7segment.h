/**************************************************************************//**
 *
 * @file cowpi_font_7segment.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Provides a font to display approximations of printable ASCII
 *      characters on 7-segment displays.
 *
 * The mapping of bits to segment lines is:
 * ```
 *  --A--
 * |     |
 * F     B
 * |     |              bit      7 6 5 4 3 2 1 0
 *  --G--           segment     DP A B C D E F G
 * |     |
 * E     C
 * |     |
 *  --D--   (DP)
 * ```
 * If your display follows the same mapping, you can use the functions' outputs
 * directly. If the endianness of segments A-G are the same but your decimal
 * point is bit 0, then you can left-shift the functions' outputs by 1 and only
 * certain punctuation characters will be improperly displayed. If the mapping
 * is any further off, then you will likely not be able to use these functions.
 *
 ******************************************************************************/

/* CowPi (c) 2021-22 Christopher A. Bohn
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *     http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef COWPI_FONT_7SEGMENT_H
#define COWPI_FONT_7SEGMENT_H

#include <stdint.h>
#include <avr/pgmspace.h>

/** @addtogroup font
 *  @{
 */

const uint8_t cowpi_font_7segment[0x80] PROGMEM = {
//      00 nul   01 soh   02 stx   03 etx   04 eot   05 enq   06 ack   07 bel   08 bs    09 ht    0a nl    0b vt    0c np    0d cr    0e so    0f si
        0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x77, 0x1F, 0x0D, 0x3D, 0x4F, 0x47,
//      10 dle   11 dc1   12 dc2   13 dc3   14 dc4   15 nak   16 syn   17 etb   18 can   19 em    1a sub   1b esc   1c fs    1d gs    1e rs    1f us
        0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
//      20 sp    21  !    22  "    23  #    24  $    25  %    26  &    27  '    28  (    29  )    2a  *    2b  +    2c  ,    2d  -    2e  .    2f  /
        0x00, 0xA0, 0x22, 0x49, 0x00, 0x5A, 0x4A, 0x02, 0x4A, 0x68, 0x2B, 0x07, 0x80, 0x01, 0x80, 0x25,
//      30  0    31  1    32  2    33  3    34  4    35  5    36  6    37  7    38  8    39  9    3a  :    3b  ;    3c  <    3d  =    3e  >    3f  ?
        0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B, 0x88, 0x88, 0x43, 0x41, 0x61, 0xE1,
//      40  @    41  A    42  B    43  C    44  D    45  E    46  F    47  G    48  H    49  I    4a  J    4b  K    4c  L    4d  M    4e  N    4f  O
        0x6F, 0x77, 0x1F, 0x0D, 0x3D, 0x4F, 0x47, 0x5E, 0x37, 0x04, 0x38, 0x2F, 0x0E, 0x57, 0x76, 0x1D,
//      50  P    51  Q    52  R    53  S    54  T    55  U    56  V    57  W    58  X    59  Y    5a  Z    5b  [    5c  \    5d  ]    5e  ^    5f  _
        0x67, 0x73, 0x05, 0x5B, 0x0F, 0x3E, 0x27, 0x3F, 0x55, 0x3B, 0x6D, 0x4E, 0x13, 0x78, 0x62, 0x08,
//      60  `    61  a    62  b    63  c    64  d    65  e    66  f    67  g    68  h    69  i    6a  j    6b  k    6c  l    6d  m    6e  n    6f  o
        0x20, 0x77, 0x1F, 0x0D, 0x3D, 0x4F, 0x47, 0x5E, 0x37, 0x04, 0x38, 0x2F, 0x0E, 0x57, 0x76, 0x1D,
//      70  p    71  q    72  r    73  s    74  t    75  u    76  v    77  w    78  x    79  y    7a  z    7b  {    7c  |    7d  }    7e  ~    7f del
        0x67, 0x73, 0x05, 0x5B, 0x0F, 0x3E, 0x27, 0x3F, 0x55, 0x3B, 0x6D, 0x4C, 0x06, 0x58, 0x40, 0xFF
};

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Provides the 7-segment bit vector for an ASCII character or for a
 *      hexadecimal numeral.
 *
 * For hexadecimal numerals 0x0-0xF, returns a bit vector to display that
 * numeral on a 7-segment display. For the printable ASCII characters 0x20-0x7E,
 * returns a bit vector to display an approximation of that character on a
 * 7-segment display. Values in the range 0x10-0x1F, and 0x7F (DEL) return 0xFF,
 * which will illuminate all segments.
 *
 * The bit vector is guaranteed to work for a 7-segment display whose segments
 * are mapped to bits in the manner specified in the MAX7219/MAX7221 datasheet
 * (MSB DP-A-B-C-D-E-F-G LSB).
 *
 * @addtogroup font
 *
 * @param c the ASCII character whose 7-segment bit vector is to be provided
 * @return  a 7-segment bit vector
 */
uint8_t cowpi_font_ascii_to_7segment(char c);

/**
 * @brief Provides an array of 7-segment bit vectors for an ASCII character
 *      string.
 *
 * The source string, `s`, is assumed to be NUL-terminated.
 *
 * The `destination` array is assumed to point to a block of memory with
 * `strlen(s)` bytes allocated; that is, it must have enough space to hold
 * the array of bit vectors.
 *
 * @note The array of bit vectors will *not* be NUL-terminated.
 *
 * @addtogroup font
 *
 * @param destination   an empty array of sufficient size to hold the bit
 *      vectors
 * @param s             the string to be converted into 7-segment bit vectors
 * @return              `destination`, with the requested bit vectors
 */
uint8_t *cowpi_font_string_to_7segment(uint8_t *destination, const char *s);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_FONT_7SEGMENT_H
