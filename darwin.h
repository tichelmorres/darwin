#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

#ifndef DARWIN_H_
#define DARWIN_H_

#define UNUSED(value) (void)(value)
#define TODO(message) do {                                                                    \
                          fprintf(stderr, "%s:%d: TODO: %s \n", __FILE__, __LINE__, message); \
                          abort();                                                            \
                      } while(0)

#define ARRAY_LEN(array) (sizeof(array)/sizeof(array[0]))

#define NANOS_PER_SEC (1000*1000*1000)

#define FPS        60
#define WIDTH      800
#define HEIGHT     600
#define BACKGROUND 0xFF182838 // ARGB

typedef uint32_t Pixel32;

static float FRAME_TIME = (1/60);

void update(Pixel32 *pixels);

#endif // DARWIN_H_
