const express = require('express');
const {get} = require('lodash');
const morgan = require('morgan');
const fileUpload = require('express-fileupload');
const bodyParser = require('body-parser');

const app = express();

app.listen(8080);

app.use(express.static('../view'));

app.use(fileUpload());

app.use(bodyParser.urlencoded({extended: false}))

app.use(express.urlencoded({extended: true}));

app.use(express.json());

app.use(morgan('dev'));

app.get('/', (req, res) => {
  res.sendFile(index.html);
});

app.post('/detect', (req, res) => {
  var algo
  var algoIndex = req.body.algo;
  if (algoIndex == 1)
    algo = 'Regression';
  else if (algoIndex == 2)
    algo = 'Hybrid';
  if (req.files) {
    var trainCsv = req.files.train;
    var testCSV = req.files.test;
    console.log(trainCsv.data.toString());
  }
});
