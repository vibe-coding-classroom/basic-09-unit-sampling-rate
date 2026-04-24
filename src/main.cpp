#include <Arduino.h>
#include <ArduinoJson.h>
#include "Filter.h"

// Task 2: FIFO Buffer length 12
MovingAverageFilter sensorFilter(12);

// For simulating sensor noise
float getRawSensorData() {
    // Base signal + random noise
    static float angle = 0;
    angle += 0.1;
    return sin(angle) * 100.0 + random(-10, 10);
}

void setup() {
    Serial.begin(115200);
    while (!Serial) continue;
    
    Serial.println("--- Sampling Rate & DSP Unit Initialized ---");
}

void loop() {
    // Task 1: Sampling Frequency control (conceptually handled here)
    // In a real app, this would be tied to an interval
    
    static uint32_t lastSampleTime = 0;
    uint32_t now = millis();
    
    // Default sampling rate for this demo: 50Hz (20ms)
    if (now - lastSampleTime >= 20) {
        lastSampleTime = now;
        
        float raw = getRawSensorData();
        float filtered = sensorFilter.update(raw);
        
        // Output for Serial Plotter
        Serial.print("Raw:");
        Serial.print(raw);
        Serial.print(",");
        Serial.print("Filtered:");
        Serial.println(filtered);
    }
    
    // Task 3: Handle incoming commands with optimized protocol
    if (Serial.available()) {
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, Serial);
        
        if (!error) {
            // Support both verbose and minified keys
            float v = doc["v"] | doc["linear_velocity"] | 0.0f;
            float w = doc["w"] | doc["angular_velocity"] | 0.0f;
            
            Serial.printf("Command Received -> v: %.2f, w: %.2f\n", v, w);
        }
    }
}
