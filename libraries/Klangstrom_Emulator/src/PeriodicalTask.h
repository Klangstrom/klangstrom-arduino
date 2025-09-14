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

#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

class PeriodicalTask {
public:
    PeriodicalTask() : frequency(1000), running(false) {}

    void start() {
        running       = true;
        worker_thread = std::thread(&PeriodicalTask::run, this);
    }

    void stop() {
        running = false;
        if (worker_thread.joinable()) {
            worker_thread.join();
        }
    }

    void sleep_for(uint32_t microseconds) {
        std::lock_guard<std::mutex> lock(sleep_mutex);
        std::chrono::microseconds   mDuration(microseconds);
        sleep_duration = mDuration;
    }

    void set_callback(std::function<void()> function_callback) {
        callback = function_callback;
    }

    void set_frequency(float frequency_hz) {
        std::lock_guard<std::mutex> lock(frequency_mutex);
        frequency = frequency_hz;
    }

    ~PeriodicalTask() {
        stop();
    }

private:
    void run() {
        using namespace std::chrono;
        while (running) {
            /* loop */
            {
                std::lock_guard<std::mutex> lock(frequency_mutex);
                period = duration<double>(1.0 / frequency);
            }
            auto next_call_time = steady_clock::now() + duration_cast<steady_clock::duration>(period);
            if (callback) {
                callback();
            }
            std::this_thread::sleep_until(next_call_time);

            /* sleep */
            {
                std::lock_guard<std::mutex> lock(sleep_mutex);
                if (sleep_duration > microseconds(0)) {
                    std::this_thread::sleep_for(sleep_duration);
                    sleep_duration = microseconds(0); // Reset sleep duration after sleeping
                }
            }
        }
    }

    float                         frequency;
    std::chrono::microseconds     sleep_duration{0};
    std::atomic<bool>             running;
    std::thread                   worker_thread;
    std::mutex                    frequency_mutex;
    std::mutex                    sleep_mutex;
    std::chrono::duration<double> period;
    std::function<void()>         callback;
};
