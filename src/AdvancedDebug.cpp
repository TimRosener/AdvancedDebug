// AdvancedDebug.cpp
#include "AdvancedDebug.h"

AdvancedDebug Debug;

AdvancedDebug::AdvancedDebug() : isEnabled(true) {
    #if defined(ESP32)
        mutex = xSemaphoreCreateMutex();
    #elif defined(ARDUINO_ARCH_RP2040)
        mutex_init(&mutex);
    #endif
}

AdvancedDebug::~AdvancedDebug() {
    #if defined(ESP32)
        vSemaphoreDelete(mutex);
    #endif
}

void AdvancedDebug::lock() {
    #if defined(ESP32)
        xSemaphoreTake(mutex, portMAX_DELAY);
    #elif defined(ARDUINO_ARCH_RP2040)
        mutex_enter_blocking(&mutex);
    #endif
}

void AdvancedDebug::unlock() {
    #if defined(ESP32)
        xSemaphoreGive(mutex);
    #elif defined(ARDUINO_ARCH_RP2040)
        mutex_exit(&mutex);
    #endif
}

void AdvancedDebug::begin(unsigned long baudRate) {
    Serial.begin(baudRate);
    while(!Serial) delay(10);
}

void AdvancedDebug::status(bool enable) {
    isEnabled = enable;
}

void AdvancedDebug::printPairWithType(const char* text, bool value) {
    Serial.print(text);
    Serial.print("<B>:");
    Serial.print(value ? "True" : "False");
}

void AdvancedDebug::printPairWithType(const char* text, int8_t value) {
    Serial.print(text);
    Serial.print("<I8>:");
    Serial.print(value);
}

void AdvancedDebug::printPairWithType(const char* text, uint8_t value) {
    Serial.print(text);
    Serial.print("<U8>:");
    Serial.print(value);
}

void AdvancedDebug::printPairWithType(const char* text, int16_t value) {
    Serial.print(text);
    Serial.print("<I16>:");
    Serial.print(value);
}

void AdvancedDebug::printPairWithType(const char* text, uint16_t value) {
    Serial.print(text);
    Serial.print("<U16>:");
    Serial.print(value);
}

void AdvancedDebug::printPairWithType(const char* text, int32_t value) {
    Serial.print(text);
    Serial.print("<I32>:");
    Serial.print(value);
}

void AdvancedDebug::printPairWithType(const char* text, uint32_t value) {
    Serial.print(text);
    Serial.print("<U32>:");
    Serial.print(value);
}

void AdvancedDebug::printPairWithType(const char* text, float value) {
    Serial.print(text);
    Serial.print("<F>:");
    Serial.print(value);
}

void AdvancedDebug::printPairWithType(const char* text, double value) {
    Serial.print(text);
    Serial.print("<D>:");
    Serial.print(value);
}

void AdvancedDebug::printPairWithType(const char* text, const char* value) {
    Serial.print(text);
    Serial.print("<S>:");
    Serial.print(value ? value : "null");
}