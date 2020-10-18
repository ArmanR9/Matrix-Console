#pragma once

// Returns sign of number
template <typename T> int sgn(T val) {
    return (T(0) < val) - (val < T(0));
}

// Clips number to given range
template <typename T> T clip(T val, T higher, T lower) {
    val = val > higher ? higher : val;
    val = val < lower ? lower : val;
    return val;
}

// 2D Vector Structure for represnting (x,y) coords
 struct Vec2{
    int x;
    int y;
 };

// DebugLevel enumeration for logging methods
 enum class DebugLevel{
    E_NORMAL = 0,
    E_VERBOSE
};