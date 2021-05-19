const {Console} = require('console');
const express = require('express');
const fs = require('fs');

const app = express();

app.use(express.static('..'));

function detect(algorithm, trainCsvPath, testCsvPath) {
  trainCsv = fs.readFileSync(trainCsvPath).toString();
  testCsv = fs.readFileSync(testCsvPath).toString();
  fs.writeFileSync('input.txt', algorithm, (err) => {
    if (err) throw err;
  });
  fs.appendFileSync('input.txt', '\ndone\n', (err) => {
    if (err) throw err;
  });
  fs.appendFileSync('input.txt', trainCsv, (err) => {
    if (err) throw err;
  });
  fs.appendFileSync('input.txt', 'done\n', (err) => {
    if (err) throw err;
  });
  fs.appendFileSync('input.txt', testCsv, (err) => {
    if (err) throw err;
  });
  fs.appendFileSync('input.txt', 'done\n', (err) => {
    if (err) throw err;
  });
  var result = 'good'  // call to c++ algorithm
  return result;       // to do: read from output.csv
}

module.exports.detect = detect