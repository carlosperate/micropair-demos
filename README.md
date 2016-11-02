# Micropair Demos

This repository contains a C/C++ application for the BBC micro:bit to
demonstrate the capabilities of the radio communication between two micro:bits.

To compile this application you will need to have installed `Yotta` as
indicated by the [microbit runtime docs](https://lancaster-university.github.io/microbit-docs/) ([offline yotta instructions](https://lancaster-university.github.io/microbit-docs/offline-toolchains/))

```
yt target bbc-microbit-classic-gcc
yt build
```

The resulting hex file will be saved in the following directory:

```
build\bbc-microbit-classic-gcc\src\micropair-demos-combined.hex
```
