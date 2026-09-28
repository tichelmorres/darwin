#include "linalc.h"

/*
         (Xm - Xmin) 
   Xs = ------------- * W
        (Xmax - Xmin)

             /  (Ym - Ymin)     \
   Ys = H - (  ------------- * H )
             \ (Ymax - Ymin)    /
 */
Point linalc_mathp_to_screenp_bounded(Point m, Limit x, Limit y, uint16_t W, uint16_t H) {
    uint32_t tx = (m.x - x.min) / (x.max - x.min);
    uint32_t ty = (m.y - y.min) / (y.max - y.min);

    return (Point) {
        .x = tx * W,
        .y = H - (ty * H)
        //     ^
        //   Flip Y
    };
}

/*
        (Xs + Xmin) 
   Xm = ----------- * (Xmax - Xmin)
             W

             / (Ys + Ymin)                \
   Ym = H + (  ----------- * (Ymax - Ymin) )
             \      H                     /
 */
Point linalc_screenp_to_mathp_bounded(Point s, Limit x, Limit y, uint16_t W, uint16_t H) {
    uint32_t tx = (s.x + x.min) / W;
    uint32_t ty = (s.y + y.min) / H;

    return (Point) {
        .x = tx * (x.max - x.min),
        .y = H + (ty * (y.max - y.min))
    };
}
