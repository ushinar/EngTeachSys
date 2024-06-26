﻿Letters and Colors teaching system for kids
===========================================

Final Project for practical engineering studies in electronics, written in cx51, and ran on an Arduino kit. Written in 2014.

The projects premise was an aid to teach children letters, numbers, words, and colors in English.
The learning process is enabled by two external inputs the kit has: a Ps2 keyboard (no relation) and a light sensor component.
Recordings are stored on an ISD4004 chip, and are played at the appropriate time using a simple speaker.
Promts, letters/numbers and words are all presented on an LCD screen.

The software routinely scans the keyboard and light sensor to check if the user (child) has either:
* Pressed a key on the keyboard
* Placed one of the colored notes attached to the kit on a designated place for the light sensor to read it.

In the first case, the software awaits further key presses, until the Enter key is pressed - it then activates an operator recording of the number/letter name previously pressed, or a recording of an entire word, in case the inputted word belongs to a limited list of word designated by the operrator.
In the second case, the software compares the signals obtained from the note  with value ranges previously obtained empirically for the various colors. If a match is obtained, an operator recording of the color name is played.

When the recording has finished playing the software resumes scanning until further inputs are picked up.

Operator functions
============================================
The string "bego" followed by Enter acts as a control. When in control mode, the keyboard functions in the same manner as before, but when enter is pressed the operator is promted to record the corresponding word/letter/number name. To record color names, the operators simply records the corresponding word on the keyboard, i.e. "blue" for a blue color etc. The system then remains in control mode until the operator Retypes "bego"+Enter.
