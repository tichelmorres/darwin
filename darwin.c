#include "darwin.h"
#include "lib/linalc.h"

// #define ITER_AMOUNT 100

void update(Pixel32 *pixels) {
    for (uint16_t y = 0; y < HEIGHT; ++y) {
        for (uint16_t x = 0; x < WIDTH; ++x) {
            pixels[y*WIDTH + x] = BACKGROUND;
        }
    }

    // for (uint8_t i = 0; i < ITER_AMOUNT; ++i) {
    //
    // }
}
