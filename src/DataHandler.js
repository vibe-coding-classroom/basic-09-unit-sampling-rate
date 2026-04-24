/**
 * DataHandler: Manages communication throttling and protocol optimization.
 */
class DataHandler {
    /**
     * @param {number} minInterval Minimum time between sends (ms) - Task 3 requirement: 20ms
     */
    constructor(minInterval = 20) {
        this.minInterval = minInterval;
        this.lastSendTime = 0;
        this.useMinifiedProtocol = true;
    }

    /**
     * Sends control data if throttling allows
     * @param {number} linearVelocity 
     * @param {number} angularVelocity 
     * @returns {string|null} The payload string if sent, else null
     */
    processCommand(linearVelocity, angularVelocity) {
        const now = Date.now();
        
        // Throttling logic
        if (now - this.lastSendTime < this.minInterval) {
            return null; // Skip this frame
        }

        this.lastSendTime = now;

        // Protocol optimization (Minification)
        let payload;
        if (this.useMinifiedProtocol) {
            payload = {
                v: parseFloat(linearVelocity.toFixed(2)),
                w: parseFloat(angularVelocity.toFixed(2))
            };
        } else {
            payload = {
                linear_velocity: parseFloat(linearVelocity.toFixed(2)),
                angular_velocity: parseFloat(angularVelocity.toFixed(2))
            };
        }

        return JSON.stringify(payload);
    }

    setThrottling(interval) {
        this.minInterval = interval;
    }

    setProtocolMinified(isMinified) {
        this.useMinifiedProtocol = isMinified;
    }
}

// Export for use in Node.js or Browser
if (typeof module !== 'undefined' && module.exports) {
    module.exports = DataHandler;
} else {
    window.DataHandler = DataHandler;
}
