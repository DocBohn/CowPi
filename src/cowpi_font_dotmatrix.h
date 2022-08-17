/**************************************************************************//**
 *
 * @file cowpi_font_dotmatrix.h
 *
 * @author Christopher A. Bohn
 *
 * @brief Provides a font to display printable ASCII characters on dot-matrix
 *      displays.
 *
 * All characters are guaranteed to occupy a rectangle no greater than 8 rows
 * by 5 columns.
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

#ifndef COWPI_FONT_DOTMATRIX_H
#define COWPI_FONT_DOTMATRIX_H

#include <stdint.h>
#include <avr/pgmspace.h>

/** @addtogroup font
 *  @{
 */

const uint8_t cowpi_font_dotmatrix_fuzz[8]         PROGMEM = {0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A, 0x15, 0x0A};

const uint8_t cowpi_font_dotmatrix_space[8]        PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t cowpi_font_dotmatrix_bang[8]         PROGMEM = {0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, 0x00};
const uint8_t cowpi_font_dotmatrix_doublequote[8]  PROGMEM = {0x05, 0x05, 0x05, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t cowpi_font_dotmatrix_octothorpe[8]   PROGMEM = {0x0A, 0x0A, 0x1F, 0x0A, 0x1F, 0x0A, 0x0A, 0x00};
const uint8_t cowpi_font_dotmatrix_dollar[8]       PROGMEM = {0x04, 0x0F, 0x14, 0x0E, 0x05, 0x1E, 0x04, 0x00};
const uint8_t cowpi_font_dotmatrix_percent[8]      PROGMEM = {0x18, 0x19, 0x02, 0x04, 0x08, 0x13, 0x03, 0x00};
const uint8_t cowpi_font_dotmatrix_ampersand[8]    PROGMEM = {0x0C, 0x12, 0x14, 0x08, 0x15, 0x12, 0x0D, 0x00};
const uint8_t cowpi_font_dotmatrix_apostrophe[8]   PROGMEM = {0x03, 0x01, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t cowpi_font_dotmatrix_leftparen[8]    PROGMEM = {0x01, 0x02, 0x04, 0x04, 0x04, 0x02, 0x01, 0x00};
const uint8_t cowpi_font_dotmatrix_rightparen[8]   PROGMEM = {0x04, 0x02, 0x01, 0x01, 0x01, 0x02, 0x04, 0x00};
const uint8_t cowpi_font_dotmatrix_asterisk[8]     PROGMEM = {0x00, 0x04, 0x15, 0x0E, 0x15, 0x04, 0x00, 0x00};
const uint8_t cowpi_font_dotmatrix_plus[8]         PROGMEM = {0x00, 0x04, 0x04, 0x1F, 0x04, 0x04, 0x00, 0x00};
const uint8_t cowpi_font_dotmatrix_comma[8]        PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x01, 0x02};
const uint8_t cowpi_font_dotmatrix_dash[8]         PROGMEM = {0x00, 0x00, 0x00, 0x1F, 0x00, 0x00, 0x00, 0x00};
const uint8_t cowpi_font_dotmatrix_period[8]       PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x03, 0x00};
const uint8_t cowpi_font_dotmatrix_slash[8]        PROGMEM = {0x01, 0x01, 0x02, 0x04, 0x08, 0x10, 0x10, 0x00};

