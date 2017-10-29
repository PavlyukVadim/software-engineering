const express = require('express');
const bodyParser = require('body-parser');
const pgp = require("pg-promise")(/*options*/);


const app = express();

app.use(bodyParser.json()); 
app.use('/', express.static(__dirname + '/static'));
app.use('/static', express.static(__dirname + '/static'));
app.use('/vendor', express.static(__dirname + '/vendor'));

app.post('/addClients', function(req, res) {
  const numberOfRows = req.body.numberOfRows;
  addClients(numberOfRows)
    .then((data) => res.status(200).send(data))
    .catch(() => res.status(500).send());
});

app.post('/addContracts', function(req, res) {
  const numberOfRows = req.body.numberOfRows;
  addContracts(numberOfRows)
    .then((data) => res.status(200).send(data))
    .catch(() => res.status(500).send());
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

const addClients = (numberOfRows) => {
  return db.one('SELECT * FROM fill_clients_table($1);', [numberOfRows])
};

const addContracts = (numberOfRows) => {
  return db.one('SELECT * FROM fill_contracts_wo_programs_table($1);', [numberOfRows])
};


const clearAllTables = () => {
  return db.one('SELECT * FROM reset_tabels();')
    .then(function (data) {
      console.log("DATA:", data);
    })
    .catch(function (error) {
      console.log("ERROR:", error);
    });
};