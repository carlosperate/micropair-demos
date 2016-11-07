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

#include "MicroBit.h"

#include "main.h"
#include "images.h"
#include "pong.h"


/* ****************************************************************************
 * Constants
 * ***************************************************************************/
static const uint8_t NUMBER_OF_ROWS = 5;
static const uint8_t NUMBER_OF_COLS = 5;
static const uint8_t COL = 0;
static const uint8_t ROW = 1;


/* ****************************************************************************
 * Globals
 * ***************************************************************************/
MicroBitImage frame(NUMBER_OF_COLS, NUMBER_OF_ROWS);


/******************************************************************************
 * Function declarations
 *****************************************************************************/
int8_t calculatePadPosition(int8_t pad_position);
void drawPad(int8_t pad_position);
void moveBall(int8_t ball_position[], int8_t ball_velocity[]);
bool padBounce(int8_t ball_position[], int8_t pad_position);
void padCollision(int8_t ball_position[], int8_t ball_velocity[],
                  int8_t pad_position);
void drawFrame();
void communicateGameState();
void winAnimation();
void loseAnimation();


/******************************************************************************
 * Function definitions
 *****************************************************************************/
/**
 * Calculates the position of the player's pad.
 * The pad itsel only moves horizontally on the lowest row.
 * This function should ideally be called at the beggining of the "frame".
 * @param
 * @return
 */
int8_t calculatePadPosition(int8_t pad_position) {
    // Pad is 2 pixels in a known axes, so only store its "left" pixel

    // First check if either the left (A) or right (B) buttons are pressed
    if (uBit.buttonAB.isPressed()) {
        // If both buttons are pressed don't move at all
    } else if (uBit.buttonA.isPressed()) {
        // Move left only if there is space on the left to move
        if (pad_position != 0) {
            pad_position--;
        }
    } else if (uBit.buttonB.isPressed()) {
        // Move right and correct position if out of bounds
        pad_position++;
        if (pad_position > NUMBER_OF_ROWS -2) {
            pad_position = NUMBER_OF_ROWS - 2;
        }
    }

    return pad_position;
}

/**
 * Description.
 * @param
 * @return
 */
void drawPad(int8_t pad_position) {
    // Simplest thing is to "erase" the row and then add the pad
    for (int i = 0; i < NUMBER_OF_ROWS; i++) {
        frame.setPixelValue(i, NUMBER_OF_ROWS - 1, 0);
    }
    frame.setPixelValue(pad_position,     NUMBER_OF_ROWS - 1, 1);
    frame.setPixelValue(pad_position + 1, NUMBER_OF_ROWS - 1, 1);
}

/**
 * Description.
 * @param
 * @return
 */
void moveBall(int8_t ball_position[], int8_t ball_velocity[]) {
    // First remove the pixel for the current ball position
    frame.setPixelValue(ball_position[COL], ball_position[ROW], 0);

    // Calculate the new ball positio based on two dimensional velocity
    ball_position[COL] += ball_velocity[COL];
    if (ball_position[COL] >= NUMBER_OF_COLS) {
        ball_position[COL] = NUMBER_OF_COLS - 1;
        ball_velocity[COL] = -ball_velocity[COL];
    } else if (ball_position[COL] <= 0) {
        ball_position[COL] = 0;
        ball_velocity[COL] = -ball_velocity[COL];
    }

    ball_position[ROW] += ball_velocity[ROW];
    if (ball_position[ROW] >= NUMBER_OF_ROWS) {
        ball_position[ROW] = NUMBER_OF_ROWS - 1;
        ball_velocity[ROW] = -ball_velocity[ROW];
    } else if (ball_position[ROW] <= 0) {
        ball_position[ROW] = 0;
        ball_velocity[ROW] = -ball_velocity[ROW];
    }

    // Add the new ball position
    frame.setPixelValue(ball_position[COL], ball_position[ROW], 1);
}

/**
 * Description.
 * @param
 * @return
 */
void padBounce(int8_t ball_position[], int8_t ball_velocity[],
               int8_t pad_position) {
    if (ball_position[ROW] == (NUMBER_OF_ROWS - 1)) {
        if ((ball_position[COL] == pad_position) ||
            (ball_position[COL] == (pad_position + 1))) {
            // If hitting the pad bounce back
            ball_velocity[ROW] = -ball_velocity[ROW];
            ball_position[ROW] += ball_velocity[ROW];

            // Draw the new ball position, there is no need to erase previous
            // position, as it was placed on top of where the pad is
            frame.setPixelValue(ball_position[COL], ball_position[ROW], 1);
        }
    }
}

/**
 * Description.
 * @param
 * @return
 */
void drawFrame() {
    uBit.display.print(frame);
}

/**
 * Description.
 * @param
 * @return
 */
bool backWallCollision(int8_t ball_position[], int8_t pad_position) {
    bool collided = false;
    if (ball_position[ROW] == (NUMBER_OF_ROWS - 1)) {
        if ((ball_position[COL] != pad_position) &&
            (ball_position[COL] != (pad_position + 1))) {
            collided = true;
        }
    }
    return collided;
}

/**
 * Description.
 * @param
 * @return
 */
void winAnimation() {
    // TODO: At the moment this is a very very crude animation, to be improved
    for (int i = 0; i < 2; i++) {
        uBit.display.print(IMAGE_TICK);
        uBit.sleep(1000);
        uBit.display.clear();
        uBit.sleep(500);
    }
    uBit.display.print(IMAGE_HAPPY);
    uBit.sleep(5000);
}

/**
 * Description.
 * @param
 * @return
 */
void loseAnimation(int8_t ball_position[]) {
    // First let's blink the ball pixel
    for (int i = 0; i < 3; i++) {
        uBit.display.image.setPixelValue(
                ball_position[COL], ball_position[ROW], 255);
        uBit.sleep(500);
        uBit.display.image.setPixelValue(
                ball_position[COL], ball_position[ROW], 0);
        uBit.sleep(500);
    }

    // TODO: At the moment this is a very very crude animation, to be improved
    for (int i = 0; i < 2; i++) {
        uBit.display.print(IMAGE_CROSS);
        uBit.sleep(1000);
        uBit.display.clear();
        uBit.sleep(500);
    }
    uBit.display.print(IMAGE_SAD);
    uBit.sleep(2000);
}

/**
 * Description.
 * @param
 * @return
 */
void communicateGameState() {}

/**
 * Description.
 * @param
 * @return
 */
void playPong() {
    uint16_t ticker = 1;
    bool collided = false;
    bool game_over = false;
    // Place the initial position of the ball at the top centre
    int8_t ball_position[] = {(NUMBER_OF_COLS) / 2, 0};
    int8_t ball_velocity[] = {1, 1};
    int8_t pad_position = 0;

    // The game "ticks" very 100ms (10fps)
    while (!game_over) {
        pad_position = calculatePadPosition(pad_position);
        drawPad(pad_position);
        moveBall(ball_position, ball_velocity);
        padBounce(ball_position, ball_velocity, pad_position);
        drawFrame();

        collided = backWallCollision(ball_position, pad_position);
        if (collided) {
            game_over = true;
            loseAnimation(ball_position);
        }

        ticker++;
        if (ticker < 1) {
            // Did our unsigned 16 bit integer just rolled over??
            // WOW that was a long and impressive game! I guess you both win?
            game_over = true;
            winAnimation();
        }

        communicateGameState();
        uBit.sleep(200);
    }
    return;
}