const uint8_t cowpi_font_dotmatrix_zero[8]         PROGMEM = {0x0E, 0x11, 0x13, 0x15, 0x19, 0x11, 0x0E, 0x00};
const uint8_t cowpi_font_dotmatrix_one[8]          PROGMEM = {0x02, 0x06, 0x02, 0x02, 0x02, 0x02, 0x07, 0x00};
const uint8_t cowpi_font_dotmatrix_two[8]          PROGMEM = {0x0E, 0x11, 0x01, 0x02, 0x04, 0x08, 0x1F, 0x00};
const uint8_t cowpi_font_dotmatrix_three[8]        PROGMEM = {0x1F, 0x02, 0x04, 0x02, 0x01, 0x11, 0x0E, 0x00};
const uint8_t cowpi_font_dotmatrix_four[8]         PROGMEM = {0x02, 0x06, 0x0A, 0x12, 0x1F, 0x02, 0x02, 0x00};
const uint8_t cowpi_font_dotmatrix_five[8]         PROGMEM = {0x1F, 0x10, 0x10, 0x1E, 0x01, 0x11, 0x0E, 0x00};
const uint8_t cowpi_font_dotmatrix_six[8]          PROGMEM = {0x06, 0x08, 0x10, 0x1E, 0x11, 0x11, 0x0E, 0x00};
const uint8_t cowpi_font_dotmatrix_seven[8]        PROGMEM = {0x1F, 0x11, 0x01, 0x02, 0x04, 0x04, 0x04, 0x00};
const uint8_t cowpi_font_dotmatrix_eight[8]        PROGMEM = {0x0E, 0x11, 0x11, 0x0E, 0x11, 0x11, 0x0E, 0x00};
const uint8_t cowpi_font_dotmatrix_nine[8]         PROGMEM = {0x0E, 0x11, 0x11, 0x0F, 0x01, 0x02, 0x0C, 0x00};
const uint8_t cowpi_font_dotmatrix_colon[8]        PROGMEM = {0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x03, 0x00};
const uint8_t cowpi_font_dotmatrix_semicolon[8]    PROGMEM = {0x00, 0x03, 0x03, 0x00, 0x00, 0x03, 0x01, 0x02};
const uint8_t cowpi_font_dotmatrix_lessthan[8]     PROGMEM = {0x01, 0x02, 0x04, 0x08, 0x04, 0x02, 0x01, 0x00};
const uint8_t cowpi_font_dotmatrix_equals[8]       PROGMEM = {0x00, 0x00, 0x1F, 0x00, 0x1F, 0x00, 0x00, 0x00};
const uint8_t cowpi_font_dotmatrix_greaterthan[8]  PROGMEM = {0x08, 0x04, 0x02, 0x01, 0x02, 0x04, 0x08, 0x00};
const uint8_t cowpi_font_dotmatrix_question[8]     PROGMEM = {0x0E, 0x11, 0x01, 0x02, 0x04, 0x00, 0x04, 0x00};

