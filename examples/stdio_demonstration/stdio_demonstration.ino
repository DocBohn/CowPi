#include "CowPi.h"

void setup() {
    cowpi_stdio_setup(9600);
    cowpi_setup(0);

    printf("Unlike normal Arduino-based systems, CowPi lets you use `printf` & `scanf`,\n");
    printf("\tbut only if you call `cowpi_stdio_setup` first.\n");

    Serial.println(F("If you plan to use Arduino's `F()` macro to save RAM, use `Serial.print`"));
    Serial.println(F("\tand/or `Serial.println`."));

    char s[83];
    printf("%s", strcpy_P(s, PSTR("But using the avr-libc `PSTR()` macro and the pointer returned by the\n")));
    printf("%s", strcpy_P(s, PSTR("\t`strcpy_P` function is a way to put string constants in flash memory\n")));
    printf("%s", strcpy_P(s, PSTR("\tand use them with `printf`.\n")));

    printf("%s", strcpy_P(s, PSTR("Floating point conversion won't work with `printf`, but you really should think\n")));
    printf("%s", strcpy_P(s, PSTR("\ttwice about using floats on a microcontroller in the first place.\n\n")));
}

void loop() {
    char s[83];
    char c;
    int i;
    printf("%s", strcpy_P(s, PSTR("Enter an integer from the host computer's keyboard: ")));
    scanf("%d", &i);
    scanf("%c", &c);    // consume the linefeed character
    printf("\nYou entered: %d\n", i);
    printf("%s", strcpy_P(s, PSTR("Enter a character from the host computer's keyboard: ")));
    scanf("%c", &c);
    printf("\nYou entered: %c\n", c);
    printf("%s", strcpy_P(s, PSTR("Enter a string from the host computer's keyboard: ")));
    scanf("%80s", s);
    printf("\nYou entered: %s\n", s);
}
