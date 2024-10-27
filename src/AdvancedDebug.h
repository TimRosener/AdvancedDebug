// AdvancedDebug.h
#ifndef ADVANCED_DEBUG_H
#define ADVANCED_DEBUG_H

#include <Arduino.h>
#include <stdint.h>

// Platform-specific includes
#if defined(ESP32)
    #include <esp_heap_caps.h>
    #include "freertos/FreeRTOS.h"
    #include "freertos/semphr.h"
#elif defined(ARDUINO_ARCH_RP2040)
    #include <pico/mutex.h>
    #include "pico/stdlib.h"
    #include "hardware/sync.h"
#endif

class AdvancedDebug {
private:
    bool isEnabled;
    
    // Platform-specific mutex implementation
    #if defined(ESP32)
        SemaphoreHandle_t mutex;
    #elif defined(ARDUINO_ARCH_RP2040)
        mutex_t mutex;
    #endif

    void lock();
    void unlock();

    // Private print functions
    void printPairWithType(const char* text, bool value);
    void printPairWithType(const char* text, int8_t value);
    void printPairWithType(const char* text, uint8_t value);
    void printPairWithType(const char* text, int16_t value);
    void printPairWithType(const char* text, uint16_t value);
    void printPairWithType(const char* text, int32_t value);
    void printPairWithType(const char* text, uint32_t value);
    void printPairWithType(const char* text, float value);
    void printPairWithType(const char* text, double value);
    void printPairWithType(const char* text, const char* value);

    // Base case for recursion
    void printMultiple() {}
    
    // Handle pairs of parameters
    template<typename T>
    void printMultiple(const char* text, T value) {
        printPairWithType(text, value);
    }
    
    // Recursive case for multiple pairs
    template<typename T, typename... Args>
    void printMultiple(const char* text, T value, Args... args) {
        printPairWithType(text, value);
        Serial.print(", ");
        printMultiple(args...);
    }

public:
    AdvancedDebug();
    ~AdvancedDebug();
    
    void begin(unsigned long baudRate = 9600);
    void status(bool enable);
    bool isActive() const { return isEnabled; }

    // Single parameter print function
    void print(const char* text) {
        if (!isEnabled) return;
        lock();
        Serial.println(text);
        unlock();
    }
    
    // Two parameter print function
    template<typename T>
    void print(const char* text, T value) {
        if (!isEnabled) return;
        lock();
        printPairWithType(text, value);
        Serial.println();
        unlock();
    }
    
    // Multi-parameter print function
    template<typename... Args>
    void print(const char* text1, Args... args) {
        if (!isEnabled) return;
        lock();
        printMultiple(text1, args...);
        Serial.println();
        unlock();
    }
};

extern AdvancedDebug Debug;

#endif // ADVANCED_DEBUG_H