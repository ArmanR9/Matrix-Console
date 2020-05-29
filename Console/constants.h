#pragma once
#include "Arduino.h"

// ERROR CODES
#define _ERR_MAX 4294967295; // UINT_MAX

// SIZES
inline constexpr unsigned short _BYTE {8};

// DEVICE CONSTANTS
inline constexpr unsigned short _SCR_W {32};
inline constexpr unsigned short _SCR_H {8};
inline constexpr unsigned short _DIN_PIN {9};
inline constexpr unsigned short _CS_PIN {8};
inline constexpr unsigned short _CLK_PIN {10};
inline constexpr unsigned short _NUM_OF_LED {4};
inline constexpr unsigned short _BTN_PIN {4};
inline constexpr unsigned short _LDR_PIN {0};
inline constexpr unsigned short _BUZZ_PIN {2};
inline constexpr unsigned short _JOYX_PIN {3};
inline constexpr unsigned short _JOYY_PIN {5};
inline constexpr unsigned short _JOYZ_PIN {1};
inline constexpr unsigned short _GAME_COUNT {2};


// BYTE ARRAYS
// Global Byte Arrays for letters on matrices.
// I should probably change this set-up, but all well. It works. ¯\_(ツ)_/¯

inline constexpr unsigned char A[_BYTE] {B00000000,B00111100,B00100100,B00100100,B00111100,B00100100,B00100100,B00000000};
inline constexpr unsigned char E[_BYTE] {B00000000,B00111100,B00100000,B00111000,B00100000,B00100000,B00111100,B00000000};
inline constexpr unsigned char G[_BYTE] {B00000000,B00111110,B00100000,B00100000,B00101110,B00100010,B00111110,B00000000};
inline constexpr unsigned char I[_BYTE] {B00000000,B00111000,B00010000,B00010000,B00010000,B00010000,B00111000,B00000000};
inline constexpr unsigned char M[_BYTE] {B00000000,B01000100,B10101010,B10010010,B10010010,B10000010,B10000010,B00000000};
inline constexpr unsigned char O[_BYTE] {B00000000,B00111100,B01000010,B01000010,B01000010,B01000010,B00111100,B00000000};
inline constexpr unsigned char R[_BYTE] {B00000000,B00111000,B00100100,B00100100,B00111000,B00100100,B00100100,B00000000};
inline constexpr unsigned char T[_BYTE] {B00000000,B01111100,B00010000,B00010000,B00010000,B00010000,B00010000,B00000000};
inline constexpr unsigned char V[_BYTE] {B00000000,B00100010,B00100010,B00100010,B00010100,B00010100,B00001000,B00000000};
inline constexpr unsigned char X[_BYTE] {B00000000,B01000010,B00100100,B00011000,B00011000,B00100100,B01000010,B00000000};
