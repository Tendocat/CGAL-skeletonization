#include "pmp/Types.h"

/**
 * @brief ...
 */
inline float dist(const pmp::Point &p1, const pmp::Point &p2)
{
    return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2) + pow(p2[2] - p1[2], 2));
}
