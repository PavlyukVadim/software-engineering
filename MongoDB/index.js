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
