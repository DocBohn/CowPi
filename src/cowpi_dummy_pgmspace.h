/**************************************************************************//**
 *
 * @file cowpi_dummy_pgmspace.h
 *
 * @author Christopher A. Bohn
 *
 * @brief This header defines dummy functions & macros to replace those in
 * avr/pgmspace.h for non-AVR architectures (or that don't need avr/pgmspace.h,
 * in the case of the ATMega4809).
 *
 * This header might not be needed, as it looks like Arduino has provided a
 * pgmspace.h header for some or all non-AVR architectures. When we extend the
 * library to the Raspberry Pi Pico SDK, we may need it, though.
 *
 ******************************************************************************/

#ifndef COWPI_DUMMY_PGMSPACE_H
#define COWPI_DUMMY_PGMSPACE_H

// One last protection against accidental misuse
#ifndef ARDUINO_ARCH_AVR

/** @cond */

#ifdef __cplusplus
extern "C" {
#endif

#define PROGMEM

inline char *strcpy_P(const char *destination, const char *source) __attribute__((__always_inline__));
inline char *strcpy_P(const char *destination, const char *source) {
    return source;
}

inline const char *PSTR(const char *s) __attribute__((__always_inline__));
inline const char *PSTR(const char *s) {
    return s;
}

inline uint8_t pgm_read_byte(const uint8_t *p) __attribute__((__always_inline__));
inline uint8_t pgm_read_byte(const uint8_t *p) {
    return *p;
}

inline uint8_t pgm_read_word(const uint8_t *p) __attribute__((__always_inline__));
inline uint8_t pgm_read_word(const uint8_t *p) {
    return *p;
}

#ifdef __cplusplus
}
#endif

/** @endcond */

#endif //ARDUINO_ARCH_AVR

#endif //COWPI_DUMMY_PGMSPACE_H
