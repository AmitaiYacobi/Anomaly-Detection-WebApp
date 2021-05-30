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
    fullPath = fullPath.concat(algo)
    fullPath = fullPath.concat('/')
    fullPath = fullPath.concat('train.csv')
    fullPath = fullPath.concat('/')
    fullPath = fullPath.concat('test.csv')
    res.redirect(307, fullPath);
});

app.post('/detect/:algorithm/:trainCSV/:testCSV', (req, res) => {
    fs.writeFileSync('output.csv', "", (err) => {
        if (err) throw err;
    });
    var outputJson = model.detect(req.params.algorithm, req.params.trainCSV, req.params.testCSV);
    var data = JSON.parse(outputJson);
    res.writeHead(200, { 'Content-Type': 'text/html' });
    res.write('<div><html>');
    res.write('<center>');
    res.write('<head>');

    res.write('<style> .styled-table {border-collapse: collapse;margin: 25px 0;font-size: 0.9em;font-family: sans-serif; min-width: 400px;box-shadow: 0 0 20px rgba(0, 0, 0, 0.15);}');
    res.write('.styled-table thead tr {background-color: #1974D2;color: #ffffff;text-align: center;}');
    res.write('.styled-table th,.styled-table td {padding: 12px 15px;}');
    res.write('.styled-table tbody tr {background-color: #FFFFFF; border-bottom: 1px solid #dddddd;text-align: center;}');
    res.write('.styled-table tbody tr: nth-of-type(even) {background-color: #f3f3f3;}');
    res.write('.styled-table tbody tr: last-of-type {border-bottom: 2px solid #009879;}');
    res.write('.styled-table tbody tr.active-row {font-weight: bold;color: #009879;}</style>');

    res.write('</head>');
    res.write('<body>');
    res.write('<table class="styled-table" >');
    res.write('<thead><tr>');
    if (outputJson == '[]') {
        res.write('<th>The algorithm didn\'t find any anomalies</th>');
    }
    for (const key in data[0]) {
        res.write('<th>');
        res.write(key.replace("_"," "));
        res.write('</th>');
        
    }
    res.write('</tr></thead><tbody>');
    for (var i = 0; i < data.length; i++) {
        res.write('<tr>');
        for (const key in data[i]) {
            res.write('<td>');
            res.write(data[i][key]);
            res.write('</td>');
        }
        res.write('</tr > ');
    }
    res.write('</tbody > ');
    res.write('</table>');
    res.write('</form>');
    res.write('</body>');
    res.write('</center>');
    res.write('</html>');
    res.write('</div>');

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