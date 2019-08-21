# LED_Code_Archive

If writing new LED code, it may be helpful to take functions that make patterns from some of these programs and maybe taking a look at how they are structured.

### LEDA3:
Aluminati (bunny2017)'s LED code. Used on competition robot. A single Neopixel string lit up the bulldozer with a symmetrical purple wave and rainbow pattern

### LEDJ2
Phantom (2017 Steamworks)'s LED code. Never put on competition robot. Responds to alliance color, times match sections, and detects sound.

### LEDT1
Code for a "time machine" for the Eugene Symphony's 2019 kids' concert. This was when the "rainbow box" (pit leds) were made. The lights were wrapped around a decorated tube and connected to a big button on top that they pushed when they wanted the Hult Center to time travel. The lights flashed for a set amount of time then faded back to off.

### LEDs19JPv3
Chimera (2019 Deep Space)'s LED code. Removed from competition robot before competition. Alliance color can be set, match sections are timed, and any color can be displayed for a driver alert all controlled from one PWM (servo) input.

### 2018rainbows4
A more complex version of Poe (2018 PowerUp)'s LED code. Alliance color can be set, and timers allow for different patterns throughout the match. Controlled by a red alliance pin and a blue alliance pin.

### 2018rainbowsS1
A modifyed version of Poe's LED code. Using two pins, 4 modes can be selected to give driver feedback. Run on the robot for at least some of offseason.

### lights4OI
LED code for lights wrapping around an OI. This code takes input from many pins, one for enabled signal, one for autonomous, one for alliance color and 5 to give match time in binary. In standby mode one of 4 patterns is selected randomly. It would have gotten input from a TI Launchpad plugged into the DS.

### oi_lights
I think this is an update on lights4OI.

### rainbowBoxCode2
Code for the pit/event decoration LEDs. Same string as for the time machines. This version advances through its list of patterns each time a button is pressed. A possible update would be using the connected 1 axis joystick to give an additional level of control. This code is a good library of pattern functions.

### time_machine_v0_2019
Code for a "time machine" for the Eugene Symphony's 2019 kids' concert. The lights were wrapped around a decorated tube, and the operator used a one axis joystick and a button to control the "level" of power the time machine had reached.
