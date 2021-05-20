const addon = require('bindings')('algorithm'); // import 'greet.node'
exports.simpleAlgo = addon.algoSimple;
exports.hybridAlgo = addon.algoHybrid;
