var express = require('express');
var app = express();

app.get('/', function (req, res) {
  res.send('Hello World!');
});

app.listen(3000, function () {
  console.log('Example app listening on port 3000!');
});


var pgp = require("pg-promise")(/*options*/);
var db = pgp("postgres://vadim:vadim@localhost:5432/DistributionOfSoftware");

db.one("SELECT * FROM d_clients LIMIT 1", 123)
  .then(function (data) {
      console.log("DATA:", data);
  })
  .catch(function (error) {
      console.log("ERROR:", error);
  });