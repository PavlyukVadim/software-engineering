const express = require('express');
const bodyParser = require('body-parser');
const pgp = require("pg-promise")(/*options*/);


const app = express();

app.use(bodyParser.json()); 
app.use('/', express.static(__dirname + '/static'));
app.use('/static', express.static(__dirname + '/static'));
app.use('/vendor', express.static(__dirname + '/vendor'));

app.post('/', function(req, res) {
  console.log('post', req.body);
});

app.delete('/', function(req, res) {
  clearAllTables()
    .then(() => res.status(200).send())
    .catch(() => res.status(500).send());
});

app.listen(3000, function () {
  console.log('Example app listening on port 3000!');
});



const db = pgp("postgres://vadim:vadim@localhost:5432/DistributionOfSoftware");

const clearAllTables = () => {
  return db.one('SELECT * FROM reset_tabels();')
    .then(function (data) {
      console.log("DATA:", data);
    })
    .catch(function (error) {
      console.log("ERROR:", error);
    });
};