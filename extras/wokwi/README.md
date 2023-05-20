# Wokwi Circuits

In this directory are diagram files for the [Wokwi](https://wokwi.com/) online microcontroller simulator.
If you create a project and copy one of these files into the project's `diagram.json` file, then you will have a simulated Cow Pi.
Upload the CowPi library's files from the library's `src/` directory to the project, and you'll be able to run any program you write for the basic Cow Pi.

- After we register the library with Arduino Library Manager, you won't need to copy the library's files into the project.
- If you use the Wokwi VS Code plugin (currently in beta), be sure to copy (and possibly edit) `wokwi.toml` into the project.

## The files

- `nano-template.json` -- Has everything *except* a display module.
    Instead, it has a pair of DIP switches, one with the wiring for SPI, and one with the wiring for I2C.
- `nano-spi-max2719matrix.json` -- Has two pushbuttons (tactile switches), two slider switches in the SPI configuration (*i.e.*, the switches are attached to pins D18/A4 and D19/A5), and a **MAX7219-based 8x8 LED matrix** that uses the SPI protocol.
- `nano-spi-max2719matrix-chained.json` -- Identical to `nano-spi-max2719matrix.json`, except that it has four **daisy-chained MAX7219-based 8x8 LED matrices**, forming a 32x8 LED matrix.
- `nano-i2c-lcd1602.json` -- Has two pushbuttons (tactile switches), two slider switches in the I2C configuration (*i.e.*, the switches are attached to pins D10 and D11), and a **HH44780-based 16x2 LCD character display** that uses the I2C protocol.
    Wokwi has the serial adapter mapped to the LCD1602's pins using the `COWPI_DEFAULT` dialect.
- `nano-i2c-oled128x64.json` -- Has two pushbuttons (tactile switches), two slider switches in the I2C configuration (*i.e.*, the switches are attached to pins D10 and D11), and a **SSD1306-based 128x64 OLED matrix** that uses the I2C protocol.
- `wokwi.toml` -- a file needed by the Wokwi VS Code plugin to locate the firmware.
    You may need to edit it.

## Why have a simulation?

Before the Pandemic Year of 2020-21, we hadn't yet transitioned away from the [Terasic Altera DE1](https://www.terasic.com.tw/cgi-bin/page/archive.pl?No=83) and hadn't yet determined what the replacement would be for our Computer Science students and our Software Engineering students.
Our Computer Engineering students transitioned to the [Terasic DE10-Lite](http://de10-lite.terasic.com/), but for what our Computer Science students and our Software Engineering students needed, the DE10-Lite is overkill and not worth the price (short version: the CS and SE students didn't take advantage of the FPGA on the DE1 and wouldn't on the DE10-Lite).
The price factor wasn't a small matter: where we had issued the DE-1 boards to student for a few weeks (or for the semester for CpE students), we would expect students to purchase whatever replaced the DE1.

The Pandemic Year added another wrinkle: many of our students weren't in-town, and many weren't even in-country!
The Computer Engineering students were able to purchase DE10-Lite boards from the same third-party (*cough* Amazon *cough*) that they would if classes were held in-person, but we couldn't easily issue the aging DE1 boards and probably wouldn't want to if we could since replacing a board that finally went dud wouldn't be a simple matter of walking down the hall from the lab room to the sysadmin suite.

And so, for the Pandemic Year, I wrote the "Simulated Single Board Computer" (SSBC) to run on the department's Linux server.
The SSBC was a hack that required students to lock a mutex before updating the simulated memory-mapped I/O registers to prevent a race condition with the SSBC's display.
I later learned that it also didn't give students the confidence that they got from working with "real" hardware, which was a little problematic when some of those students became TAs.

If we have another Pandemic Year, our university's EE Shop would temporarily suspend its no-shipping policy like it did for 2020-21, but it would be nice if international students didn't have to worry about international shipping!
And so I decided that a simulation of the Cow Pi was necessary.
While I initially considered using something like [simavr](https://github.com/buserror/simavr) and writing a full simulator myself, there are a couple of online simulators already available: [TinkerCad](https://www.tinkercad.com/) and [Wokwi](https://wokwi.com/) (The software behind Wokwi can also be run as a local instance, which is nice, but without many of the components available at [wokwi.com](https://wokwi.com/)).

On the balance, Wokwi is a clear winner for our potential needs.
While Wokwi started as an AVR simulation, it has grown to ARM-based microcontroller boards such as the Raspberry Pi Pico (using either the Arduino framework or the Raspberry Pi Pico SDK).
Both TinkerCad and Wokwi have I2C-LCD1602s (and both have 74HC595s, allowing us to create SPI-LCD1602s), but only Wokwi has a MAX7219 display (an 8x8 LED matrix -- I'd prefer an 8-digit 7-segment display, but neither has that).
TinkerCad can have more than one microcontroller in one simulation, but each microcontroller only gets one file which is problematic for non-trivial projects, whereas Wokwi allows many files (but only one microcontroller) per project.
Wokwi also has an "okay" autocomplete feature.
The shortcomings of Wokwi relative to TinkerCad have substantially disappeared since I first made the comparison, which makes it an even clearer winner.
The VS Code plugin is the icing on the cake.