const { Console } = require('console');
const express = require('express');
const fs = require('fs');

const app = express();
app.use(express.static('..'));

function detect(algorithm, trainCSVpath, testCSVpath){
  fs.writeFileSync('input.txt', algorithm, (err) => {
    if (err) throw err;
  });
  fs.appendFileSync('input.txt', '\ndone\n', (err) => {
    if (err) throw err;
  });
  fs.readFile(trainCSVpath, (err,data)=>{
      if(err)
          console.log(err)
      else {
        fs.appendFile('input.txt', data.toString(), (err) => {
          if (err) throw err;
        });
      }
  })
  fs.appendFileSync('input.txt', 'done\n', (err) => {
    if (err) throw err;
  });
  fs.readFile(testCSVpath, (err,data)=>{
      if(err)
          console.log(err)
      else {
        fs.appendFile('input.txt', data.toString(), (err) => {
          if (err) throw err;
        });
      }
  })
  fs.appendFileSync('input.txt', 'done\n', (err) => {
    if (err) throw err;
  });
      var result = "good" //call to c++ algorithm
      return result; // to do: read from output.csv
}


module.exports.detect = detect