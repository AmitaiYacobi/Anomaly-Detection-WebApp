const express = require('express');
const morgan = require('morgan');

const app = express();

app.listen(9876);

app.use(express.static('views'));
app.use(express.urlencoded({extended: true}));
app.use(express.json());
app.use(morgan('dev'));

app.post('/api/model', (req, res) => {
  console.log(req.query);
});