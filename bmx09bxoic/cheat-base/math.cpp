#include "math.h"

namespace math
{
float roundFloat(float x, int decimals)
{
    float scale = std::powf(10.0f, decimals);
    return roundf(x * scale) / scale;
}

inline float toFloat(int x)
{
    return static_cast<float>(x);
}

inline int toInt(float x)
{
    return static_cast<int>(x);
}
}