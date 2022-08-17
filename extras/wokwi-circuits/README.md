# Wokwi Circuits

In this directory are diagram files for the [Wokwi](https://wokwi.com/) online
microcontroller simulator. If you create a project and copy one of these files
into the project's `diagram.json` file, then you will have a simulated Cow Pi
that only lacks the 74LS20 NAND chip. Upload the CowPi library's files from
the library's `src/` directory to the project, and you'll be able to run any
program you write for the basic Cow Pi, with two possible changes:

- If you're using interrupts to detect key presses and/or button presses then
  you'll need to set up pin change interrupts instead of external interrupts.
- If you're using an LCD1602 with the I2C protocol, you'll need to set the
  dialect to `WOKWI`.

## The files

- `Uno-MAX7219-Matrix.json` -- Has two pushbuttons (tactile switches), two
  slider switches in the SPI configuration (*i.e.*, the switches are attached
  to pins A4 and A5), and a MAX7219-based 8x8 LED matrix that uses the SPI
  protocol.
- `Uno-LCD1602-SPI-Adafruit.json` -- Has two pushbuttons (tactile switches), two
  slider switches in the SPI configuration (*i.e.*, the switches are attached
  to pins A4 and A5), and a LCD1602 connected to a 74HC595 so that it uses the
  SPI protocol. The '595 pins are mapped to the LCD1602's pins using the
  `ADAFRUIT` dialect; you can, of course, change this if you wish.
- `Uno-LCD1602-I2C.json` -- Has two pushbuttons (tactile switches), two
  slider switches in the I2C configuration (*i.e.*, the switches are attached
  to pins D10 and D11), and a LCD1602 that uses the I2C protocol. Wokwi has
  the I2C mapped to the LCD1602's pins using the `COWPI_DEFAULT` dialect; this cannot
  be changed unless you rewrite the LCD1602 module on a local Wokwi instance.

## Why have a simulation?

Before the Pandemic Year of 2020-21, we hadn't yet transitioned away from the
[Terasic Altera DE1](https://www.terasic.com.tw/cgi-bin/page/archive.pl?No=83)
and hadn't yet determined what the replacement would be for our Computer Science
students and our Software Engineering students. Our Computer Engineering
students transitioned to the [Terasic DE10-Lite](http://de10-lite.terasic.com/),
but for what our Computer Science students and our Software Engineering students
needed, the DE10-Lite is overkill and not worth the price (short version: the CS
and SE students didn't take advantage of the FPGA on the DE1 and wouldn't on the
DE10-Lite). The price factor wasn't a small matter: where we had issued the DE-1
boards to student for a few weeks (or for the semester for CpE students), we
would expect students to purchase the replacement.

The Pandemic Year added another wrinkle: many of our students weren't in-town,
and many weren't even in-country! The Computer Engineering students were able to
purchase DE10-Lite boards from the same third-party (*cough* Amazon *cough*)
that they would if classes were held in-person, but we couldn't easily issue
the aging DE1 boards and probably wouldn't want to if we could since replacing
a board that finally went dud wouldn't be a simple matter of walking down the
hall from the lab room to the sysadmin suite.

And so, for the Pandemic Year, I wrote the "Simulated Single Board Computer"
(SSBC) to run on the department's Linux server. The SSBC was a hack that
required students to lock a mutex before updating the simulated memory-mapped
I/O registers to prevent a race condition with the SSBC's display. I later
learned that it also didn't give students the confidence that they got from
working with "real" hardware, which was a little problematic when some of those
students became TAs.

If we have another Pandemic Year, our university's EE Shop would temporarily
suspend its no-shipping policy like it did for 2020-21, but it would be nice
if international students didn't have to worry about international shipping!
And so I decided that a simulation of the Cow Pi was necessary. While I
initially considered using something like
[simavr](https://github.com/buserror/simavr) and writing a full simulator
myself, there are a couple of online simulators already available:
[TinkerCad](https://www.tinkercad.com/) and [Wokwi](https://wokwi.com/) (Wokwi
can also be run as a local instance, which is nice).

On the balance, Wokwi is a clear winner for our potential needs. While Wokwi
started as an AVR simulation, it has grown to ARM-based microcontroller boards
such as the Raspberry Pi Pico (using either the Arduino framework or the
Raspberry Pi Pico SDK). Both TinkerCad and Wokwi have I2C-LCD1602s (and both
have 74HC595s, allowing us to create SPI-LCD1602s), but only Wokwi has a MAX7219
display (an 8x8 LED matrix -- I'd prefer an 8-digit 7-segment display, but
neither has that). TinkerCad can have more than one microcontroller in one
simulation, but each microcontroller only gets one file which is problematic
for non-trivial projects, whereas Wokwi allows many files (but only one
microcontroller) per project. Wokwi also has an "okay" autocomplete feature.
The only advantages that TinkerCad has over Wokwi are that TinkerCad has simple
logic ICs (such as the 74LS20) but Wokwi doesn't -- which means that
InterruptLab would need to use pin change interrupts instead of external
interrupts -- ~~and TinkerCad has a built-in debugger~~ and TinkerCad has a
debugger that has a look-and-feel like that of an IDE debugger, whereas Wokwi
uses [Web GDB](https://docs.wokwi.com/gdb-debugging) (since my students will
have learned GDB before the hardware labs, I can live with that, even if Web
GDB is a bit slow).
