# CowPi Library

version 0.4

## What is the Cow Pi?

### The hardware

The Cow Pi is a simple circuit that consists of a microcontroller board, a
display module, a couple of LEDs, a couple of momentary buttons, a couple of
maintained switches, and a matrix keypad. We use it to teach memory-mapped I/O,
polling, and interrupts.

### The library

Initially we supported the memory-mapped I/O lab with a header file that
defined some `struct`s and named constants. Later we added some macros to reduce
complexity that didn't contribute to the learning objectives.

We decided to create a library for three reasons:
- It allows us to provide some additional bootstrapping for students: they'll
  be able to work on polling logic using some of the functions in the library
  and then later replace those with functions that use memory-mapped I/O. Or
  they can start with memory-mapped I/O and then move on to the polling logic.
  Before the library, students had no choice but to start with memory-mapped
  I/O.
- It allows us to replace parameterized macros with functions.
- We can use more complex display modules. Originally, the Cow Pi's display
  module was an 8-digit/7-segment display module. The Terasic Altera DE1 boards
  that we used to use had a 4-digit/7-segment display. Manipulating 7-segment
  displays is incredibly easy. To simplify the supply chain for our supplier,
  we're going to try using 2-row/16-column LCD display modules. Manipulating
  the LCD1602 display modules is not incredibly easy. With a library, we can let
  students focus on the memory-mapped I/O aspect and not on the details of
  controlling the display module.

## Why is it called the *Cow Pi*?

Because it's punny.

### No, I mean, *-Pi* is typically used as a suffix for circuits that use a Raspberry Pi instead of an Arduino.

Typically, yes, but *Cowduino* isn't very punny, is it?

Besides, there soon will be a version of the Cow Pi that makes use of the
Raspberry Pi Pico. That's why we said that the circuit has "a microcontroller
board" instead of "an Arduino Nano."

## Why did you design something new? Didn't you consider something manufactured?

We used to use the [Terasic Altera
DE1](https://www.terasic.com.tw/cgi-bin/page/archive.pl?No=83). Our computer
science students and software engineering students didn't reprogram the FPGA;
they simply used C and compiled their programs to run on the Nios II soft core
that came pre-programmed into the FPGA. When we decided it was time to stop
using the DE1s, our computer engineering students switched to the [Terasic
DE10-Lite](http://de10-lite.terasic.com/), but we decided that the cost was too
great for the features that our CS and SE students would use.

The problem we ran into with the various Arduino shields or Raspberry Pi hats is
that they either were unavailable in the quantity we needed, or would require
our students to solder them together -- and we have no expectations that our
CS and SE students are able to solder. We were pretty sure that they could put
together a circuit on a solderless breadboard, though.

We are, however, planning to have PCBs manufactured and assembled, assuming we
can keep the cost down.

## The Cow Pi uses nearly all of the pins on the Arduino Nano; that'll make it hard to do any other projects with it.

Yes, that's true. The Cow Pi is designed to support specific learning
objectives. If you want to do a different project, then disassemble the kit and
use the parts to build your project.

## Why don't you just use existing libraries like `LiquidCrystal` and `Wire`?

Because those libraries hide the details. Part of what we use the Cow Pi for is
teaching memory-mapped I/O.

## Have you considered making the CowPi library work with MicroPython or CircuitPython?

😐

Python isn't exactly known for being a language that exposes the underlying
hardware. While it's possible to make the library work with MicroPython and/or
CircuitPython, that'd defeat the point of the library being a way to hide
*only* the complexities that are unrelated to memory-mapped I/O,
polling, and interrupts.

## Are you going to make it work with the XYZ microcontroller board?

Probably.

The Cow Pi works with the Arduino Nano and the Arduino Uno.

We have plans to make it work with the Arduino Mega 2560, the Arduino Nano
Every, the Arduino Nano 33 IOT, and the Raspberry Pi Pico (both using the
Arduino framework and using the Pico SDK). Probably the Raspberry Pi 4 and 400,
too. Eventually the Arduino Nano 33 BLE Sense, the Arduino RP2040 Connect, and
the Arduino Uno WiFi (but we don't have samples of any of these laying
around).

### What about the STM32 "Blue Pill," or something in the Adafruit Feather family, or the SparkFun Teensy family, or...?

If there's interest using one of these microcontroller boards for the Cow Pi,
we can certainly look into it.

Similarly, if there's interest in a different display module, we can look into
it.
