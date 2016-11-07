/* ****************************************************************************
 * MIT License
 *
 * Copyright (c) 2016 carlosperate https://github.com/carlosperate/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * FROM, LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 * ***************************************************************************/

#include <stdint.h>
#include "images.h"


/* ****************************************************************************
 * Constants
 * ***************************************************************************/
const uint8_t IMAGEDATA_HEAR[] __attribute__ ((aligned (4))) = {
    0xff, 0xff, 5, 0, 5, 0,
    0, 1, 0, 1, 0,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    0, 1, 1, 1, 0,
    0, 0, 1, 0, 0,
};
MicroBitImage IMAGE_HEART((ImageData*)(void*)IMAGEDATA_HEAR);

const uint8_t IMAGEDATA_HEAR_ANIMATION[] __attribute__ ((aligned (4))) = {
    0xff, 0xff, 10, 0, 5, 0,
    0, 1, 0, 1, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 1, 1, 0, 1, 0, 1, 0,
    1, 1, 1, 1, 1, 0, 1, 1, 1, 0,
    0, 1, 1, 1, 0, 0, 0, 1, 0, 0,
    0, 0, 1, 0, 0, 0, 0, 0, 0, 0
};
MicroBitImage IMAGE_HEAR_ANIMATION((ImageData*)(void*)IMAGEDATA_HEAR_ANIMATION);

const uint8_t IMAGEDATA_TICK[] __attribute__ ((aligned (4))) = {
    0xff, 0xff, 5, 0, 5, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 1,
    0, 0, 0, 1, 0,
    1, 0, 1, 0, 0,
    0, 1, 0, 0, 0,
};
MicroBitImage IMAGE_TICK((ImageData*)(void*)IMAGEDATA_TICK);

const uint8_t IMAGEDATA_CROSS[] __attribute__ ((aligned (4))) = {
    0xff, 0xff, 5, 0, 5, 0,
    1, 0, 0, 0, 1,
    0, 1, 0, 1, 0,
    0, 0, 1, 0, 0,
    0, 1, 0, 1, 0,
    1, 0, 0, 0, 1,
};
MicroBitImage IMAGE_CROSS((ImageData*)(void*)IMAGEDATA_CROSS);

const uint8_t IMAGEDATA_HAPPY[] __attribute__ ((aligned (4))) = {
    0xff, 0xff, 5, 0, 5, 0,
    0, 0, 0, 0, 0,
    0, 1, 0, 1, 0,
    0, 0, 0, 0, 0,
    1, 0, 0, 0, 1,
    0, 1, 1, 1, 0,
};
MicroBitImage IMAGE_HAPPY((ImageData*)(void*)IMAGEDATA_HAPPY);

const uint8_t IMAGEDATA_SAD[] __attribute__ ((aligned (4))) = {
    0xff, 0xff, 5, 0, 5, 0,
    0, 0, 0, 0, 0,
    0, 1, 0, 1, 0,
    0, 0, 0, 0, 0,
    0, 1, 1, 1, 0,
    1, 0, 0, 0, 1,
};
MicroBitImage IMAGE_SAD((ImageData*)(void*)IMAGEDATA_SAD);

const uint8_t IMAGEDATA_ANGRY[] __attribute__ ((aligned (4))) = {
    0xff, 0xff, 5, 0, 5, 0,
    1, 0, 0, 0, 1,
    0, 1, 0, 1, 0,
    0, 0, 0, 0, 0,
    1, 1, 1, 1, 1,
    1, 0, 0, 0, 1,
};
MicroBitImage IMAGE_ANGRY((ImageData*)(void*)IMAGEDATA_ANGRY);

const uint8_t IMAGEDATA_ARROW_UP[] __attribute__ ((aligned (4))) = {
    0xff, 0xff, 5, 0, 5, 0,
    0, 0, 1, 0, 0,
    0, 1, 1, 1, 0,
    1, 0, 1, 0, 1,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
};
MicroBitImage IMAGE_ARROW_UP((ImageData*)(void*)IMAGEDATA_ARROW_UP);

const uint8_t IMAGEDATA_ARROW_DOWN[] __attribute__ ((aligned (4))) = {
    0xff, 0xff, 5, 0, 5, 0,
    0, 0, 1, 0, 0,
    0, 0, 1, 0, 0,
    1, 0, 1, 0, 1,
    0, 1, 1, 1, 0,
    0, 0, 1, 0, 0,
};
MicroBitImage IMAGE_ARROW_DOWN((ImageData*)(void*)IMAGEDATA_ARROW_DOWN);

const uint8_t IMAGEDATA_ARROW_LEFT[] __attribute__ ((aligned (4))) = {
    0xff, 0xff, 5, 0, 5, 0,
    0, 0, 1, 0, 0,
    0, 1, 0, 0, 0,
    1, 1, 1, 1, 1,
    0, 1, 0, 0, 0,
    0, 0, 1, 0, 0,
};
MicroBitImage IMAGE_ARROW_LEFT((ImageData*)(void*)IMAGEDATA_ARROW_LEFT);

const uint8_t IMAGEDATA_ARROW_RIGHT[] __attribute__ ((aligned (4))) = {
    0xff, 0xff, 5, 0, 5, 0,
    0, 0, 1, 0, 0,
    0, 0, 0, 1, 0,
    1, 1, 1, 1, 1,
    0, 0, 0, 1, 0,
    0, 0, 1, 0, 0,
};
MicroBitImage IMAGE_ARROW_RIGHT((ImageData*)(void*)IMAGEDATA_ARROW_RIGHT);

// TODO: This is here mostly to copy and paste, should be removed
const uint8_t IMAGE_BLANK[] __attribute__ ((aligned (4))) = {
    0xff, 0xff, 5, 0, 5, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
};