const uint8_t cowpi_font_dotmatrix_at[8]           PROGMEM = {0x0E, 0x11, 0x15, 0x1B, 0x1F, 0x10, 0x0E, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_A[8]      PROGMEM = {0x0E, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_B[8]      PROGMEM = {0x1E, 0x11, 0x11, 0x1E, 0x11, 0x11, 0x1E, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_C[8]      PROGMEM = {0x0E, 0x11, 0x10, 0x10, 0x10, 0x11, 0x0E, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_D[8]      PROGMEM = {0x1C, 0x13, 0x11, 0x11, 0x11, 0x13, 0x1C, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_E[8]      PROGMEM = {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x1F, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_F[8]      PROGMEM = {0x1F, 0x10, 0x10, 0x1E, 0x10, 0x10, 0x10, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_G[8]      PROGMEM = {0x0E, 0x11, 0x10, 0x17, 0x11, 0x11, 0x0F, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_H[8]      PROGMEM = {0x11, 0x11, 0x11, 0x1F, 0x11, 0x11, 0x11, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_I[8]      PROGMEM = {0x07, 0x02, 0x02, 0x02, 0x02, 0x02, 0x07, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_J[8]      PROGMEM = {0x07, 0x02, 0x02, 0x02, 0x02, 0x12, 0x0C, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_K[8]      PROGMEM = {0x11, 0x12, 0x14, 0x18, 0x14, 0x12, 0x11, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_L[8]      PROGMEM = {0x10, 0x10, 0x10, 0x10, 0x10, 0x10, 0x1F, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_M[8]      PROGMEM = {0x11, 0x1B, 0x15, 0x15, 0x11, 0x11, 0x11, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_N[8]      PROGMEM = {0x11, 0x19, 0x19, 0x15, 0x13, 0x13, 0x11, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_O[8]      PROGMEM = {0x0E, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00};

const uint8_t cowpi_font_dotmatrix_upper_P[8]      PROGMEM = {0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10, 0x10, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_Q[8]      PROGMEM = {0x0E, 0x11, 0x11, 0x11, 0x15, 0x12, 0x0D, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_R[8]      PROGMEM = {0x1E, 0x11, 0x11, 0x1E, 0x14, 0x12, 0x11, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_S[8]      PROGMEM = {0x0E, 0x11, 0x10, 0x0E, 0x01, 0x11, 0x0E, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_T[8]      PROGMEM = {0x1F, 0x04, 0x04, 0x04, 0x04, 0x04, 0x04, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_U[8]      PROGMEM = {0x11, 0x11, 0x11, 0x11, 0x11, 0x11, 0x0E, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_V[8]      PROGMEM = {0x11, 0x11, 0x11, 0x0A, 0x0A, 0x0A, 0x04, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_W[8]      PROGMEM = {0x11, 0x11, 0x11, 0x15, 0x15, 0x0A, 0x0A, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_X[8]      PROGMEM = {0x11, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x11, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_Y[8]      PROGMEM = {0x11, 0x11, 0x0A, 0x0A, 0x04, 0x04, 0x04, 0x00};
const uint8_t cowpi_font_dotmatrix_upper_Z[8]      PROGMEM = {0x1F, 0x01, 0x02, 0x04, 0x08, 0x10, 0x1F, 0x00};
const uint8_t cowpi_font_dotmatrix_leftbracket[8]  PROGMEM = {0x07, 0x04, 0x04, 0x04, 0x04, 0x04, 0x07, 0x00};
const uint8_t cowpi_font_dotmatrix_backslash[8]    PROGMEM = {0x10, 0x10, 0x08, 0x04, 0x02, 0x01, 0x01, 0x00};
const uint8_t cowpi_font_dotmatrix_rightbracket[8] PROGMEM = {0x07, 0x01, 0x01, 0x01, 0x01, 0x01, 0x07, 0x00};
const uint8_t cowpi_font_dotmatrix_carat[8]        PROGMEM = {0x04, 0x0A, 0x11, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t cowpi_font_dotmatrix_underscore[8]   PROGMEM = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0x00};

const uint8_t cowpi_font_dotmatrix_backtick[8]     PROGMEM = {0x04, 0x02, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_a[8]      PROGMEM = {0x00, 0x00, 0x0E, 0x01, 0x0E, 0x11, 0x0E, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_b[8]      PROGMEM = {0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x1E, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_c[8]      PROGMEM = {0x00, 0x00, 0x0E, 0x10, 0x10, 0x11, 0x0E, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_d[8]      PROGMEM = {0x01, 0x01, 0x0D, 0x13, 0x11, 0x11, 0x0F, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_e[8]      PROGMEM = {0x00, 0x00, 0x0E, 0x11, 0x1F, 0x10, 0x0E, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_f[8]      PROGMEM = {0x06, 0x09, 0x08, 0x1C, 0x08, 0x08, 0x08, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_g[8]      PROGMEM = {0x00, 0x00, 0x0E, 0x11, 0x0F, 0x01, 0x11, 0x0E};
const uint8_t cowpi_font_dotmatrix_lower_h[8]      PROGMEM = {0x10, 0x10, 0x16, 0x19, 0x11, 0x11, 0x11, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_i[8]      PROGMEM = {0x00, 0x02, 0x00, 0x06, 0x02, 0x02, 0x07, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_j[8]      PROGMEM = {0x00, 0x02, 0x00, 0x06, 0x02, 0x02, 0x09, 0x06};
const uint8_t cowpi_font_dotmatrix_lower_k[8]      PROGMEM = {0x08, 0x08, 0x09, 0x0A, 0x0C, 0x0A, 0x09, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_l[8]      PROGMEM = {0x06, 0x02, 0x02, 0x02, 0x02, 0x02, 0x07, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_m[8]      PROGMEM = {0x00, 0x00, 0x1A, 0x15, 0x15, 0x15, 0x15, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_n[8]      PROGMEM = {0x00, 0x00, 0x16, 0x19, 0x11, 0x11, 0x11, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_o[8]      PROGMEM = {0x00, 0x00, 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00};

const uint8_t cowpi_font_dotmatrix_lower_p[8]      PROGMEM = {0x00, 0x00, 0x1E, 0x11, 0x11, 0x1E, 0x10, 0x10};
const uint8_t cowpi_font_dotmatrix_lower_q[8]      PROGMEM = {0x00, 0x00, 0x0F, 0x11, 0x11, 0x0F, 0x01, 0x01};
const uint8_t cowpi_font_dotmatrix_lower_r[8]      PROGMEM = {0x00, 0x00, 0x16, 0x19, 0x10, 0x10, 0x10, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_s[8]      PROGMEM = {0x00, 0x00, 0x0F, 0x10, 0x0E, 0x01, 0x1E, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_t[8]      PROGMEM = {0x00, 0x04, 0x0E, 0x04, 0x04, 0x04, 0x03, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_u[8]      PROGMEM = {0x00, 0x00, 0x11, 0x11, 0x11, 0x13, 0x0D, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_v[8]      PROGMEM = {0x00, 0x00, 0x11, 0x11, 0x0A, 0x0A, 0x04, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_w[8]      PROGMEM = {0x00, 0x00, 0x11, 0x11, 0x15, 0x15, 0x0A, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_x[8]      PROGMEM = {0x00, 0x00, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00};
const uint8_t cowpi_font_dotmatrix_lower_y[8]      PROGMEM = {0x00, 0x00, 0x11, 0x11, 0x09, 0x07, 0x01, 0x0E};
const uint8_t cowpi_font_dotmatrix_lower_z[8]      PROGMEM = {0x00, 0x00, 0x1F, 0x02, 0x04, 0x08, 0x1F, 0x00};
const uint8_t cowpi_font_dotmatrix_leftbrace[8]    PROGMEM = {0x01, 0x02, 0x02, 0x04, 0x02, 0x02, 0x01, 0x00};
const uint8_t cowpi_font_dotmatrix_pipe[8]         PROGMEM = {0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00};
const uint8_t cowpi_font_dotmatrix_rightbrace[8]   PROGMEM = {0x04, 0x02, 0x02, 0x01, 0x02, 0x02, 0x04, 0x00};
const uint8_t cowpi_font_dotmatrix_tilde[8]        PROGMEM = {0x00, 0x00, 0x0D, 0x12, 0x00, 0x00, 0x00, 0x00};

const int8_t cowpi_font_dotmatrix_widths[] PROGMEM = {
        5, 3, 5, 5, 5, 5, 5, 5,
        5, 5, 0, 0, 0, 0, 0, 0,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
        2, 1, 3, 5, 5, 5, 5, 2,
        3, 3, 5, 5, 2, 5, 2, 5,
        5, 3, 5, 5, 5, 5, 5, 5,
        5, 5, 2, 2, 4, 5, 4, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 3, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 5, 5, 5, 5, 5,
        5, 5, 5, 3, 5, 3, 5, 5,
        3, 5, 5, 5, 5, 5, 5, 5,
        5, 3, 4, 4, 3, 5, 5, 5,
        5, 5, 5, 5, 4, 5, 5, 5,
        5, 5, 5, 3, 1, 3, 5, 5
};

const uint8_t *const cowpi_font_dotmatrix[] PROGMEM = {
        cowpi_font_dotmatrix_zero,         cowpi_font_dotmatrix_one,          cowpi_font_dotmatrix_two,          cowpi_font_dotmatrix_three,        cowpi_font_dotmatrix_four,         cowpi_font_dotmatrix_five,         cowpi_font_dotmatrix_six,          cowpi_font_dotmatrix_seven,
        cowpi_font_dotmatrix_eight,        cowpi_font_dotmatrix_nine,         cowpi_font_dotmatrix_upper_A,      cowpi_font_dotmatrix_upper_B,      cowpi_font_dotmatrix_upper_C,      cowpi_font_dotmatrix_upper_D,      cowpi_font_dotmatrix_upper_E,      cowpi_font_dotmatrix_upper_F,
        cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,
        cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,         cowpi_font_dotmatrix_fuzz,
        cowpi_font_dotmatrix_space,        cowpi_font_dotmatrix_bang,         cowpi_font_dotmatrix_doublequote,  cowpi_font_dotmatrix_octothorpe,   cowpi_font_dotmatrix_dollar,       cowpi_font_dotmatrix_percent,      cowpi_font_dotmatrix_ampersand,    cowpi_font_dotmatrix_apostrophe,
        cowpi_font_dotmatrix_leftparen,    cowpi_font_dotmatrix_rightparen,   cowpi_font_dotmatrix_asterisk,     cowpi_font_dotmatrix_plus,         cowpi_font_dotmatrix_comma,        cowpi_font_dotmatrix_dash,         cowpi_font_dotmatrix_period,       cowpi_font_dotmatrix_slash,
        cowpi_font_dotmatrix_zero,         cowpi_font_dotmatrix_one,          cowpi_font_dotmatrix_two,          cowpi_font_dotmatrix_three,        cowpi_font_dotmatrix_four,         cowpi_font_dotmatrix_five,         cowpi_font_dotmatrix_six,          cowpi_font_dotmatrix_seven,
        cowpi_font_dotmatrix_eight,        cowpi_font_dotmatrix_nine,         cowpi_font_dotmatrix_colon,        cowpi_font_dotmatrix_semicolon,    cowpi_font_dotmatrix_lessthan,     cowpi_font_dotmatrix_equals,       cowpi_font_dotmatrix_greaterthan,  cowpi_font_dotmatrix_question,
        cowpi_font_dotmatrix_at,           cowpi_font_dotmatrix_upper_A,      cowpi_font_dotmatrix_upper_B,      cowpi_font_dotmatrix_upper_C,      cowpi_font_dotmatrix_upper_D,      cowpi_font_dotmatrix_upper_E,      cowpi_font_dotmatrix_upper_F,      cowpi_font_dotmatrix_upper_G,
        cowpi_font_dotmatrix_upper_H,      cowpi_font_dotmatrix_upper_I,      cowpi_font_dotmatrix_upper_J,      cowpi_font_dotmatrix_upper_K,      cowpi_font_dotmatrix_upper_L,      cowpi_font_dotmatrix_upper_M,      cowpi_font_dotmatrix_upper_N,      cowpi_font_dotmatrix_upper_O,
        cowpi_font_dotmatrix_upper_P,      cowpi_font_dotmatrix_upper_Q,      cowpi_font_dotmatrix_upper_R,      cowpi_font_dotmatrix_upper_S,      cowpi_font_dotmatrix_upper_T,      cowpi_font_dotmatrix_upper_U,      cowpi_font_dotmatrix_upper_V,      cowpi_font_dotmatrix_upper_W,
        cowpi_font_dotmatrix_upper_X,      cowpi_font_dotmatrix_upper_Y,      cowpi_font_dotmatrix_upper_Z,      cowpi_font_dotmatrix_leftbracket,  cowpi_font_dotmatrix_backslash,    cowpi_font_dotmatrix_rightbracket, cowpi_font_dotmatrix_carat,        cowpi_font_dotmatrix_underscore,
        cowpi_font_dotmatrix_backtick,     cowpi_font_dotmatrix_lower_a,      cowpi_font_dotmatrix_lower_b,      cowpi_font_dotmatrix_lower_c,      cowpi_font_dotmatrix_lower_d,      cowpi_font_dotmatrix_lower_e,      cowpi_font_dotmatrix_lower_f,      cowpi_font_dotmatrix_lower_g,
        cowpi_font_dotmatrix_lower_h,      cowpi_font_dotmatrix_lower_i,      cowpi_font_dotmatrix_lower_j,      cowpi_font_dotmatrix_lower_k,      cowpi_font_dotmatrix_lower_l,      cowpi_font_dotmatrix_lower_m,      cowpi_font_dotmatrix_lower_n,      cowpi_font_dotmatrix_lower_o,
        cowpi_font_dotmatrix_lower_p,      cowpi_font_dotmatrix_lower_q,      cowpi_font_dotmatrix_lower_r,      cowpi_font_dotmatrix_lower_s,      cowpi_font_dotmatrix_lower_t,      cowpi_font_dotmatrix_lower_u,      cowpi_font_dotmatrix_lower_v,      cowpi_font_dotmatrix_lower_w,
        cowpi_font_dotmatrix_lower_x,      cowpi_font_dotmatrix_lower_y,      cowpi_font_dotmatrix_lower_z,      cowpi_font_dotmatrix_leftbrace,    cowpi_font_dotmatrix_pipe,         cowpi_font_dotmatrix_rightbrace,   cowpi_font_dotmatrix_tilde,        cowpi_font_dotmatrix_fuzz
};

/** @} */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Provides the minimum number of columns needed to represent a character
 *      in the dot matrix font.
 *
 * @ingroup font
 *
 * @param   c the character whose width is to be determined
 * @return  the dot matrix width of the character
 */
int8_t cowpi_font_get_dotmatrix_width(char c);

/**
 * @brief Provides the dot matrix representation of an ASCII character with no
 *      blank columns to the right of the character.
 *
 * Each byte of the destination array stores one row of the character's dot
 * matrix representation, with element 0 being the top of the character. Each
 * bit position in an array element represents a column.
 *
 * The `destination` array is assumed to point to a block of memory with 8
 * bytes allocated; that is, it must have enough space to hold the character's
 * dot matrix representation.
 *
 * @sa cowpi_font_ascii_to_5wide_dotmatrix
 * @sa cowpi_font_ascii_to_8wide_dotmatrix
 *
 * @ingroup font
 *
 * @param destination   an empty 8-byte array
 * @param c             the ASCII character whose dot matrix representation is
 *      to be provided
 * @return              `destination`, with the requested dot matrix character
 */
uint8_t *cowpi_font_ascii_to_narrow_dotmatrix(uint8_t *destination, char c);

/**
 * @brief Provides the dot matrix representation of an ASCII character centered
 *      horizontally in the five columns used for a 5x8 dot matrix character
 *      (the five right-most columns of the 8x8 matrix).
 *
 * Each byte of the destination array stores one row of the character's dot
 * matrix representation, with element 0 being the top of the character.
 *
 * The `destination` array is assumed to point to a block of memory with 8
 * bytes allocated; that is, it must have enough space to hold the character's
 * dot matrix representation.
 *
 * @sa cowpi_font_ascii_to_narrow_dotmatrix
 * @sa cowpi_font_ascii_to_8wide_dotmatrix
 *
 * @ingroup font
 *
 * @param destination   an empty 8-byte array
 * @param c             the ASCII character whose dot matrix representation is
 *      to be provided
 * @return              `destination`, with the requested dot matrix character
 */
uint8_t *cowpi_font_ascii_to_5wide_dotmatrix(uint8_t *destination, char c);

/**
 * @brief Provides the dot matrix representation of an ASCII character centered
 *      horizontally in the eight columns of the 8x8 matrix.
 *
 * Each byte of the destination array stores one row of the character's dot
 * matrix representation, with element 0 being the top of the character.
 *
 * The `destination` array is assumed to point to a block of memory with 8
 * bytes allocated; that is, it must have enough space to hold the character's
 * dot matrix representation.
 *
 * @sa cowpi_font_ascii_to_narrow_dotmatrix
 * @sa cowpi_font_ascii_to_5wide_dotmatrix
 *
 * @ingroup font
 *
 * @param destination   an empty 8-byte array
 * @param c             the ASCII character whose dot matrix representation is
 *      to be provided
 * @return              `destination`, with the requested dot matrix character
 */
uint8_t *cowpi_font_ascii_to_8wide_dotmatrix(uint8_t *destination, char c);

/**
 * @brief Transposes an 8x8 dot matrix representation.
 *
 * After the transposition, each element of the `matrix` array represents a
 * column, and each bit position of an array element represents a row.
 *
 * This is an in-place transposition; that is, the original matrix is
 * overwritten.
 *
 * @ingroup font
 *
 * @param matrix    the dot matrix to be transposed
 * @return          `matrix` after the transposition
 */
uint8_t *cowpi_font_transpose_dotmatrix(uint8_t *matrix);

/**
 * @brief Provides a single dot matrix representation of an ASCII character
 *      string suitable for scrolling horizontally.
 *
 * Each byte of the destination array stores one column of the string's dot
 * matrix representation, with element 0 being the leftmost column of the first
 * character.
 *
 * The `destination` array is assumed to point to a block of memory with
 * sufficient space allocated to hold the full string's dot matrix
 * representation; `6 * strlen(s)` is guaranteed to be sufficient.
 *
 * @ingroup font
 *
 * @param destination   an empty array to hold the dot matrix representation
 * @param s             the ASCII string whose dot matrix representation is to
 *      be provided
 * @param kerned        indicates whether to use minimal space between
 *      characters or to use a fixed 5 columns per character
 * @return              the number of columns in the string's dot matrix
 *      representation
 */
int cowpi_font_string_to_horizontal_dotmatrix(uint8_t *destination, const char *s, bool kerned);

/**
 * @brief Provides a single dot matrix representation of an ASCII character
 *      string suitable for scrolling vertically.
 *
 * Each byte of the destination array stores one row of the string's dot matrix
 * representation, with element 0 being the top row of the first character.
 *
 * The `destination` array is assumed to point to a block of memory with
 * sufficient space allocated to hold the full string's dot matrix
 * representation; `9 * strlen(s)` is guaranteed to be sufficient.
 *
 * @ingroup font
 *
 * @param destination   an empty array to hold the dot matrix representation
 * @param s             the ASCII string whose dot matrix representation is to
 *      be provided
 * @param kerned        indicates whether to use minimal space between
 *      characters or to use a fixed 8 rows per character
 * @return              the number of rows in the string's dot matrix
 *      representation
 */
int cowpi_font_string_to_vertical_dotmatrix(uint8_t *destination, const char *s, bool kerned);

#ifdef __cplusplus
} // extern "C"
#endif

#endif //COWPI_FONT_DOTMATRIX_H
