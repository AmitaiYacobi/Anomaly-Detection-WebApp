const {Console} = require('console');
const express = require('express');
const fs = require('fs');
const d3 = require("d3")
const jsonToTable = require('json-to-table');
let csvToJson = require('convert-csv-to-json');


const app = express();

app.use(express.static('..'));

// Convert cs file into JSON
function csvJSON(csv) {
  var data = d3.csvParse(csv);
  var headers = Object.keys(data[0]);
  var myObject = {};

  headers.forEach(function(d) {
    myObject[d] = [];
  });

  data.forEach(function(d) {
    for (var key in d) {
      myObject[key].push(d[key]);
    }
  });
  return JSON.stringify(myObject);
}

async function sleep_sec(){
  console.log("sleep")
  await new Promise(resolve => setTimeout(resolve, 1000));
  console.log("end sleep")
  return;
}

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

   // call to c++ algorithm that generate "output.csv"
  
  let outputJSON = csvToJson.fieldDelimiter(',').getJsonFromCsv("output.csv");
  // outputJSON = fs.readFileSync("output.json").toString();
  return JSON.stringify(outputJSON);


}

module.exports.detect = detect