/*
 * Klangstrom
 *
 * This file is part of the *wellen* library (https://github.com/dennisppaul/wellen).
 * Copyright (c) 2025 Dennis P Paul.
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This library is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <cstdint>

// implement all functions from https://www.arduino.cc/reference/

// TODO add variable
// TODO add emulations for Digital I/O + Analog I/O

// Digital I/O
// digitalRead()
// digitalWrite()
// pinMode()

// Analog I/O
// analogRead()
// analogReadResolution()
// analogReference()
// analogWrite()
// analogWriteResolution()

// Advanced I/O
// noTone()
// pulseIn()
// pulseInLong()
// shiftIn()
// shiftOut()
// tone()

// Time
void     delay(uint32_t milliseconds);
void     delayMicroseconds(uint32_t microseconds);
uint32_t micros();
uint32_t millis();

// Math
template<typename T>
T abs(T value);
template<typename T>
T constrain(T value, T min, T max) {
    if (value < min) return min;
    if (value > max) return max;
    return value;
}
long map(long value, long fromLow, long fromHigh, long toLow, long toHigh);
template<typename T>
T max(T a, T b) { return (a > b) ? a : b; }
template<typename T>
T      min(T a, T b) { return (a < b) ? a : b; }
double pow(double base, double exponent); // from cmath
template<typename T>
T      sq(T value) { return value * value; }
double sqrt(double value); // from cmath

// Trigonometry
double cos(double value); // from cmath
double sin(double value); // from cmath
double tan(double value); // from cmath

// Characters
bool isAlpha(char c);
bool isAlphaNumeric(char c);
bool isAscii(char c);
bool isControl(char c);
bool isDigit(char c);
bool isGraph(char c);
bool isHexadecimalDigit(char c);
bool isLowerCase(char c);
bool isPrintable(char c);
bool isPunct(char c);
bool isSpace(char c);
bool isUpperCase(char c);
bool isWhitespace(char c);

// Random Numbers
long random(long max);
long random(long min, long max);
void randomSeed(uint32_t seed);

// Bits and Bytes
uint8_t bit(uint8_t n);
uint8_t bitClear(uint8_t value, uint8_t bit);
bool    bitRead(uint8_t value, uint8_t bit);
uint8_t bitSet(uint8_t value, uint8_t bit);
uint8_t bitWrite(uint8_t value, uint8_t bit, bool bitValue);
uint8_t highByte(uint16_t value);
uint8_t lowByte(uint16_t value);

// External Interrupts
void attachInterrupt();
void detachInterrupt();
void digitalPinToInterrupt();

// Interrupts
void interrupts();
void noInterrupts();

// Communication
// Print
// Serial
// SPI
// Stream
// Wire

// USB
// Keyboard
// Mouse