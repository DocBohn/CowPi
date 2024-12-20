# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to
[Semantic Versioning](https://semver.org/spec/v2.0.0.html).

<!--
## [major.minor.patch] - yyyy-mm-dd
-->

<!--
- `Added` for new features.
- `Changed` for changes in existing functionality.
- `Deprecated` for soon-to-be removed features.
- `Removed` for now removed features.
- `Fixed` for any bug fixes.
- `Security` in case of vulnerabilities.
-->

<!--
## [TODO]
- Microcontroller-dependent code other than that for ATMega328P & RP2040
- Implementation that uses Raspberry Pi Pico SDK
- Implement `cowpi_register_pin_ISR()` for RP2040
- Wrap and document the [Ticker](https://os.mbed.com/docs/mbed-os/v6.16/apis/ticker.html) and [Timeout](https://os.mbed.com/docs/mbed-os/v6.16/apis/timeout.html) APIs
-->

## [0.8.2] - 2024-10-27

### Fixed

- Library manifests corrected

## [0.8.1] - 2024-10-27

### Fixed

- Replaced pinMode with cowpi_pin_mode from CowPi_stdio

## [0.8.0] - 2024-10-24

### Added

- Ported to [Arduino-Pico](https://arduino-pico.readthedocs.io/en/latest/index.html) core based on RPi Pico SDK
- Register/deregister ISRs for pin interrupts on Raspberry Pi Pico (uses mbed::InterruptIn)
- Configure periodic timers (AVR) or periodic virtual timers (MBED) and register periodic timer interrupts

### Changed

- Renamed constants to deconflict with other libraries

## [0.7.1] - 2024-03-08

### Fixed

- Static variables are initialized with constants and not with const variables

## [0.7.0] - 2024-03-03

### Added

- Pin mappings for Raspberry Pi Pico
- Memory-mapped I/O structures for RP2040
- Debouncing code for 32-bit inputs

### Removed

- `COWPI_IO_BASE`

## [0.6.1] - 2023-10-14

### Fixed

- Added Nyquist Rate check to debouncing code

## [0.6.0] - 2023-08-02

### Added

- Code to read chorded keypresses
  - This function should only be called when the keys are protected by diodes to prevent short-circuits!
- Code to support switch debouncing

### Changed

- `cowpi_setup` now uses CowPi_stdio library's configuration structures
- Default code to read keypresses can handle form factors other than Uno/Nano

### Deprecated

- `COWPI_IO_BASE`
  - Use absolute memory addresses instead of offsets from `COWPI_IO_BASE`

## [0.5.0] - 2023-07-06

### Added

- Option to register interrupt service routines for changes on any digital pin on Arduino Nano (uses pin change interrupts)

### Changed

- Migrated AVR `printf`/`scanf` code from CowPi library to CowPi_stdio library
- Migrated code for controlling MAX7219- and HD44780-based display modules migrated from CowPi library to CowPi_stdio library

## [0.4.1] - 2023-04-06

### Fixed

- Nested header files are not dependent on the order in which they are #include'd

## [0.4.0] - 2023-01-26

### Added

- LCD1602 default dialect for SPI

### Changed

- Renamed `right/left_switch_in_right/left_position()` functions to `right/left_switch_is_in_right/left_position()`
- Renamed `cowpi_io_base` to `COWPI_IO_BASE`

### Fixed

- Removed I2C false-error detection
  - Accept risk of failure to detect true error
- Symbol duplication when student code spans multiple files

## [0.3.0] - 2022-08-01

### Added

- Replaced single header file with library
  - Default implementations for reading inputs and writing outputs
    - Most are microcontroller-independent; I2C is still ATMega328P-only
  - Microcontroller-dependent code (*e.g.* memory-mapped I/O structures)
    isolated from microcontroller-independent code
  - Framework to allow polling I/O code and memory-mapped I/O code to be graded
    distinctly
- 7-segment and dot-matrix fonts
- Framework to control LCD1602 display module; students only need to write code
  to use SPI or I2C hardware
- Setup code to enable `printf`/`scanf` for AVR microcontrollers
- Example code
  - Replace test code in construction instructions with examples
  - Additional examples demonstrating library features

## [0.2.1] - 22-04-26

### Added

- Default implementations to scan keypad and to send data to display module

### Fixed

- Explicitly configures NAND input pins

## [0.2.0] - 22-04-01

### Added

- Setup code to configure I/O pins
- Setup code to configure MAX7219
- Macros to enable and disable SPI hardware, to leave external LED an output pin

### Changed

## [0.1.0] - 2021-11-02

### Added

- `cowpi.h`

  - Structures for accessing ATMega328P memory-mapped I/O registers
