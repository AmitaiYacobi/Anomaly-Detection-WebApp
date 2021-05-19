const express = require('express');
// const {get} = require('lodash');
// const morgan = require('morgan');
const fileUpload = require('express-fileupload');
const bodyParser = require('body-parser');
const fs = require('fs');
const model = require('../model/anomalyDetection')

const app = express();

app.listen(8080);

app.use(express.static('../view'));

app.use(fileUpload());

app.use(bodyParser.urlencoded({extended: false}))

app.use(express.urlencoded({extended: true}));

app.use(express.json());

// app.use(morgan('dev'));

app.get('/', (req, res) => {
  res.sendFile("./index.html");
});

app.post('/detect/:algorithm/:trainCSV/:testCSV', (req, res)=>{
  var result = model.detect(req.params.algorithm, req.params.trainCSV, req.params.testCSV);
  res.write(result);
  res.end();
});



app.post('/detect', (req, res) => {
  var algo;
  var algoIndex = req.body.algo;
    if (algoIndex == 1)
      algo = 'Regression';
    else if (algoIndex == 2)
      algo = 'Hybrid';
  var fullPath = "/detect/"
  fullPath = fullPath.concat(algo)
  fullPath = fullPath.concat("/")
  fullPath = fullPath.concat(req.files.train.name)
  fullPath = fullPath.concat("/")
  fullPath = fullPath.concat(req.files.test.name)
  res.redirect(307, fullPath);
});
