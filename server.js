const testAddon = require('./build/Release/opticalFlow_addon.node');

console.log('addon', testAddon.hello())

module.exports = testAddon;
