const express = require('express');
const fileUpload = require('express-fileupload');
const bodyParser = require('body-parser');
const model = require('../model/anomalyDetection')
const fs = require('fs');

const app = express();

app.listen(8080);

app.use(express.static('../view'));

app.use(fileUpload());

app.use(bodyParser.urlencoded({ extended: false }))

app.use(express.urlencoded({ extended: true }));

app.use(express.json());

app.get('/', (req, res) => {
    res.sendFile('./index.html');
});

app.post('/detect', (req, res) => {
    var algo;
    var algoIndex = req.body.algo;
    if (algoIndex == 1)
        algo = 'Regression';
    else if (algoIndex == 2)
        algo = 'Hybrid';
    var fullPath = '/detect/'
    var trainCsv = req.files.train.data.toString();
    var testCsv = req.files.test.data.toString();
    fs.writeFileSync('train.csv', trainCsv, (err) => {
        if (err) throw err;
    });
    fs.writeFileSync('test.csv', testCsv, (err) => {
        if (err) throw err;
    });
    fs.writeFileSync('output.csv', "", (err) => {
        if (err) throw err;
    });
    fullPath = fullPath.concat(algo)
    fullPath = fullPath.concat('/')
    fullPath = fullPath.concat('train.csv')
    fullPath = fullPath.concat('/')
    fullPath = fullPath.concat('test.csv')
    res.redirect(307, fullPath);
});

app.post('/detect/:algorithm/:trainCSV/:testCSV', (req, res) => {
    var result = model.detect(req.params.algorithm, req.params.trainCSV, req.params.testCSV);
    res.write(result);
    fs.unlink('train.csv', (err) => {
        if (err) throw err;
    });
    fs.unlink('test.csv', (err) => {
        if (err) throw err;
    });
    fs.unlink('output.csv', (err) => {
        if (err) throw err;
    });
    res.end();
});