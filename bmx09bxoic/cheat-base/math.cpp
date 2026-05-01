#include "math.h"

namespace math
{
float roundFloat(float x, int decimals)
{
    float scale = std::powf(10.0f, decimals);
    return roundf(x * scale) / scale;
}
}