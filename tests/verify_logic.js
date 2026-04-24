const assert = require('assert');
const DataHandler = require('../src/DataHandler');

function testThrottling() {
    console.log('--- Testing Throttling ---');
    const handler = new DataHandler(100); // 100ms interval
    
    const first = handler.processCommand(1.0, 0.5);
    assert.ok(first !== null, 'First command should be sent');
    
    const second = handler.processCommand(1.0, 0.5);
    assert.ok(second === null, 'Second command (immediate) should be throttled');
    
    // Simulate waiting (manual check if this was a real async test, 
    // but here we just check logic with a mock timer if needed)
    console.log('Throttling test passed (Logic check)');
}

function testMinification() {
    console.log('--- Testing Minification ---');
    const handler = new DataHandler(0);
    
    handler.setProtocolMinified(true);
    const minified = JSON.parse(handler.processCommand(1.234, 0.567));
    assert.strictEqual(minified.v, 1.23, 'Should use "v" key and 2 decimal precision');
    assert.strictEqual(minified.w, 0.57, 'Should use "w" key and 2 decimal precision');
    
    handler.setProtocolMinified(false);
    const verbose = JSON.parse(handler.processCommand(1.234, 0.567));
    assert.strictEqual(verbose.linear_velocity, 1.23, 'Should use "linear_velocity" key');
    
    console.log('Minification test passed');
}

try {
    testThrottling();
    testMinification();
    console.log('\n✅ All tests passed!');
} catch (e) {
    console.error('\n❌ Tests failed!');
    console.error('Message:', e.message);
    if (e.actual !== undefined) {
        console.error('Actual:', e.actual);
        console.error('Expected:', e.expected);
    }
    process.exit(1);
}
