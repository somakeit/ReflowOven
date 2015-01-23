# ReflowOven
So Make It's reflow oven firmware &amp; hardware source

##Building
You will need to install these arduino libraries:
- [Adafruit-MAX31855-library][1]
- [PID_v1][2]

[1]: https://github.com/adafruit/Adafruit-MAX31855-library
[2]: https://github.com/br3ttb/Arduino-PID-Library/

##PC Interface
I propose we use G-Codes:
- M104 - set temp eg. "M04 S200"
- M105 - get temp, reports oven and electronics bay temp, eg. "ok T:200 B:50" (maybe also PID value).
- M32 - start a built in program, eg. "M32 lead-reflow".
- M20 - list built in programs.
- M300 - Beep
- M301 - set Kp/Ki/Kd values in RAM.
- M500 - Save RAM settings to EEPROM.
- M502 - Restore default settings in EEPROM and RAM.
- M503 - Report settings
- M510* - Set bake temp in RAM in C eg. "M510 S80" #TOTO fill in sensible defaults.
- M511* - Set bake time in RAM in minutes eg. "M511 S60"
- M520* - Set sn/pb soak temp in C. #TODO make sure this actually describes the processes we need
- M521* - set sn/pb ramp to saok rate in C/min.
- M522* - set sn/pb soak time in min.
- M523* - set sn/pb flow temp.
- M524* - set sn/pb flow time.
- M530/1/2/3/4 - set no-pb paramaters as in M520/1/2/3/4
- Any other profiles, Dave?
The obvious advanage is we can use printer host software to drive the machine when we need a pretty graph.
*non-standard G-Code.

##LCD interface
This is #TODO, we have an RGB backlit 16x2 character display, main screen when operating maybe:
```
 ________________
|T248/250C P 42% |
|SN/PB-FLOW      |
------------------
```
