#include <stdint.h>

typedef struct {
    uint32_t x, y;
} Point;

typedef struct {
    uint32_t min, max;
} Limit;

Point linalc_mathp_to_screenp_bounded(Point m, Limit x, Limit y, uint16_t W, uint16_t H);
Point linalc_screenp_to_mathp_bounded(Point s, Limit x, Limit y, uint16_t W, uint16_t H);
