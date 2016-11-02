/*
MIT License

Copyright (c) 2016 carlosperate https://github.com/carlosperate/

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "MicroBit.h"

#include "main.h"
#include "proximity_heart.h"

/*
 * Globals
 */
MicroBit uBit;

ManagedString DEMO_1("1");
ManagedString DEMO_2("2");
ManagedString DEMO_RUN("run");
ManagedString demoSelection = DEMO_1;


/*
 * Function declarations
 */
static void runSelectedDemo();
static void selectNextDemo();
static void onData(MicroBitEvent);


/*
 * Function definitions
 */
static void runSelectedDemo() {
    if (demoSelection == DEMO_1) {
        uBit.messageBus.ignore(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
        run_proximity_heart();
    } else if (demoSelection == DEMO_2) {
        uBit.display.scroll("Other demo");
    } else {
        uBit.display.scroll("Unrecognised demo");
    }
}

static void selectNextDemo() {
    if (demoSelection == DEMO_1) {
        demoSelection = DEMO_2;
    } else if (demoSelection == DEMO_2) {
        demoSelection = DEMO_1;
    } else {
        uBit.display.scroll("Unrecognised demo");
        return;
    }
    uBit.display.print(demoSelection);
}

static void onData(MicroBitEvent) {
    ManagedString receivedDemoSelection = uBit.radio.datagram.recv();

    if (receivedDemoSelection == DEMO_1) {
        demoSelection = DEMO_1;
        uBit.display.print(demoSelection);
    } else if (receivedDemoSelection == DEMO_2) {
        demoSelection = DEMO_2;
        uBit.display.print(demoSelection);
    } else if (receivedDemoSelection == DEMO_RUN) {
        runSelectedDemo();
    } else {
        uBit.display.scroll("Received unsupported value.");
        return;
    }
}


/*
 * main
 */
int main() {
    // Initialise the micro:bit runtime.
    uBit.init();
    uBit.messageBus.listen(MICROBIT_ID_RADIO, MICROBIT_RADIO_EVT_DATAGRAM, onData);
    uBit.radio.enable();

    // Set up a simple triangular waveform for 2 seconds.
    MicroBitImage img("1 0 0 0 0 0 0 0 0 1\n"
                      "0 1 0 0 0 0 0 0 1 0\n"
                      "0 0 1 0 0 0 0 1 0 0\n"
                      "0 0 0 1 0 0 1 0 0 0\n"
                      "0 0 0 0 1 1 0 0 0 0\n");
    for (int i = 0; i < 3; i++) {
        uBit.display.scroll(img, 80, -1);
    }

    uBit.display.scroll("SELECT");
    uBit.display.print(demoSelection);

    while (1) {
        if (uBit.buttonA.isPressed()) {
            selectNextDemo();
            uBit.radio.datagram.send(demoSelection);
            uBit.sleep(500);
        } else if (uBit.buttonB.isPressed()) {
            uBit.radio.datagram.send(demoSelection);
            uBit.radio.datagram.send(DEMO_RUN);
            runSelectedDemo();
        }
        uBit.sleep(100);
    }

    // If main exits, there may still be other fibers running or registered event handlers etc.
    // Simply release this fiber, which will mean we enter the scheduler. Worse case, we then
    // sit in the idle task forever, in a power efficient sleep.
    release_fiber();

    return 0;
}
