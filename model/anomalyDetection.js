const { Console } = require('console');
const express = require('express');
const fs = require('fs');
const d3 = require("d3")
let csvToJson = require('convert-csv-to-json');


const app = express();

app.use(express.static('..'));

const algorithms = require('..');
path = require('path')

// Convert cs file into JSON
function csvJSON(csv) {
    var data = d3.csvParse(csv);
    var headers = Object.keys(data[0]);
    var myObject = {};

    headers.forEach(function (d) {
        myObject[d] = [];
    });

    data.forEach(function (d) {
        for (var key in d) {
            myObject[key].push(d[key]);
        }
    });
    return JSON.stringify(myObject);
}

function detect(option, trainCsvPath, testCsvPath) {

    // call to c++ algorithm that generate "output.csv"
    var outputPath = path.join(__dirname, '../controller/') + 'output.csv';
    var inputTrainPath = path.join(__dirname, '../controller/') + trainCsvPath.toString();
    var inputTestPath = path.join(__dirname, '../controller/') + testCsvPath.toString();
    if (option == "Hybrid") {
        algorithms.hybridAlgo(inputTrainPath.toString(), inputTestPath.toString(), outputPath.toString());
    }
    else {
        algorithms.simpleAlgo(inputTrainPath.toString(), inputTestPath.toString(), outputPath.toString());
    }
    let outputJSON = csvToJson.fieldDelimiter(',').getJsonFromCsv("output.csv");
    return JSON.stringify(outputJSON);


}

module.exports.detect = detect