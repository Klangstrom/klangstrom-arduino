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

#include <iostream>
#include <cstdint>
#include <cctype>
#include <cmath>

#include "Arduino.h"
#include "ArduinoFunctions.h"
#include "KlangstromEmulator.h"

void delay(uint32_t milliseconds) {
    umfeld::KlangstromEmulator::instance()->delay_loop(milliseconds * 1000);
}

void delayMicroseconds(uint32_t microseconds) {
    umfeld::KlangstromEmulator::instance()->delay_loop(microseconds);
}

uint32_t micros() {
    static auto startTime   = std::chrono::steady_clock::now();
    auto        currentTime = std::chrono::steady_clock::now();
    auto        duration    = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - startTime).count();
    return static_cast<uint32_t>(duration);
}

uint32_t millis() {
    return micros() / 1000;
}

template<typename T>
T abs(T value) {
    return (value < 0) ? -value : value;
}

long map(long value, long fromLow, long fromHigh, long toLow, long toHigh) {
    return (value - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

bool isAlpha(char c) {
    return std::isalpha(static_cast<unsigned char>(c));
}

bool isAlphaNumeric(char c) {
    return std::isalnum(static_cast<unsigned char>(c));
}

bool isAscii(char c) {
    return static_cast<unsigned char>(c) <= 127;
}

bool isControl(char c) {
    return std::iscntrl(static_cast<unsigned char>(c));
}

bool isDigit(char c) {
    return std::isdigit(static_cast<unsigned char>(c));
}

bool isGraph(char c) {
    return std::isgraph(static_cast<unsigned char>(c));
}

bool isHexadecimalDigit(char c) {
    return std::isxdigit(static_cast<unsigned char>(c));
}

bool isLowerCase(char c) {
    return std::islower(static_cast<unsigned char>(c));
}

bool isPrintable(char c) {
    return std::isprint(static_cast<unsigned char>(c));
}

bool isPunct(char c) {
    return std::ispunct(static_cast<unsigned char>(c));
}

bool isSpace(char c) {
    return std::isspace(static_cast<unsigned char>(c));
}

bool isUpperCase(char c) {
    return std::isupper(static_cast<unsigned char>(c));
}

bool isWhitespace(char c) {
    return std::isspace(static_cast<unsigned char>(c));
}

long random(long max) {
    if (max == 0) {
        return 0;
    }
    return std::rand() % max;
}

long random(long min, long max) {
    if (min >= max) {
        return min;
    }
    long range = max - min;
    return min + std::rand() % range;
}

void randomSeed(uint32_t seed) {
    std::srand(seed);
}

uint8_t bit(uint8_t n) {
    return 1 << n;
}

uint8_t bitClear(uint8_t value, uint8_t bit) {
    value &= ~(1 << bit);
    return value;
}

bool bitRead(uint8_t value, uint8_t bit) {
    return (value >> bit) & 1;
}

uint8_t bitSet(uint8_t value, uint8_t bit) {
    value |= (1 << bit);
    return value;
}

uint8_t bitWrite(uint8_t value, uint8_t bit, bool bitValue) {
    if (bitValue) {
        value = bitSet(value, bit);
    } else {
        value = bitClear(value, bit);
    }
    return value;
}

uint8_t highByte(uint16_t value) {
    return value >> 8;
}

uint8_t lowByte(uint16_t value) {
    return value & 0xFF;
}

void attachInterrupt() {}

void detachInterrupt() {}

void digitalPinToInterrupt() {}

void interrupts() {}

void noInterrupts() {}
