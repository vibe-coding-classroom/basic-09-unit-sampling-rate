# Signal Quality & DSP Experiment Report

## Task 1: Jitter & Control Feel Lab

| Sampling Frequency (Hz) | Interval (ms) | Subjective Control Feel (1-10) | Notes (Jitter/Delay) |
|-------------------------|---------------|-------------------------------|----------------------|
| 5 Hz                    | 200 ms        |                               |                      |
| 10 Hz                   | 100 ms        |                               |                      |
| 20 Hz                   | 50 ms         |                               |                      |
| 50 Hz                   | 20ms          |                               |                      |
| 100 Hz                  | 10ms          |                               |                      |

**Analysis:**
- At what frequency does the control start to feel "smooth"?
- What happens at very low frequencies?

---

## Task 2: Moving Average Filter (SMA)

| Buffer Length (N) | Signal Stability | Latency (Perceived) |
|-------------------|------------------|---------------------|
| 5                 |                  |                     |
| 12 (Default)      |                  |                     |
| 30                |                  |                     |
| 50                |                  |                     |

**Observation:**
- How does increasing the buffer length affect the "jitter" in the signal?
- At what length does the "lag" (phase shift) become problematic for real-time control?

---

## Task 3: Protocol Optimization

- **Original JSON Size:** `{"linear_velocity": 1.00, "angular_velocity": 0.50}` -> ~56 bytes
- **Minified JSON Size:** `{"v": 1.00, "w": 0.50}` -> ~23 bytes
- **Reduction Ratio:** 

**Conclusion:**
How does throttling and minification improve the robustness of the ESP32 communication?
