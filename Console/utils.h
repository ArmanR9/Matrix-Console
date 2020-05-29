#pragma once

template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

template <typename T> T clip(T val, T higher, T lower) {
    val = val > higher ? higher : val;
    val = val < lower ? lower : val;
    return val;
}

 struct Vec2{
    int x;
    int y;
 };

 enum class DebugLevel{
    E_NORMAL = 0,
    E_VERBOSE
};