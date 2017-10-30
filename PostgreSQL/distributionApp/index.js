const express = require('express');
const bodyParser = require('body-parser');
const pgp = require("pg-promise")(/*options*/);


const app = express();
app.disable('etag');
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

app.get('/query-wo', function(req, res) {
  queryWO()
    .then(() => {
      const timeDiff = Number(new Date()) - Number(timeStart);
      res.status(200).send({
        time: timeDiff
      });
    })
    .catch(() => res.status(500).send());
});

app.get('/query-w', function(req, res) {
  queryW()
    .then(() => {
      const timeDiff = Number(new Date()) - Number(timeStart);
      res.status(200).send({
        time: timeDiff
      });
    })
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
};

let timeStart;
const queryWO = () => {
  return db.any("drop index contracts_wo_programs_contract_date_idx;")
    .then(() => {
      timeStart = Number(new Date());
      return db.any("SELECT * FROM contracts_wo_programs JOIN clients USING (client_id) WHERE contract_date between NOW() and (NOW() + INTERVAL '30 DAY')")
    })
    .catch(() => {
      timeStart = Number(new Date());
      return db.any("SELECT * FROM contracts_wo_programs JOIN clients USING (client_id) WHERE contract_date between NOW() and (NOW() + INTERVAL '30 DAY')")
    })
};

const queryW = () => {
  return db.any("create index on contracts_wo_programs(contract_date);")
    .then(() => {
      timeStart = Number(new Date());
      return db.any("SELECT * FROM contracts_wo_programs JOIN clients USING (client_id) WHERE contract_date between NOW() and (NOW() + INTERVAL '30 DAY')")
    })
};
