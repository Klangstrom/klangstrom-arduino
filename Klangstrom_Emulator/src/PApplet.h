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

#include "Arduino.h"

namespace umfeld {
    class PApplet {
    public:
        virtual ~PApplet() noexcept = default;
        virtual void arguments(std::vector<std::string> args) = 0;
        virtual void settings() = 0;
        virtual void setup() = 0;
        virtual void draw() = 0;
        virtual void audioblock(float** input, float** output, int length) = 0;
        virtual void keyPressed() = 0;
        virtual void keyReleased() = 0;
        virtual int  getWidth() = 0;
        virtual int  getHeight() = 0;
    };
}