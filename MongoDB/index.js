db.getCollection('contracts').find({contract_id: 68})

// update collection contracts 

db.getCollection('contracts').update(
  {contract_id: 67},
  {
    $set: {
      client: {
        fullName: "Alexander Moore",
        address: "622 Roberts",
        company: "company#_Moore"
      }
    },
    $unset: {
      "client_id" : 1,
    }
  }
);


db.getCollection('contracts').update(
  {contract_id: 68},
  {
    $set: {
      client: {
        fullName: "Alexander Smith",
        address: "6 Saxton Street",
        company: "_Smith"
      }
    },
    $unset: {
      "client_id" : 1,
    }
  }
);

db.getCollection('contracts').update(
  {contract_id: 69},
  {
    $set: {
      client: {
        fullName: "Alexander Miller",
        address: "9680 Edgemont",
        company: "company#_Miller"
      }
    },
     $unset: {
      "client_id" : 2,
    }
  }
);

db.getCollection('contracts').update(
  {contract_id: 70},
  {
    $set: {
      client: {
        fullName: "Williams Jesus",
        address: "9680 Edgemont",
        company: "company#_Williams"
      }
    },
    $unset: {
      "client_id" : 2,
    }
  }
);

db.getCollection('contracts').update(
  {contract_id: 71},
  {
    $set: {
      client: {
        fullName: "Michael Jones",
        address: "71 N. Baker Lane",
        company: "company#_Jones"
      }
    },
    $unset: {
      "client_id" : 3,
    }
  }
);


// get number of contracts for each year
db.getCollection('contracts').aggregate([
  {
    $group: {
     _id: "$year",
      count: { $sum: 1 }
    }
  }
]);

// get number of contracts after 2007
db.getCollection('contracts').aggregate([
  {
    $match: {
      year: {
        $gt: 2007
      }
    },
  },
  {
    $group: {
     _id: "$year",
      count: { $sum: 1 }
    }
  }
]);

// get quantity of client with the same name 
db.getCollection('contracts').aggregate([
  { 
    $match: {
      "client.fullName": {
        $regex: /^A/
      }
    }
  },
  {
    $group: {
     _id: "$client.fullName" ,
      count: { $sum: 1 },
      quantity: { $sum: "$quantity" }
    }
  }
]);

// get avg quantity for each client by years
db.getCollection('contracts').aggregate([
  {
    $group: {
     _id: {
         year: "$year",
         client: "$client.fullName"
      },
      avg_quantity: { $avg: "$quantity" },
      quantity: { $sum: "$quantity" }
    }
  }
])


var mapComp = function () {
  var output = {
    MUid: this.MUId,
    name: this.Nm,
    MU: null
  };
  emit(this.MUId, output);
};

var mapCMU = function () {
  var output= {
    MUid: this.Id,
    name:null,
    MU:this.Nm
  }
  emit(this.Id, output);
};

var reduceF = function(key, values) {
  var outs = {
    name: null,
    MU: null
  };
  values.forEach(function(v) {
  if(outs.name == null) {
    outs.name = v.name
  }
  if(outs.MU == null) {
    outs.MU = v.MU
  }
  });
  return outs;
};

result = db.cComp.mapReduce(mapComp, reduceF, {out: {reduce: 'Comp_CMU'}});
result = db.CMU.mapReduce(mapCMU, reduceF, {out: {reduce: 'Comp_CMU'}});
db.Comp_CMU.find()
----------

function mapPrograms() {
  var result = {
    pId: this.program_id,
    programName: this.program_name,
    contractId: null,
  };
  emit(result.pId, result);
};

function mapContracts() {
  var result = {
    pId: this.program_id,
    programName: null,
    contractId: this.contract_id, 
  };
  emit(result.pId, result);
};

function reduce(key, values) {
  var result = {
    contractId: null,
    programName: null
  };

  values.forEach(function(obj) {
    if (result.contractId == null) {
      result.contractId = obj.contractId;
    }
    if (result.programName == null) {
      result.programName = obj.programName;
    }
  });
  return result;
};

result = db.getCollection('contracts').mapReduce(mapContracts, reduce, {out: {reduce: 'contractsWP'}});
result = db.getCollection('programs').mapReduce(mapPrograms, reduce, {out: {reduce: 'contractsWP'}});
db.getCollection('contractsWP').find({});
